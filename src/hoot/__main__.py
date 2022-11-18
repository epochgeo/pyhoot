# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
"""
__main__ is the command line interface that mostly passes through to hoot's
command line interface.
"""

import os
from os.path import exists, join
import shutil
import subprocess
import sys
from urllib.request import urlretrieve
import zipfile

import hoot

if __name__ == "__main__":
    #print(sys.argv)
    if len(sys.argv) == 3 and sys.argv[1] == "env":
        if sys.argv[2] == "home":
            print(hoot.HOOT_HOME)
            sys.exit(0)
        else:
            print("`hoot env home` will print the HOOT_HOME path")
            sys.exit(1)
    elif len(sys.argv) == 2 and sys.argv[1] == "download-data":
        # Download icudt69l for transliteration
        if exists(join(os.environ["ICU_DATA"], "icudt69l.dat")):
            print("icudt69l.dat already exists, skipping.")
        elif exists("icudt69l.dat"):
            print("Found a local copy of icudt69l.dat, copying to " + \
                  os.environ["ICU_DATA"])
            shutil.copy("icudt69l.dat",
                        join(os.environ["ICU_DATA"], "icudt69l.dat"))
        else:
            print("downloading icudt69l.dat")
            urlretrieve(
                "https://github.com/unicode-org/icu/releases/download/release-69-1/icu4c-69_1-data-bin-l.zip",
                join(os.environ["ICU_DATA"], "icudt69l.zip"))
            with zipfile.ZipFile(join(os.environ["ICU_DATA"], "icudt69l.zip"))\
                as zip_ref:
                zip_ref.extractall(os.environ["ICU_DATA"])
                os.remove(join(os.environ["ICU_DATA"], "icudt69l.zip"))
    
        # download proj.db for projecting data
        if exists(join(os.environ["PROJ_LIB"], "proj.db")):
            print("proj.db already exists, skipping.")
        elif exists("proj.db"):
            print("Found a local copy of proj.db, copying to " + \
                  os.environ["PROJ_LIB"])
            shutil.copy("proj.db", join(os.environ["PROJ_LIB"], "proj.db"))
        else:
            print("downloading proj.db")
            urlretrieve(
                "https://eg-pyhoot.s3.amazonaws.com/resources/data-files-rev1/proj.db",
                join(os.environ["PROJ_LIB"], "proj.db"))
    
        sys.exit(0)
    else:
        # Call the hoot command line directly.
        #BINARY_PATH = str(os.path.join(hoot.HOOT_HOME, "bin/hoot"))
        #sys.exit(subprocess.run([BINARY_PATH] + sys.argv[1:], check=True).
        #         returncode)
        cmd = ""
        if len(sys.argv) >= 2:
            cmd = sys.argv[1]
        args = []
        if len(sys.argv) >= 3:
            args = sys.argv[2:]
        hoot.Command.run(cmd, args)
