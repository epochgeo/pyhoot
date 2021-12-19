# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import os

# Make sure we're using the right hoot home.
HOOT_HOME = os.path.join(os.path.abspath(os.path.dirname(__file__)))
os.environ["HOOT_HOME"] = HOOT_HOME

TOY_TEST_A_PATH = os.path.join(HOOT_HOME, "ToyTestA.osm")
TOY_TEST_B_PATH = os.path.join(HOOT_HOME, "ToyTestB.osm")

from .libpyhoot import *
