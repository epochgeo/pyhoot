/**
 * The original code by Maxar/NGA is licensed under GPLv3.
 * 
 * All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
 * GPLv3 license.
 *
 * --------------------------------------------------------------------
 *
 * @copyright Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021 Maxar (http://www.maxar.com/)
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "PythonMatchCreator.h"

// hoot
#include <hoot/core/conflate/matching/MatchThreshold.h>
#include <hoot/core/conflate/matching/MatchType.h>
#include <hoot/core/criterion/ArbitraryCriterion.h>
#include <hoot/core/criterion/StatusCriterion.h>
#include <hoot/core/index/OsmMapIndex.h>
#include <hoot/core/info/CreatorDescription.h>
#include <hoot/core/schema/OsmSchema.h>
#include <hoot/core/util/ConfPath.h>
#include <hoot/core/util/ConfigOptions.h>
#include <hoot/core/util/Factory.h>
#include <hoot/core/util/StringUtils.h>
#include <hoot/core/visitors/ElementConstOsmMapVisitor.h>
#include <hoot/core/visitors/SpatialIndexer.h>
#include <hoot/core/criterion/PolygonCriterion.h>
#include <hoot/core/criterion/NonConflatableCriterion.h>
#include <hoot/core/criterion/PointCriterion.h>
#include <hoot/core/criterion/ChainCriterion.h>
#include <hoot/core/util/MemoryUsageChecker.h>
#include <hoot/core/geometry/ElementToGeometryConverter.h>

// pybind11
#include <pybind11/embed.h>

// pyhoot
#include <hoot/bindings/PyBindModule.h>
#include <hoot/core/matching/PythonMatchCreator.h>
#include <hoot/core/matching/PythonMatchVisitor.h>

// Qt
#include <qnumeric.h>
#include <QStringBuilder>
#include <QElapsedTimer>

// Standard
#include <functional>
#include <cmath>

// TGS
#include <tgs/RStarTree/IntersectionIterator.h>
#include <tgs/RStarTree/MemoryPageStore.h>

using namespace geos::geom;
using namespace std;
using namespace Tgs;

namespace py = pybind11;

namespace hoot
{

HOOT_FACTORY_REGISTER(MatchCreator, PythonMatchCreator)

void init_PythonMatchCreator(py::module_& m)
{
    py::class_<PythonMatchCreator>(m, "PythonMatchCreator")
        .def(py::init<>())
        .def("init", &PythonMatchCreator::init)
        .def("setInitFunction", &PythonMatchCreator::setInitFunction)
        .def("getName", &PythonMatchCreator::getName)
        .def("setName", &PythonMatchCreator::setName)
    ;
}

REGISTER_PYHOOT_SUBMODULE(init_PythonMatchCreator)

PythonMatchCreator::PythonMatchCreator()
{
}

void PythonMatchCreator::setConfiguration(const Settings& conf)
{
  ConfigOptions opts(conf);
}

void PythonMatchCreator::init(const ConstOsmMapPtr& map)
{
  if (_initFunction) _initFunction(map);
  _getCachedVisitor(map)->initSearchRadiusInfo();
}

Meters PythonMatchCreator::calculateSearchRadius(
  const ConstOsmMapPtr& map, const ConstElementPtr& e)
{
  return _getCachedVisitor(map)->getSearchRadius(e);
}

void PythonMatchCreator::setArguments(const QStringList& args)
{
  if (args.size() != 1)
  {
    throw HootException("The PythonMatchCreator takes exactly one argument (script path).");
  }

  // Isolate* current = v8::Isolate::GetCurrent();
  // HandleScope handleScope(current);
  // _scriptPath = ConfPath::search(args[0], "rules");
  // _script = std::make_shared<PluginContext>();
  // Context::Scope context_scope(_script->getContext(current));
  // _script->loadScript(_scriptPath, "plugin");
  // // bit of a hack...see MatchCreator.h...need to refactor
  // _description = className() + "," + args[0];
  // _cachedScriptVisitor.reset();
  // _scriptInfo = _getScriptDescription(_scriptPath);

  setConfiguration(conf());
  // Validate the configuration outside of setConfiguration, since it needs to be done each time a
  // different conflate script is specified.
  _validateConfig(_scriptInfo.getBaseFeatureType());

  LOG_DEBUG(
    "Set arguments for: " << className() << " - rules: " << QFileInfo(_scriptPath).fileName());
}

void PythonMatchCreator::setInitFunction(std::function<void(const ConstOsmMapPtr& map)> func)
{
  _initFunction = func;
}

void PythonMatchCreator::_validateConfig(
  const CreatorDescription::BaseFeatureType& baseFeatureType)
{
}

// void PythonMatchCreator::_validatePluginConfig(
//   const CreatorDescription::BaseFeatureType& baseFeatureType, Local<Object> plugin) const
// {
// }

MatchPtr PythonMatchCreator::createMatch(
  const ConstOsmMapPtr& map, ElementId eid1, ElementId eid2)
{
  LOG_VART(eid1);
  LOG_VART(eid2);

  // There may be some benefit at some point in caching matches calculated in PythonMatchCreator and
  // accessing that cached information here to avoid extra calls into the JS match script. So far,
  // haven't seen any performance improvement after adding match caching.

  assert(false);
  const bool isPointPolyConflation = false; //_scriptPath.contains(POINT_POLYGON_SCRIPT_NAME);
  LOG_VART(isPointPolyConflation);
  bool attemptToMatch = false;
  ConstElementPtr e1 = map->getElement(eid1);
  ConstElementPtr e2 = map->getElement(eid2);
  if (e1 && e2)
  {
    if (!isPointPolyConflation)
    {
      attemptToMatch = isMatchCandidate(e1, map) && isMatchCandidate(e2, map);
    }
    else
    {
      if (!_pointPolyPolyCrit)
      {
          _pointPolyPolyCrit =
            std::make_shared<ChainCriterion>(
              std::make_shared<PolygonCriterion>(map),
              std::make_shared<NonConflatableCriterion>(map));
      }
      if (!_pointPolyPointCrit)
      {
          _pointPolyPointCrit =
            std::make_shared<ChainCriterion>(
              std::make_shared<PointCriterion>(map),
              std::make_shared<NonConflatableCriterion>(map));
      }

      // see related note in PythonMatchCreator::checkForMatch
      attemptToMatch =
        (_pointPolyPointCrit->isSatisfied(e1) && _pointPolyPolyCrit->isSatisfied(e2)) ||
        (_pointPolyPolyCrit->isSatisfied(e1) && _pointPolyPointCrit->isSatisfied(e2));
    }
  }
  LOG_VART(attemptToMatch);

  if (attemptToMatch)
  {
    // Isolate* current = v8::Isolate::GetCurrent();
    // HandleScope handleScope(current);
    // Context::Scope context_scope(_script->getContext(current));

    // Local<Object> mapJs = OsmMapJs::create(map);
    // Persistent<Object> plugin(current, PythonMatchCreator::getPlugin(_script));

    // std::shared_ptr<ScriptMatch> match =
    //   std::make_shared<ScriptMatch>(_script, plugin, map, mapJs, eid1, eid2, getMatchThreshold());
    // match->setMatchMembers(
    //   ScriptMatch::geometryTypeToMatchMembers(
    //     GeometryTypeCriterion::typeToString(_scriptInfo.getGeometryType())));
    // return match;
  }

  return MatchPtr();
}

void PythonMatchCreator::createMatches(
  const ConstOsmMapPtr& map, std::vector<ConstMatchPtr>& matches, ConstMatchThresholdPtr threshold)
{
  // if (!_script)
  // {
  //   throw IllegalArgumentException("The script must be set on the PythonMatchCreator.");
  // }

  // The parent does some initialization we need.
  MatchCreator::createMatches(map, matches, threshold);

  QElapsedTimer timer;
  timer.start();

  // PythonMatchCreator v(map, matches, threshold, _script, _filter);
  // v.setScriptPath(_scriptPath);
  // _descriptionCache[_scriptPath] = _scriptInfo;
  // v.setCreatorDescription(_scriptInfo);
  // v.initSearchRadiusInfo();
  // v.calculateSearchRadius();

  // QFileInfo scriptFileInfo(_scriptPath);

  // // This doesn't work with _candidateDistanceSigma, but right now its set to 1.0 in every script
  // // and has no effect on the search radius.
  // QString searchRadiusStr;
  // const double searchRadius = v.getCustomSearchRadius();
  // if (v.hasCustomSearchRadiusFunction())
  // {
  //   searchRadiusStr = "within a function calculated search radius";
  // }
  // else if (searchRadius < 0)
  // {
  //   searchRadiusStr = "within a feature dependent search radius";
  // }
  // else
  // {
  //   searchRadiusStr =
  //     "within a search radius of " + QString::number(searchRadius, 'g', 2) + " meters";
  // }

  // LOG_INFO(
  //   "Looking for matches with: " << scriptFileInfo.fileName() << " " << searchRadiusStr << "...");
  // LOG_VARD(*threshold);
  // const int matchesSizeBefore = matches.size();

  // _cachedCustomSearchRadii[_scriptPath] = searchRadius;
  // _candidateDistanceSigmaCache[_scriptPath] = v.getCandidateDistanceSigma();

  // LOG_VARD(GeometryTypeCriterion::typeToString(_scriptInfo.getGeometryType()));
  // // kind of hack; not sure of a better way to do determine if we're doing collection relation
  // // conflation
  // if (scriptFileInfo.fileName().toLower().contains("relation"))
  // {
  //   map->visitRelationsRo(v);
  // }
  // else
  // {
  //   switch (_scriptInfo.getGeometryType())
  //   {
  //     case GeometryTypeCriterion::GeometryType::Point:
  //       map->visitNodesRo(v);
  //       break;
  //     case GeometryTypeCriterion::GeometryType::Line:
  //       map->visitWaysRo(v);
  //       map->visitRelationsRo(v);
  //       break;
  //     case GeometryTypeCriterion::GeometryType::Polygon:
  //       map->visitWaysRo(v);
  //       map->visitRelationsRo(v);
  //       break;
  //     default:
  //       // visit all geometry types if the script didn't identify its geometry
  //       map->visitRo(v);
  //       break;
  //   }
  // }

  // const int matchesSizeAfter = matches.size();

  // QString matchType = CreatorDescription::baseFeatureTypeToString(_scriptInfo.getBaseFeatureType());
  // // Workaround for the Point/Polygon script since it doesn't identify a base feature type. See
  // // note in PythonMatchCreator::getIndex and rules/PointPolygon.js.
  // if (_scriptPath.contains(POINT_POLYGON_SCRIPT_NAME))
  // {
  //   matchType = "PointPolygon";
  // }

  // LOG_STATUS(
  //   "\tFound " << StringUtils::formatLargeNumber(v.getNumMatchCandidatesFound()) << " " <<
  //   matchType << " match candidates and " <<
  //   StringUtils::formatLargeNumber(matchesSizeAfter - matchesSizeBefore) <<
  //   " total matches in: " << StringUtils::millisecondsToDhms(timer.elapsed()) << ".");
}

vector<CreatorDescription> PythonMatchCreator::getAllCreators() const
{
  vector<CreatorDescription> result;

  // // find all the files that end with .js in [ConfPath]/rules/
  // const QStringList scripts = ConfPath::find(QStringList() << "*.js", "rules");
  // // go through each script
  // for (int i = 0; i < scripts.size(); i++)
  // {
  //   try
  //   {
  //     // if the script is a valid generic script w/ 'description' exposed, add it to the list.
  //     CreatorDescription d = _getScriptDescription(scripts[i]);
  //     if (!d.getDescription().isEmpty())
  //     {
  //       result.push_back(d);
  //       LOG_TRACE(d.getDescription());
  //     }
  //     else
  //     {
  //       LOG_TRACE(QString("Skipping reporting script %1 because it has no "
  //         "description.").arg(scripts[i]));
  //     }
  //   }
  //   catch (const HootException& e)
  //   {
  //     LOG_WARN("Error loading script: " + scripts[i] + " exception: " + e.getWhat());
  //   }
  // }

  return result;
}

shared_ptr<PythonMatchVisitor> PythonMatchCreator::_getCachedVisitor(const ConstOsmMapPtr& map)
{
  return shared_ptr<PythonMatchVisitor>();
  // if (!_cachedScriptVisitor.get() || _cachedScriptVisitor->getMap() != map)
  // {
  //   LOG_VART(_cachedScriptVisitor.get());
  //   QString scriptPath = _scriptPath;
  //   if (_cachedScriptVisitor.get())
  //   {
  //     LOG_VART(_cachedScriptVisitor->getMap() == map);
  //     scriptPath = _cachedScriptVisitor->getScriptPath();
  //   }
  //   LOG_VART(scriptPath);

  //   QFileInfo scriptFileInfo(_scriptPath);
  //   LOG_TRACE("Resetting the match candidate checker: " << scriptFileInfo.fileName() << "...");

  //   vector<ConstMatchPtr> emptyMatches;
  //   _cachedScriptVisitor =
  //     std::make_shared<PythonMatchCreator>(
  //       map, emptyMatches, ConstMatchThresholdPtr(), _script, _filter);

  //   _cachedScriptVisitor->setScriptPath(scriptPath);

  //   // setting these cached values on the visitor here for performance reasons; this could all be
  //   // consolidated and cleaned up
  //   LOG_VART(_descriptionCache.contains(scriptPath));
  //   if (_descriptionCache.contains(scriptPath))
  //   {
  //     _cachedScriptVisitor->setCreatorDescription(_descriptionCache[scriptPath]);
  //   }

  //   LOG_VART(_candidateDistanceSigmaCache.contains(scriptPath));
  //   if (_candidateDistanceSigmaCache.contains(scriptPath))
  //   {
  //     _cachedScriptVisitor->setCandidateDistanceSigma(_candidateDistanceSigmaCache[scriptPath]);
  //   }

  //   //If the search radius has already been calculated for this matcher once, we don't want to do
  //   //it again due to the expense.
  //   LOG_VART(_cachedCustomSearchRadii.contains(scriptPath));
  //   if (!_cachedCustomSearchRadii.contains(scriptPath))
  //   {
  //     _cachedScriptVisitor->calculateSearchRadius();
  //   }
  //   else
  //   {
  //     LOG_VART(_cachedCustomSearchRadii[scriptPath]);
  //     _cachedScriptVisitor->setCustomSearchRadius(_cachedCustomSearchRadii[scriptPath]);
  //   }
  // }

  // return _cachedScriptVisitor;
}

CreatorDescription PythonMatchCreator::_getScriptDescription(QString path) const
{
  LOG_DEBUG("Getting script description...");

  CreatorDescription result;
  result.setExperimental(true);

  // std::shared_ptr<PluginContext> script = std::make_shared<PluginContext>();
  // Isolate* current = v8::Isolate::GetCurrent();
  // HandleScope handleScope(current);
  // Context::Scope context_scope(script->getContext(current));
  // Local<Context> context = current->GetCurrentContext();
  // script->loadScript(path, "plugin");
  // Persistent<Object> plugin(current, PythonMatchCreator::getPlugin(script));

  // Local<String> descriptionStr = String::NewFromUtf8(current, "description").ToLocalChecked();
  // if (ToLocal(&plugin)->Has(context, descriptionStr).ToChecked())
  // {
  //   Local<Value> value = ToLocal(&plugin)->Get(context, descriptionStr).ToLocalChecked();
  //   result.setDescription(toCpp<QString>(value));
  // }
  // else
  // {
  //   throw IllegalArgumentException("No script description provided for: " + path);
  // }

  // Local<String> experimentalStr = String::NewFromUtf8(current, "experimental").ToLocalChecked();
  // if (ToLocal(&plugin)->Has(context, experimentalStr).ToChecked())
  // {
  //   Local<Value> value = ToLocal(&plugin)->Get(context, experimentalStr).ToLocalChecked();
  //   result.setExperimental(toCpp<bool>(value));
  // }

  // CreatorDescription::BaseFeatureType baseFeatureType =
  //   CreatorDescription::BaseFeatureType::Unknown;
  // Local<String> featureTypeStr = String::NewFromUtf8(current, "baseFeatureType").ToLocalChecked();
  // if (ToLocal(&plugin)->Has(context, featureTypeStr).ToChecked())
  // {
  //   Local<Value> value = ToLocal(&plugin)->Get(context, featureTypeStr).ToLocalChecked();
  //   baseFeatureType = CreatorDescription::stringToBaseFeatureType(toCpp<QString>(value));
  //   result.setBaseFeatureType(baseFeatureType);
  // }
  // // A little kludgy, but we'll identify generic geometry Point/Polygon conflation by its script
  // // name.
  // else if (!path.contains("PointPolygon.js"))
  // {
  //   throw IllegalArgumentException("No base feature type provided for: " + path);
  // }

  // Local<String> geometryTypeStr = String::NewFromUtf8(current, "geometryType").ToLocalChecked();
  // if (ToLocal(&plugin)->Has(context, geometryTypeStr).ToChecked())
  // {
  //   Local<Value> value = ToLocal(&plugin)->Get(context, geometryTypeStr).ToLocalChecked();
  //   result.setGeometryType(GeometryTypeCriterion::typeFromString(toCpp<QString>(value)));
  // }
  // else if (!path.contains("PointPolygon.js"))
  // {
  //   throw IllegalArgumentException("No geometry type provided for: " + path);
  // }

  // // The criteria parsed here describe which feature types a script conflates. Its used only for
  // // determining which conflate ops to disable with SuperfluousConflateOpRemover and for some
  // // scripts, also to determine how to cull features when performing rubbersheeting during search
  // // radius auto-calc. Is does *not* actually cull features during matching.
  // // exports.isMatchCandidate does that. So, there is a bit of a disconnect there. However, it
  // // hasn't caused any problems so far.
  // Local<String> matchCandidateCriterionStr =
  //   String::NewFromUtf8(current, "matchCandidateCriterion").ToLocalChecked();
  // if (ToLocal(&plugin)->Has(context, matchCandidateCriterionStr).ToChecked())
  // {
  //   Local<Value> value = ToLocal(&plugin)->Get(context, matchCandidateCriterionStr).ToLocalChecked();
  //   const QString valueStr = toCpp<QString>(value);
  //   if (valueStr.contains(";"))
  //   {
  //     result.setMatchCandidateCriteria(valueStr.split(";"));
  //   }
  //   else
  //   {
  //     result.setMatchCandidateCriteria(QStringList(valueStr));
  //   }
  // }
  // else
  // {
  //   throw IllegalArgumentException("No match candidate criteria provided for: " + path);
  // }

  // QFileInfo fi(path);
  // result.setClassName(className() + "," + fi.fileName());

  // // config error handling that required plugin
  // _validatePluginConfig(baseFeatureType, ToLocal(&plugin));

  return result;
}

bool PythonMatchCreator::isMatchCandidate(ConstElementPtr element, const ConstOsmMapPtr& map)
{
  // if (!_script)
  // {
  //   throw IllegalArgumentException("The script must be set on the PythonMatchCreator.");
  // }
  return _getCachedVisitor(map)->isMatchCandidate(element);
}

std::shared_ptr<MatchThreshold> PythonMatchCreator::getMatchThreshold()
{
  // if (!_matchThreshold.get())
  // {
  //   if (!_script)
  //   {
  //     throw IllegalArgumentException("The script must be set on the PythonMatchCreator.");
  //   }
  //   Isolate* current = v8::Isolate::GetCurrent();
  //   HandleScope handleScope(current);
  //   Context::Scope context_scope(_script->getContext(current));
  //   Local<Object> plugin = PythonMatchCreator::getPlugin(_script);

  //   double matchThreshold = -1.0;
  //   double missThreshold = -1.0;
  //   double reviewThreshold = -1.0;
  //   try
  //   {
  //     matchThreshold = PythonMatchCreator::getNumber(plugin, "matchThreshold", 0.0, 1.0);
  //     missThreshold = PythonMatchCreator::getNumber(plugin, "missThreshold", 0.0, 1.0);
  //     reviewThreshold = PythonMatchCreator::getNumber(plugin, "reviewThreshold", 0.0, 1.0);
  //   }
  //   catch (const IllegalArgumentException& /*e*/)
  //   {
  //   }

  //   if (matchThreshold != -1.0 && missThreshold != -1.0 && reviewThreshold != -1.0)
  //   {
  //     return std::make_shared<MatchThreshold>(matchThreshold, missThreshold, reviewThreshold);
  //   }
  //   else
  //   {
  //     return std::make_shared<MatchThreshold>();
  //   }
  // }
  return _matchThreshold;
}

QString PythonMatchCreator::getName() const
{
  // QFileInfo scriptFileInfo(_scriptPath);
  // return className() + ";" + scriptFileInfo.fileName();
  return "";
}

QStringList PythonMatchCreator::getCriteria() const
{
  return _scriptInfo.getMatchCandidateCriteria();
}

}
