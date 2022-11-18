# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
"""
pyhoot is an unofficial wrapper for Hootenanny.

Hootenanny is an open source map data conflation tool developed with machine
learning techniques to facilitate automated and semi-automated conflation of
critical Foundation GEOINT features in the topographic domain. In short, it
merges multiple maps into a single seamless map.

Use help(hoot.libpyhoot) for a complete list of wrapped classes.
"""

import os
from os.path import exists, join

# Make sure we're using the right hoot home.
if "HOOT_HOME" in os.environ and os.environ["HOOT_HOME"].strip() != "":
    HOOT_HOME = os.environ["HOOT_HOME"]
else:
    HOOT_HOME = os.path.join(os.path.abspath(os.path.dirname(__file__)))
    os.environ["HOOT_HOME"] = HOOT_HOME
#print("HOOT_HOME: " + HOOT_HOME)

# Point ICU data to the hoot conf directory
if "ICU_DATA" not in os.environ:
    os.environ["ICU_DATA"] = os.path.join(HOOT_HOME, "conf")

# Point proj.db data to the hoot directory
if "PROJ_LIB" not in os.environ:
    os.environ["PROJ_LIB"] = HOOT_HOME

if not exists(join(os.environ["ICU_DATA"], "icudt69l.dat")) or \
    not exists(join(os.environ["PROJ_LIB"], "proj.db")):
    print("""
It appears that one or more data files are missing. To download the data files
run:
    python -m hoot download-data
""")

# We have to ensure the environment is set properly before importing libpyhoot
# pylint: disable=wrong-import-position
try:
    from .libpyhoot import * # noqa
except:
    from hoot.libpyhoot import *
from .utils import * # noqa
from .hoot_pythonic import * # noqa

TOY_TEST_A_PATH = os.path.join(HOOT_HOME, "ToyTestA.osm")
TOY_TEST_B_PATH = os.path.join(HOOT_HOME, "ToyTestB.osm")