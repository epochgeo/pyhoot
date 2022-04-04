/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>

#include <tgs/RandomForest/DataFrame.h>

#include <hoot/core/util/Log.h>
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;
using namespace std;
using namespace Tgs;

namespace hoot
{

void init_DataFrame(py::module_& m)
{
  // This is a lazy wrapping of DataFrame. All the functions have been wrapped to some degree but
  // the more difficult functions have been commented out.
  //
  // No new comments have been added but existing hoot comments have been converted to python
  // style docstrings.
  auto wrapme = py::class_<Tgs::DataFrame, std::shared_ptr<DataFrame> >(m, "DataFrame")
    .def("to_list", [](DataFrame& self) {
      vector<py::dict> result;
      result.reserve(self.getNumFactors());
      vector<string> factorLabels = self.getFactorLabels();
      for (unsigned int i = 0; i < self.getNumDataVectors(); i++)
      {
        py::dict row;
        row["class"] = self.getTrainingLabel(i);
        vector<double> rowData = self.getDataVector(i);
        for (size_t j = 0; j < rowData.size(); j++)
        {
          if (self.isNull(rowData[j]))
          {
            row[py::str(factorLabels[j])] = nullptr;
          }
          else
          {
            row[py::str(factorLabels[j])] = rowData[j];
          }
        }
        result.push_back(row);
      }
      return result;
    })
    .def(py::init([]() { return make_shared<DataFrame>(); }))
    .def("addData", [](DataFrame& self, py::buffer b) {
        py::buffer_info info = b.request();

        if (info.format != py::format_descriptor<double>::format())
        {
          throw hoot::HootException("incompatible format, expected doubles");
        }

        if (info.ndim != 2)
        {
          throw hoot::HootException(QString("incompatible dimensions, expected 2").
            arg(info.ndim).arg(self.getActiveFactorCount()));
        }

        int cols = info.shape[1];
        int rows = info.shape[0];

        if (cols != self.getActiveFactorCount())
        {
          throw hoot::HootException(QString("incompatible column count (%1), expected %2").
            arg(cols).arg(self.getActiveFactorCount()));
        }

        double* ptr = static_cast<double*>(info.ptr);
        for (int i = 0; i < rows; i++)
        {
          self.addDataVector("", ptr + cols * i, 1);
        }
      },
R"TOK(
Appends a data vector to the end of the dataframe

:param label: the class label for the training vector
:param dataItem: the data vector to add
:param eventWeight: the weight associated with the data vector
)TOK",
      py::arg("data_array"))
    .def("addDataVector", [](DataFrame& self, const std::string& label,
        const std::vector<double>& dataItem, double eventWeight) {
        self.addDataVector(label, dataItem, eventWeight);
      },
R"TOK(
Appends a data vector to the end of the dataframe

:param label: the class label for the training vector
:param dataItem: the data vector to add
:param eventWeight: the weight associated with the data vector
)TOK",
      py::arg("label"),
      py::arg("data_item"),
      py::arg("event_weight") = 1)
    .def("clear", &DataFrame::clear, R"TOK(
 Resets all the internal data structures associated with data frame
)TOK")
    .def("computeBandwidthByFactor", &DataFrame::computeBandwidthByFactor, R"TOK(
 Computes the Silverman's rule for a set of data vectors values for a single
 factor

:param fIdx: the factor index
:param dataIndices: the data vectors of interest
:param minVal: returns the minimum factor value computed by the function
:param minVal: returns the minimum factor value computed by the function
:param mean: returns the mean factor value computed by the function
:param q1: returns the first quartile
:param q3: returns the third quartile
:returns: the computed bandwidth
)TOK")
    .def("deactivateFactor", &DataFrame::deactivateFactor, R"TOK(
Deactivates the factor by removing its index from the
list of active factor indices

:param factor: the factor to deactivate
)TOK")
    .def("empty", &DataFrame::empty, R"TOK(
 :returns: true is DataFrame contains 0 data vectors
)TOK")
//    .def("exportData", &DataFrame::exportData, R"TOK(
//exportData exports the data to an XML document
//:param modelDoc: the main XML doc object
//:param parentNode: the node to add the data to
//)TOK")
//    .def("exportData", &DataFrame::exportData, R"TOK(
// Export the data frame as XML through to the file stream

