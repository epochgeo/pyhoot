# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import os
import subprocess
import sys

home = os.path.join(os.path.abspath(os.path.dirname(__file__)))

if len(sys.argv) > 3 and sys.argv[1] == "env":
    if sys.argv[2] == "home":
        print(home)
        exit(0)
    else:
        print("`hoot env home` will print the HOOT_HOME path")
        exit(1)

# Call the hoot command line directly.
binary = str(os.path.join(os.path.abspath(os.path.dirname(__file__)), "bin/hoot"))
print([binary] + sys.argv[1:])
exit(subprocess.run([binary] + sys.argv[1:]).returncode)
