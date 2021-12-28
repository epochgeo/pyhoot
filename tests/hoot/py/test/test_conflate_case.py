# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import unittest

import hoot

class TestConflateCase(unittest.TestCase):

    def test_basic(self):
        hoot.Log.get_instance().set_level(hoot.Log.WARN)
        result = hoot.ConflateCaseTestSuite.run_dir("test-files/cases")
        print("Done!")
        self.assertTrue(result)
