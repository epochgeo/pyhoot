
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

To see a complete list of wrapped code type this from the command line:

```
python -c "import hoot; help(hoot.libpyhoot)"
```

Where appropriate conventions are converted from Hoot's c++ coding standard to typical Python
conventions. E.g. the method `getChildWeight()` is converted either to `get_child_weight()` or
a property named `child_weight`.

## Bugs

BEWARE: due to the early stages of this implementation, nearly no testing is run on this build of
hoot. While we're using hoot source code, we may be using different versions of libraries which
can sometimes have unexpected side effects. If you're running into a strange issue or crashes this
is most likely due to pyhoot and should be reported to the pyhoot github first and we will
escalate to the main hoot repo if needed.

As/if pyhoot matures and regression tests are put into place, these issues will go away.

Known Issues:

1. GLPK gives an unexpected segfault so GLPK based optimization is disabled by default.
2. HOOT_HOME is not being properly set in every environment. On Amazon Linux set it with:
```
export HOOT_HOME=/home/ec2-user/.local/lib/python3.7/site-packages/hoot
```
3. pyhoot is built from Hootenanny 0.2.64. Upgrading to a later version of Hootenanny is not a 
trivial process, so regular upgrades are not currently planned but may be possible in the future.

## Installation

At this time, pyhoot is available for Python 3.7.

Installing on CentOS 7:

```
sudo yum install libSM libX11 libXext libXrender
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
help(hoot.libpyhoot)
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
hoot.log_var(tags.getName())
```

Command Line Interface
----------------------

The Hootenanny CLI is conveniently wrapped in a python call:

```
python -m hoot conflate $HOOT_HOME/ToyTestA.osm $HOOT_HOME/ToyTestB.osm out.osm
```

## Development Environment

https://github.com/epochgeo/pyhoot/blob/main/docs/600-developer-docs.md
