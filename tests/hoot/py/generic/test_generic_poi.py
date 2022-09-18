# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import unittest
import numpy as np

import hoot

class ExampleGenericPoi:

    # TODO: methods here duplicated from SimpleNameConflator

    def is_match_candidate(self, osmMap, element):
        return True

    def extract_features(self, osm_map, elements1, elements2):
        df = hoot.DataFrame()
        ignored = np.zeros(shape=(1,), dtype=np.bool)
        return (df, ignored)

    def match_score(self, map, element1, element2, df):

        MATCHI = 0
        MISSI = 1
        REVIEWI = 2

        result = np.zeros((len(element1), 3))
        # force a match
        for i in range(len(element1)):
            result[i, MATCHI] = 1
            result[i, MISSI] = 0
            result[i, REVIEWI] = 0
        reasons = ["todo"] * len(element1)
        return (result, reasons)

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

    def get_search_radius(self, element):
        return 250.0

    @staticmethod
    def register():
        example = ExampleGenericPoi()

        creator = hoot.PythonCreatorDescription()
        creator.description.set_class_name(ExampleGenericPoi.__name__)
        creator.criterion = hoot.PoiCriterion()
        creator.is_match_candidate = example.is_match_candidate
        creator.match_score = example.match_score
        creator.merge_pair = example.merge_pair
        creator.extract_features = example.extract_features
        # Could also do this: creator.search_radius = 5
        creator.search_radius_function = example.get_search_radius

        hoot.PythonMatchCreator.register_creator(creator)
        hoot.PythonMergerCreator.register_creator(creator)

        hoot.conf().set("match.creators", 
                        f"PythonMatchCreator,{ExampleGenericPoi.__name__}")
        hoot.conf().set("merger.creators",
                        f"PythonMergerCreator,{ExampleGenericPoi.__name__}")

class TestGenericPoi(unittest.TestCase):

    def setUp(self):
        hoot.TestUtils.reset_all()

    def tearDown(self):
        hoot.TestUtils.reset_all()

    def test_basic(self):

        hoot.Log.get_instance().set_level(hoot.Log.WARN)

        # Enable linear programming optimization to avoid an obscure bug
        hoot.conf()["unify.enable.optimal.constrained.matches"] = True
        #hoot.conf()["debug.maps.write"] = True
        # This doesn't seem to be getting set. Would like to be able retain all ID's.
        #hoot.conf()["conflate.use.data.source.ids.2"] = True

        ExampleGenericPoi.register()

        result = hoot.ConflateCaseTestSuite.run_dir("test-files/generic-poi/poi-generic-1")
        self.assertTrue(result)
