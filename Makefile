
VERSION = $(shell cat VERSION)
FINAL_WHEEL = wheelhouse/hoot-$(VERSION)-cp36-cp36m-manylinux_2_17_x86_64.manylinux2014_x86_64.whl

all: build_wheel

.force:

clean:
	rm -rf dist
	rm -rf $(FINAL_WHEEL)
	rm -rf build
	rm -f .quick .installquick .install

build_wheel: $(FINAL_WHEEL)

test: local
	HOOT_HOME=`pwd`/build PYTHONPATH=`pwd`/build/lib/:`pwd`/src/ \
        python -m unittest discover -s tests.hoot

# do a quick install that won't test the final version
quick: ._quick
._quick: dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl
	python -m pip install --force dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl
	touch .quick

installquick: ._installquick
._installquick: ._quick
	python -m pip install --force dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl
	touch .installquick

install: ._install
._install: $(FINAL_WHEEL)
	python -m pip install --force $(FINAL_WHEEL)
	touch .install

testfinal: ._install
	python -m hoot conflate tmp/ToyTestA.osm tmp/ToyTestA.osm tmp/ToyTestOut.osm
	python -m unittest discover -s tests.hoot

$(FINAL_WHEEL): dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl
	auditwheel repair --plat manylinux_2_17_x86_64 dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl

dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl: $(wildcard src/**/*) README.md
	rm -rf dist
	python -m build -n
	twine check dist/*

uploadtest: ${FINAL_WHEEL}
	python3 -m pip install --upgrade twine
	# Set TWINE_TOKEN to the giant token assigned by test.pypi.org. It starts with pypi-
	# See https://packaging.python.org/en/latest/tutorials/packaging-projects/ for details
	# To install use: python -m pip install --index-url https://test.pypi.org/simple/ hoot --upgrade --force
	python3 -m twine upload -u __token__ -p $$TWINE_TOKEN --repository testpypi $(FINAL_WHEEL)
	
uploadfinal: ${FINAL_WHEEL}
	python3 -m pip install --upgrade twine
	# you can set TWINE_USERNAME & TWINE_PASSWORD to avoid the prompt
	python3 -m twine upload $(FINAL_WHEEL)

unzipfinal: $(FINAL_WHEEL)
	rm -rf tmp/unzipfinal
	unzip $(FINAL_WHEEL) -d tmp/unzipfinal

unzipquick: .quick
	rm -rf tmp/unzip
	unzip dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl -d tmp/unzip

local: src/hoot/libpyhoot.so

src/hoot/libpyhoot.so: build/lib/libpyhoot.so
	cp build/lib/libpyhoot.so src/hoot/

build/lib/libpyhoot.so: .force
	cd build && $(MAKE)

build/Makefile: conanfile.txt CMakeLists.txt
	cd build && conan install .. && cmake ..

