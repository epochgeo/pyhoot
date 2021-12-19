
# Hootenanny

These are the unofficial Python bindings for
[Hootenanny](https://github.com/ngageoint/hootenanny).

> Hootenanny is an open source map data conflation tool developed with machine learning 
> techniques to facilitate automated and semi-automated conflation of critical Foundation 
> GEOINT features in the topographic domain. In short, it merges multiple maps into a single
> seamless map.

To call this alpha software would be generous. This wrapper aims to slowly wrap the parts of hoot
that are requested and no more. A 1:1 mapping will be maintained where possible while accounting
for Python conventions (e.g. snake_case). If you need a specific feature, please head on over to
our [GitHub repo](https://github.com/epochgeo/pyhoot) and let us know.

## Bugs

BEWARE: due to the early stages of this implementation, nearly no testing is run on this build of
hoot. While we're using hoot source code, we may be using different versions of libraries which
can sometimes have unexpected side effects. If you're running into a strange issue or crashes this
is most likely due to pyhoot and should be reported to the pyhoot github first and we will
escalate to the main hoot repo if needed.

As pyhoot matures and regression tests are put into place, these issues will go away.

Known Issues:

1. GLPK gives an unexpected segfault so GLPK based optimization is disabled by default.

## Installation

At this time, pyhoot is only available for Python 3.6.

Installing on CentOS 7:

```
sudo yum install libSM libX11 
python3 -m pip install hoot
```

## Example

The following python example conflates two sample files that come with pyhoot and writes the result
to `out.osm`.

```
import hoot

hoot.ConflateExecutor().conflate(hoot.TOY_TEST_A_PATH, hoot.TOY_TEST_B_PATH, "out.osm")
```

## Documentation

To see what classes and functions are available via pyhoot, use Python's help:

```
import hoot
help(hoot)
```

Please see the [Hootenanny documentation](https://github.com/ngageoint/hootenanny/raw/master/docs/HootenannyUserGuide.pdf)
for detailed usage instructions.

pyhoot uses the same names but converts them to python style conventions. E.g. snake_case for
functions.

For example, this C++ code:

```
Tags tags;
tags.set("name", "foo");
LOG_VAR(tags.getName());
```

Is equivalent to the following Python:

```
import hoot
tags = hoot.Tags()
tags["name"] = "foo"
print(tags.get_name())
```

Command Line Interface
----------------------

The Hootenanny CLI is conveniently wrapped in a python call:

```
python -m hoot help
```
