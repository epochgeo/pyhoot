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
import numpy as np

import hoot

class SimpleNameConflator:

    def is_match_candidate(self, osmMap, element):
        return True

    def extract_features(self, osm_map, elements1, elements2):
        df = hoot.DataFrame()
        ignored = np.zeros(shape=(len(elements1),), dtype=bool)
        return (df, ignored)

    def match_score(self, map, element1, element2, df):

        MATCHI = 0
        MISSI = 1
        REVIEWI = 2

        result = np.zeros((len(element1), 3))
        result[0, MATCHI] = 1
        result[0, MISSI] = 0
        result[0, REVIEWI] = 0
        reasons = ["todo"] * len(element1)
        return (result, reasons)

    # TODO: This can probably be moved to a util method.
    def merge_pair(self, map, element1, element2):

        # element1 doesn't necessarily have status=Unknown1.
        keep_element = element1
        discard_element = element2
        if element1.get_status() == hoot.Status.UNKNOWN2:
            keep_element = element2
            discard_element = element1

        new_tags = hoot.TagMergerFactory.merge_tags(keep_element.get_tags(),
                                                    discard_element.get_tags())
        keep_element.set_tags(new_tags)
        keep_element.set_status(hoot.Status.CONFLATED)

        hoot.ReplaceElementOp(discard_element.get_element_id(),
                              keep_element.get_element_id()).apply(map)
        hoot.RecursiveElementRemover(discard_element.get_element_id()).apply(map)
        return keep_element

class PythonMatchCreatorTest(unittest.TestCase):

    def test_basic(self):

        hoot.Log.get_instance().set_level(hoot.Log.WARN)
        hoot.warn("PythonMatchCreatorTest")

        foo = SimpleNameConflator()
        hoot.OsmMap.reset_counters()

        # Enable linear programming optimization to avoid an obscure bug
        hoot.conf()["unify.enable.optimal.constrained.matches"] = "true"
        #hoot.conf()["debug.maps.write"] = True
        hoot.conf()["tag.merger.default"] = "OverwriteTag2Merger"

        creator = hoot.PythonCreatorDescription()
        creator.criterion = hoot.PoiCriterion()
        creator.description.set_class_name("SimpleNameConflator")
        creator.search_radius = 5
        creator.is_match_candidate = foo.is_match_candidate
        creator.extract_features = foo.extract_features
        creator.match_score = foo.match_score
        creator.merge_pair = foo.merge_pair

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
        reader.set_default_status(hoot.Status(hoot.Status.UNKNOWN1))
        reader.load_from_string(json1, osm_map)
        reader.set_default_status(hoot.Status(hoot.Status.UNKNOWN2))
        reader.load_from_string(json2, osm_map)

        #hoot.warn("loaded map: " + osm_map.to_json())

        hoot.MapProjector.project_to_planar(osm_map)
        
        hoot.info(hoot.UnifyingConflator().get_name())
        hoot.UnifyingConflator().apply(osm_map)

        hoot.MapProjector.project_to_wgs84(osm_map)

        #hoot.warn("conflated map: " + osm_map.to_json())

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
            "id": -1,
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
        #hoot.warn("expected map: " + expected_map.to_json())
        self.assertTrue(hoot.MapComparator().is_match(osm_map, expected_map))
