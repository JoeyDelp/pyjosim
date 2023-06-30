# JoSIM Python Interface
## Prerequisites
- A working C++ compiler with C++17 support
- Python 3.6 or newer
- Pip 10 or newer
- CMake 3.13 or newer

#### Hints
- Microsoft Visual Studio Community is [free](https://visualstudio.microsoft.com/vs/community/)
- Python for any system can easily be handled using [pyenv](https://github.com/pyenv/pyenv) or [pyenv-win](https://github.com/pyenv-win/pyenv-win)
- CMake can be installed with Python package installer pip.

## Installation
```bash
$ git clone https://github.com/JoeyDelp/pyjosim.git
$ pip install ./pyjosim
```

## Verify
```bash
$ python -c "import pyjosim; print(pyjosim.__doc__)"
JoSIM python interface
```

## Changelog
### v2.6.1 - 30/06/2023
- Updated to support JoSIM v2.6.6 with seperated KLU and SLU

### v2.6 - 27/01/2022
- Updated readme documentation
- Updated pybind11 interface
- Updated code to work with latest JoSIM v2.6
- Improved installation compatibility to work cross-platform

## Acknowledgments
- Original code by Dr. Paul le Roux
- [CMake C Package Manager](https://github.com/cpm-cmake/CPM.cmake)
- [pybind11](https://github.com/pybind/pybind11)