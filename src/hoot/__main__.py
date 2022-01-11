# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
"""
__main__ is the command line interface that mostly passes through to hoot's
command line interface.
"""

import os
import subprocess
import sys

import hoot

if len(sys.argv) > 3 and sys.argv[1] == "env":
    if sys.argv[2] == "home":
        print(hoot.HOOT_HOME)
        sys.exit(0)
    else:
        print("`hoot env home` will print the HOOT_HOME path")
        sys.exit(1)

# Call the hoot command line directly.
BINARY_PATH = str(os.path.join(hoot.HOOT_HOME, "bin/hoot"))
sys.exit(subprocess.run([BINARY_PATH] + sys.argv[1:], check=True).returncode)
