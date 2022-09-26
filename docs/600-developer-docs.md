
# pyhoot Developer Instructions

## Installation

Follow the [Hootenanny Conan install instructions](https://github.com/epochgeo/hootenanny-conan#install) to install dependencies.

Then, install pyhoot and run the tests. This will build all the C++ bindings and create a wheel:
```
source /opt/rh/devtoolset-8/enable
export HOOT_HOME=/home/vagrant/pyhoot/build/
export ICU_DATA=/home/vagrant/pyhoot/build/res
cd pyhoot
make
# you only need to run this once or when deps change
pip install -e .[dev]
python -m hoot download-data
make -j$(nproc) test
```

Optionally, you can install Visual Studio Code and set up a terminal pointing to your py hoot VM: 
* Run `vagrant ssh-config` from the directory where you launched the pyhoot VM.
* Paste the output from the previous command to `~/.ssh/config`. 
* Rename the entry from `default` to something unique.
* Create a terminal connection pointing to the config file entry's name within VS Code.
