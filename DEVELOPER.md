
# pyhoot Developer Instructions

## Installation

### Linux

If you haven't already, install pyenv

```
git clone https://github.com/pyenv/pyenv.git ~/.pyenv
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bash_profile
echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bash_profile 
```

Add external conan deps:

```
conan remote add sintef https://artifactory.smd.sintef.no/artifactory/api/conan/conan-local
```

#### CentOS 7

```
curl -sL https://rpm.nodesource.com/setup_14.x | sudo bash -
sudo yum install -y centos-release-scl && sudo yum update -y
sudo yum install -y git devtoolset-8-gcc devtoolset-8-gcc-c++ libSM libX11 
# Start using the gcc 8 tools, you'll have to do this each time you start a new shell
source /opt/rh/devtoolset-8/enable
```

#### Start using python environment

```
pipenv shell
pipenv install --dev
```

#### Build the Package

```
python -m build -n
```

### Ubuntu 20.04

#### Build Hootenanny

```
sudo apt install libgtk2.0-dev libglpk-dev libstxxl-dev libphonenumber-dev liboauth-dev
```

Hmm. Probably not relevant

```
sudo apt install python2-dev libopencv-dev libglpk-dev libnode-dev libqt5sql5-psql qt5-qmake-bin qt5-default
automake --add-missing
autoreconf
autoconf && automake && ./configure --with-services=no CPPFLAGS=-I/usr/include/opencv4 PYTHON_VERSION=2
```
