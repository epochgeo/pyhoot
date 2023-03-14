
# pyhoot Developer Instructions

## Installation

Follow the [Hootenanny Conan install instructions](https://github.com/epochgeo/hootenanny-conan#install) 
to install Hootenanny and its dependencies on a CentOS 7 VM.

Install Visual Studio Code and set up a terminal pointing to your VM: 
* Run `vagrant ssh-config` from the directory where you launched the VM.
* Paste the output from the previous command to `~/.ssh/config`. 
* Rename the entry from `default` to something unique.
* Create a terminal connection pointing to the config file entry's name within VS Code.

Then, install pyhoot and run the tests. This will build all the C++ bindings and create a wheel 
file:
```
source ~/.bash_profile
sudo yum install python-sphinx
pip install numpy wheel patchelf auditwheel twine build
cd pyhoot
make clean
mkdir -p $ICU_DATA
python -m hoot download-data
# Running test also forces a download of the words dictionary.
make -j$(nproc) test
python -m pip install .
```

To create an installation package:
```
make -j$(nproc) install
```

To test deploy the installation package:
* Update `VERSION` with the new version.
* Update the `setup.py` `setup` method with the new version (TODO: temporary).
* Update `TWINE_TOKEN` in the Makefile
* Upload a test version to https://test.pypi.org/project/hoot/<version>:
```
make -j$(nproc) uploadtest
```

To deploy the actual installation package (see further instructions in Makefile target:
* Follow the steps above to update the software version.
* Upload a production version to https://pypi.org/project/hoot/<version>:
```
make -j$(nproc) uploadfinal
```
