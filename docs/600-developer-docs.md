
# pyhoot Developer Instructions

## Installation

### Linux

If you haven't already, install pyenv:

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

Install CentOS requirements:

```
curl -sL https://rpm.nodesource.com/setup_14.x | sudo bash -
# Add an upgrade version of git for pydoc-markdown
sudo yum -y install https://packages.endpointdev.com/rhel/7/os/x86_64/endpoint-repo.x86_64.rpm
sudo yum install -y centos-release-scl && sudo yum update -y
sudo yum install -y git devtoolset-8-gcc devtoolset-8-gcc-c++ libSM libX11 
# Start using the gcc 8 tools, you'll have to do this each time you start a new shell
source /opt/rh/devtoolset-8/enable

# if you want to build docs...
sudo yum install -y pandoc texlive-latex-bin-bin texlive-*.noarch
```

#### Ubuntu 20.04

Below are mostly notes and it is not currently not being maintained.

##### Build Hootenanny

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

#### Start using python environment

Create a virtual environment & install pyhoot:

```
virtualenv -p python3.6 venv
# run this every time you start a new prompt
source venv/bin/activate
```

#### Build pyhoot Bindings

This will build all the C++ bindings and create a wheel:

```
make
# you only need to run this once or when deps change
pip install -e .[dev]
```
