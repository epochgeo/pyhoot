"""
cpp_to_pybind11 contains a collection of crazy collection of regex to convert from typically
commented C++ code into a set of .def commands for pybind11.

This is simply intended to aid the process and won't catch everything. Please double check the
results.
"""

import re
import sys

if len(sys.argv) != 3:
    print("python cpp_to_pybind11.py MyClass.h MyClass")

code = open(sys.argv[1], "r").read() + "\n"

class_name = sys.argv[2]

code = re.sub(r"""(?s) +/\*\*""", "R\"TOK(", code)
code = re.sub(r"""(?ms) +\*/""", ')TOK"', code)
code = re.sub(r"(?ms)^ +\* ?", "", code)
code = re.sub(r"(?ms)(R\"TOK.*?TOK\")?\s* +(virtual )?(static)? *((const )?[a-zA-Z_:<>]+[&]*) (\w+)\(.*?[;|}]\s*\n",
    rf"""    .def_\3("\6", &{class_name}::\6, \1)\n""", code)
code = re.sub(r"""def_\(""", """def(""", code)
code = re.sub(r""", \)""", """)""", code)
code = re.sub(r"""(?ms)@param +([^ ]+)""", r":param \1:", code)
code = re.sub(r"""(?ms)@brief +""", "", code)
code = re.sub(r"""@return """, """:returns: """, code)
code = re.sub(r"""\n"\);""", """"\\);""", code)
code = re.sub(r""",R"\s*\n""", """,\nR\"""", code)

print(code)
