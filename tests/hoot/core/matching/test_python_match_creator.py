# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import unittest

import hoot

class PythonMatchCreatorTest(unittest.TestCase):

    def test_basic(self):
        print("test_basic")
        print(hoot.Version.get_full_version())
