# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import unittest

import hoot


class ExampleGenericPoi:

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

    @staticmethod
    def register():
        example = ExampleGenericPoi()

        creator = hoot.PythonCreatorDescription()
        creator.description.set_class_name(ExampleGenericPoi.__name__)
        creator.search_radius = 5
        creator.criteria = ["PoiCriterion"]
        creator.init_function = example.init
        creator.is_match_candidate_function = example.is_match_candidate
        creator.match_score_function = example.match_score
        creator.merge_pair_function = example.merge_pair

        hoot.PythonMatchCreator.register_creator(creator)
        hoot.PythonMergerCreator.register_creator(creator)


class TestGenericPoi(unittest.TestCase):

    def setUp(self):
        hoot.TestUtils.reset_all()

    def tearDown(self):
        hoot.TestUtils.reset_all()

    def test_basic(self):
        hoot.Log.get_instance().set_level(hoot.Log.WARN)

        # Enable linear programming optimization to avoid an obscure bug
        hoot.conf()["unify.enable.optimal.constrained.matches"] = True

        ExampleGenericPoi.register()

        result = hoot.ConflateCaseTestSuite.run_dir("test-files/generic-poi")
        self.assertTrue(result)
