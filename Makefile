
VERSION = 0.0.5
FINAL_WHEEL = wheelhouse/hoot-$(VERSION)-cp36-cp36m-manylinux_2_17_x86_64.manylinux2014_x86_64.whl

all: build_wheel

clean:
	rm -rf dist
	rm -rf $(FINAL_WHEEL)
	rm -rf build

install: dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl
	python -m pip install --force dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl

build_wheel: $(FINAL_WHEEL)

$(FINAL_WHEEL): dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl
	auditwheel repair --plat manylinux_2_17_x86_64 dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl

dist/hoot-$(VERSION)-cp36-cp36m-linux_x86_64.whl: $(wildcard src/**/*) Makefile
	rm -rf dist
	python -m build -n

upload: build_wheel
	python3 -m pip install --upgrade twine
	# you can set TWINE_USERNAME & TWINE_PASSWORD to avoid the prompt
	python3 -m twine upload $(FINAL_WHEEL)
    
local:
	rm -rf build
	mkdir build
	cd build && conan install .. && cmake .. && make
