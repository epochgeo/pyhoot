
# pyhoot Developer Instructions

## Installation

Follow the [Hootenanny Conan install instructions](https://github.com/epochgeo/hootenanny-conan#install) 
to install Hootenanny and its dependencies on a CentOS 7 VM.

Install Visual Studio Code and set up a terminal pointing to your VM: 
* Run `vagrant ssh-config` from the directory where you launched the VM.
* Paste the output from the previous command to `~/.ssh/config`. 
* Rename the entry from `default` to something unique.
* Create a terminal connection pointing to the config file entry's name within VS Code.

Then, install pyhoot and run the tests. This will build all the C++ bindings and create a wheel:
```
source /opt/rh/devtoolset-8/enable
export HOOT_HOME=/home/vagrant/pyhoot/build/
export ICU_DATA=/home/vagrant/pyhoot/build/res
export PROJ_LIB=$HOOT_HOME
sudo yum install python-sphinx
pip install numpy wheel patchelf
cd pyhoot
make clean
python -m pip install .
mkdir -p $ICU_DATA
python -m hoot download-data
make -j$(nproc) test
```

To create an installation package:
```
make -j$(nproc) install
```

To test deploy the installation package (see further instructions in Makefile target):
* Update `VERSION` with the new version.
* Update the `setup.py` `setup` method with the new version (TODO: temporary).
* Upload a test version to https://test.pypi.org/project/hoot/<version>
```
make uploadtest
```

To deploy the actual installation package (see further instructions in Makefile target; deploy to 
test repo first to be safe):
* Follow the steps above to update the software version.
* Upload a production version to https://pypi.org/project/hoot/<version>:
```
make uploadfinal
```