//:param fileStream: the output file stream
//:param tabDepth: set of tabs to indent the exported content
//)TOK")
    .def("getActiveFactorCount", &DataFrame::getActiveFactorCount, R"TOK(
getActiveFactorCount
:returns: the number of active factors
)TOK")
    .def("getClassLabels", &DataFrame::getClassLabels, R"TOK(
 Gets the class labels unique to the whole data set

:returns: the class labels
)TOK")
    .def("getClassPopulations", &DataFrame::getClassPopulations, R"TOK(
 Get the number of instances per class based on the subset of data
 vectors represented by the index value within the indices input parameter

 :param indices: a list of data vector indices in the data set
 :param populations: the output map of class names to number of instances
)TOK")
    .def("getClassDistribution", &DataFrame::getClassDistribution, R"TOK(
 Get the number of instances per class based on the subset of data
 vectors represented by the index value within the indices input parameter. This cannot
 be mapped back to the enumerated classes and is provided because it is slightly more
 efficient than the above function.

 :param indices: a list of data vector indices in the data set
 :param populations: the output of number of instances in each class represented
)TOK")
    .def("getDataElement", &DataFrame::getDataElement, R"TOK(
Gets the value of a factor within a data vector
within the data frame

:param vIdx: the vector index
:param fIdx: the factor index
:returns: the requested value

)TOK")
    .def("getWeight", &DataFrame::getWeight,
R"TOK(
Returns the weight for the row
:param vIdx: the vector index
)TOK")
    .def("getDataVector", &DataFrame::getDataVector,
R"TOK(
Gets reference to a single data vector in the data frame

:param vIdx: the vector index
:returns: a reference to the requested vector
)TOK")
    .def("getFactorLabels", &DataFrame::getFactorLabels, R"TOK(
Gets the list of factor labels

:param factors: a container to hold the factor labels
)TOK")
    .def("getFactorTypes", &DataFrame::getFactorTypes)
    .def("getFactorLabelFromIndex", &DataFrame::getFactorLabelFromIndex, R"TOK(
:returns: the number of data vectors in the data set
)TOK")
    .def("getNumDataVectors", &DataFrame::getNumDataVectors,
R"TOK(
:returns: the number of factors in the data set
)TOK")
    .def("getIndexFromFactorLabel", &DataFrame::getIndexFromFactorLabel,
R"TOK(
Gets the index into the factor list based on its string
representation

:param fLabel: the factor label to find the index
:returns: the index into the list of factors
)TOK")
    .def("getFactorLabelFromIndex", &DataFrame::getFactorLabelFromIndex,
R"TOK(
 Gets the factor label corresponding to the factor index

:param fIdx: the index into the list of factors
:returns: the factor label corresponding to the entry in the factor list
)TOK")
    .def("getMajorityTrainingLabel", &DataFrame::getMajorityTrainingLabel, R"TOK(
 Gets the majority class label corresponding to the data set

:param dataSet: the data vector set
:returns: the class label corresponding to the majority of data vectors
)TOK")
    .def("getNullTreatment", &DataFrame::getNullTreatment, R"TOK(
Returns the NullTreatment for a given factor
)TOK")
    .def("getTrainingLabel", &DataFrame::getTrainingLabel, R"TOK(
 Gets the class label corresponding to the data vector index

:param dIdx: the data vector index into the dataset
:returns: the class label corresponding to the data vector
)TOK")
    .def("getTrainingLabelList", &DataFrame::getTrainingLabelList, R"TOK(
getTrainingLabelList
:returns: the list of class labels corresponding to the training data vectors
)TOK")
    .def("hasFactorTypes", &DataFrame::hasFactorTypes, R"TOK(
hasFactorTypes
:returns: true is factor types have been set
)TOK")
    .def("hasNullTreatments", &DataFrame::hasNullTreatments, R"TOK(
hasNullTreatments
:returns: true if null treatment values have been set
)TOK")
//    .def("importFrame", &DataFrame::importFrame, R"TOK(
// Import the data frame from the file stream

//:param fileStream: the input file stream
//)TOK")
//    .def("importFrame", &DataFrame::importFrame, R"TOK(
// Import the data frame

