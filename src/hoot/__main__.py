# MIT License
# https://opensource.org/licenses/MIT
#
# @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)

import os
import subprocess
import sys

if len(sys.argv) > 3 and sys.argv[1] == "env":
    if sys.argv[2] == "home":
        print(HOOT_HOME)
        exit(0)
    else:
        print("`hoot env home` will print the HOOT_HOME path")
        exit(1)

# Call the hoot command line directly.
binary = str(os.path.join(HOOT_HOME, "bin/hoot"))
print([binary] + sys.argv[1:])
exit(subprocess.run([binary] + sys.argv[1:]).returncode)
