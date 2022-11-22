
#
# This makefile contains a number of utility methods for developing and 
# maintaining pyhoot. E.g. build, update on pypi, etc.
#

VERSION = $(shell cat VERSION)
FINAL_WHEEL = wheelhouse/hoot-$(VERSION)-cp37-cp37m-manylinux_2_17_x86_64.manylinux2014_x86_64.whl

all: build_wheel

.force:

clean:
	rm -rf dist
	rm -rf $(FINAL_WHEEL)
	rm -rf build
	rm -f .quick .installquick .install
	rm -f conanbuildinfo*
	rm -f conan.lock
	$(MAKE) -C sphinx clean

build_wheel: $(FINAL_WHEEL)

# Run pyhoot unit tests on a local build of pyhoot.
test: local build/conf/dictionary/words.sqlite
	HOOT_HOME=`pwd`/build PYTHONPATH=`pwd`/build/lib/:`pwd`/src/ \
	python -W ignore -m unittest discover -s tests/hoot/py

docs: docs/PyHootManual.pdf

docs/PyHootManual.pdf: docs/710_api_documentation.md
	cd docs; pandoc \
	--number-sections \
	--toc \
	-V colorlinks \
	-V links-as-notes \
	*.md --output PyHootManual.pdf

# The configuration for this is in sphinx/
docs/710_api_documentation.md: .force
	$(MAKE) -C sphinx markdown
	cp sphinx/_build/markdown/hoot.md docs/710_api_documentation.md

# do a quick install that won't test the final version
quick: ._quick
._quick: dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl
	python -m pip install --force dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl
	touch .quick

# build and install a "quick" wheel. This uses references to local libraries.
installquick: ._installquick
._installquick: ._quick
	python -m pip install --force dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl
	touch .installquick

# install the production wheel locally
install: ._install
._install: $(FINAL_WHEEL)
	python -m pip install --force $(FINAL_WHEEL)
	touch .install

# TODO: HOOT_HOME must be set to manually to 
# "~/.pyenv/versions/3.7.14/lib/python3.7/site-packages/hoot" on my box for this to work. - BDW
testfinal: ._install
	python -m hoot conflate $(HOOT_HOME)/ToyTestA.osm $(HOOT_HOME)/ToyTestA.osm ToyTestOut.osm
	python -W ignore -m unittest discover -s tests/hoot/py

$(FINAL_WHEEL): dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl
    # For some reason it can't find libjvm w/o LD_LIBRARY_PATH being specified.
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/jvm/java/jre/lib/amd64/server/ auditwheel repair --plat manylinux_2_17_x86_64 dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl

dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl: $(wildcard src/**/*) README.md
	rm -rf dist
	python -m build -n
	twine check dist/*

uploadtest: ${FINAL_WHEEL}
#   Don't need HootTest in production. The executable is being removed in setup.py but couldn't find
#   anywhere else to remove the library than here, since its needed to run tests locally.
	zip -d $(FINAL_WHEEL) "hoot.libs/libHootTest*.so"
	python3 -m pip install --upgrade twine
	# Set TWINE_TOKEN to the giant token assigned by test.pypi.org. It starts
	# with pypi-
	# See https://packaging.python.org/en/latest/tutorials/packaging-projects/
	# for details
	# To install use:
	# python -m pip install --index-url https://test.pypi.org/simple/ hoot --upgrade --force
	python3 -m twine upload -u __token__ -p $$TWINE_TOKEN --repository testpypi $(FINAL_WHEEL)
	
uploadfinal: ${FINAL_WHEEL}
	python3 -m pip install --upgrade twine
	# you can set TWINE_USERNAME & TWINE_PASSWORD to avoid the prompt
	#python3 -m twine upload $(FINAL_WHEEL)
	python3 -m twine upload -u __token__ -p $$TWINE_TOKEN $(FINAL_WHEEL)

unzipfinal: $(FINAL_WHEEL)
	rm -rf tmp/unzipfinal
	unzip $(FINAL_WHEEL) -d tmp/unzipfinal

unzipquick: .quick
	rm -rf tmp/unzip
	unzip dist/hoot-$(VERSION)-cp37-cp37m-linux_x86_64.whl -d tmp/unzip

local: src/hoot/libpyhoot.so

src/hoot/libpyhoot.so: build/lib/libpyhoot.so
	cp build/lib/libpyhoot.so src/hoot/

build: conanfile.txt
	mkdir build
	cd build && conan install ..

build/Makefile: build CMakeLists.txt
	cd build && cmake ..

build/conf/dictionary/words.sqlite: build
	mkdir -p build/conf/dictionary
	cp -u /tmp/words.sqlite build/conf/dictionary/words.sqlite || \
	curl https://hoot-support.s3.amazonaws.com/words1.sqlite.bz2 | \
	bunzip2 > $@

build/lib/libpyhoot.so: build/Makefile .force
	$(MAKE) -C build