//:param e: a QDomElement containing the contents of tag <DataFrame> from an XML file
//)TOK")
    .def("isDataSetPure", &DataFrame::isDataSetPure, R"TOK(
 Checks to see if the data vectors belonging to the set of indices
are all of the same class
)TOK")
    .def("isNominal", &DataFrame::isNominal, R"TOK(
Returns true if the specified column is nominal.
)TOK")
    .def_static("isNull", &DataFrame::isNull, R"TOK(
Returns true if v is a "null"
)TOK")
    .def("makeBalancedBoostrapAndOobSets", &DataFrame::makeBalancedBoostrapAndOobSets, R"TOK(
 Creates balanced bootstrap and out of bag sets with replacement
based on paper:

C. Chen, et.al. Using Random Forest to Learn Imbalanced Data

:param bootstrap: the output container to hold indices to data vectors for the bootstrap set
:param oob:  the output container to hold indices to data vectors for the out of bag set
)TOK")
    .def("makeBalancedRoundRobinBootstrapAndOobSets", &DataFrame::makeBalancedRoundRobinBootstrapAndOobSets, R"TOK(
 Creates balanced binary bootstrap and out of bag sets with replacement
based on paper:

C. Chen, et.al. Using Random Forest to Learn Imbalanced Data


:param className1: the name of the class to represent the positive class
:param className2: the name of the class to represent the negative class
:param bootstrap: the output container to hold indices to data vectors for the bootstrap set
:param oob:  the output container to hold indices to data vectors for the out of bag set
)TOK")
    .def("makeBoostrapAndOobSets", &DataFrame::makeBoostrapAndOobSets, R"TOK(
 Creates bootstrap and out of bag sets with replacement

:param bootstrap: the output container to hold indices to data vectors for the bootstrap set
:param oob:  the output container to hold indices to data vectors for the out of bag set
)TOK")
    .def_static("null", &DataFrame::null, R"TOK(
Returns what DataFrame considers a null value (NaN in double land).
)TOK")
    .def("remapClassLabels", &DataFrame::remapClassLabels, R"TOK(
Assignment operator, copies all data. Potentially very expensive.
)TOK")
//    DataFrame& operator=(const DataFrame& from);

//R"TOK(
//operator [] provides access to the stored training data vectors
//:param vIdx: the index to the vector of interest
//:returns: a reference to the data vector
//)TOK"
//    std::vector<double> & operator[](unsigned int vIdx);

//R"TOK(
// Remaps all the classes to different labels.  The original class
//labels can be restored using restoreClassLabels;

//:param labelMap: a map of the original class name to a new class name
//)TOK")
    .def("restoreClassLabels", &DataFrame::restoreClassLabels, R"TOK(
Restores the list of class labels from the backup (use after creating binary classes)
)TOK")
    .def("selectRandomFactors", &DataFrame::selectRandomFactors, R"TOK(
Random picks indices of m factors without replacement

:param fIndices: a list of the resulting factor indices that
has already been resized to the number of requested factors
)TOK")
    .def("setAllFactorsActive", &DataFrame::setAllFactorsActive, R"TOK(
Adds all factors to the active factor list.
)TOK")
    .def("setBinaryClassLabels", &DataFrame::setBinaryClassLabels, R"TOK(
Goes through the training label list and renames all classes not matching posClass
to "other"

Use restoreClassLabels to restore to original scheme

:param posClass: the positive class label
)TOK")
    .def("setDataElement", &DataFrame::setDataElement, R"TOK(
Sets the value of a single data element.
)TOK")
    .def("setFactorLabels", &DataFrame::setFactorLabels, R"TOK(
 Copies the factor names into an internal vector (not strictly needed inside the data set)
)TOK")
    .def("setFactorTypes", &DataFrame::setFactorTypes, R"TOK(
Sets the factor type to one of Nominal or Numeric
)TOK")
    .def("setFactorType", &DataFrame::setFactorType, R"TOK(
Sets one factor type to one of Nominal or Numeric
)TOK")
    .def("setNullTreatment", &DataFrame::setNullTreatment, R"TOK(
Set the null treatment to one of NullAsMissingValue or NullAsValue. The exact way that a
null will be treated will depend on the algorithm that operates on the data.
)TOK")
    .def("sortIndicesOnFactorValue", &DataFrame::sortIndicesOnFactorValue, R"TOK(
Sorts a vector of indices to data vectors by the selected factor
value.

:param indices: the input/output containing the data vector indices
:param fIdx: the factor index on the data vector
)TOK")
    .def("validateData", &DataFrame::validateData, R"TOK(
Checks to ensure that there is a value for each factor.  If all values are the
same then the factor is deactivated.
)TOK")
    ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_DataFrame)

}

