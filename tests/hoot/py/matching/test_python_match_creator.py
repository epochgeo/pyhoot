# The original code by Maxar/NGA is licensed under GPLv3.
# 
# All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
# GPLv3 license.
#
# --------------------------------------------------------------------
#
# @copyright Copyright (C) 2015-2021 Maxar (http://www.maxar.com/)
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import unittest

import hoot


class SimpleNameConflator:

    def init(self, osmMap):
        print("init!")

    def is_match_candidate(self, osmMap, element):
        return True

    def match_score(self, map, element1, element2):
        return hoot.MatchClassification(1, 0, 0)

    def merge_pair(self, map, element1, element2):
        new_tags = hoot.TagMergerFactory.merge_tags(element1.get_tags(),
                                                    element2.get_tags())
        element1.set_tags(new_tags)
        element1.set_status(hoot.Status.CONFLATED)

        hoot.ReplaceElementOp(element1.get_element_id(),
                              element2.get_element_id()).apply(map)
        hoot.RecursiveElementRemover(element2.get_element_id()).apply(map)
        return element1


class PythonMatchCreatorTest(unittest.TestCase):

    def test_basic(self):

        hoot.Log.get_instance().set_level(hoot.Log.WARN)

        foo = SimpleNameConflator()
        hoot.OsmMap.reset_counters()

        # Enable linear programming optimization to avoid an obscure bug
        hoot.conf()["unify.enable.optimal.constrained.matches"] = True
        hoot.conf()["debug.maps.write"] = True

        creator = hoot.PythonCreatorDescription()
        creator.criteria = ["PoiCriterion"]
        creator.description.set_class_name("SimpleNameConflator")
        creator.search_radius = 5
        creator.init_function = foo.init
        creator.is_match_candidate_function = foo.is_match_candidate
        creator.match_score_function = foo.match_score
        creator.merge_pair_function = foo.merge_pair

        hoot.PythonMatchCreator.register_creator(creator)
        hoot.PythonMergerCreator.register_creator(creator)

        hoot.conf().set("match.creators",
                        f"PythonMatchCreator,{SimpleNameConflator.__name__}")
        hoot.conf().set("merger.creators",
                        f"PythonMergerCreator,{SimpleNameConflator.__name__}")

        osm_map = hoot.OsmMap()

        json1 = """
{
    "version": 0.6,
    "generator": "Overpass API",
    "osm3s": {
        "timestamp_osm_base": "date",
        "copyright": "c 1999"
    },
    "elements": [
        {
            "type": "node",
            "id": -1,
            "lat": 2.0,
            "lon": -3.000001,
            "tags": {
                "name": "foo"
            }
        }
    ]
}
"""

        json2 = """
{
    "version": 0.6,
    "generator": "Overpass API",
    "osm3s": {
        "timestamp_osm_base": "date",
        "copyright": "c 1999"
    },
    "elements": [
        {
            "type": "node",
            "id": -1,
            "lat": 2.000001,
            "lon": -3.0,
            "tags": {
                "name": "bar"
            }
        }
    ]
}
"""

        reader = hoot.OsmJsonReader()
        reader.set_use_data_source_ids(False)

        # match one feature against itself.
        reader.set_default_status(hoot.Status(hoot.Status.UNKNOWN2))
        reader.load_from_string(json2, osm_map)

        reader.set_default_status(hoot.Status(hoot.Status.UNKNOWN1))
        reader.load_from_string(json1, osm_map)

        hoot.UnifyingConflator().apply(osm_map)

        hoot.MapProjector.project_to_wgs84(osm_map)

        expected = """
{
    "version": 0.6,
    "generator": "Overpass API",
    "osm3s": {
        "timestamp_osm_base": "date",
        "copyright": "c 1999"
    },
    "elements": [
        {
            "type": "node",
            "id": -2,
            "lat": 2.0,
            "lon": -3.000001,
            "tags": {
                "name": "foo",
                "alt_name": "bar"
            }
        }
    ]
}
"""
        expected_map = hoot.load_json(expected,
                                      default_status=hoot.Status.CONFLATED)
        print(hoot.to_json(osm_map))
        self.assertTrue(hoot.MapComparator().is_match(osm_map, expected_map))
