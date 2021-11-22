
# pyhoot Developer Instructions

## Installation

### Linux

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
