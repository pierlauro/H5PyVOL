__This repository has been archived due to author's change of plans - look at HANDOVER.md for the details that have been given before archiving__

# H5PyVOL

This is a beta version of a generic Python virtual object layer (VOL) for HDF5. It is providing some easily implementable APIs to create new python VOLs.

The library is built upon the [develop](https://bitbucket.hdfgroup.org/projects/HDFFV/repos/hdf5/browse?at=refs%2Fheads%2Fdevelop) branch of HDF5.

NB: at moment, not all VOL functions are implemented. (All the capabilities of [sci-swift](https://github.com/valiantljk/sci-swift) are currently supported, it is in the roadmap to implement all the missing functionalities).

### Python part (module [H5PyVOL](https://github.com/pierlauro/H5PyVOL/tree/master/src/python))
In order to develop an easily pluggable python VOL, an [abstract data model](https://github.com/pierlauro/H5PyVOL/tree/master/src/python/H5PyVOL/__init__.py) and one [basic example implementation](https://github.com/pierlauro/H5PyVOL/tree/master/examples/python_vol/__init__.py) are provided.

### Containerized environment

The [docker folder](https://github.com/pierlauro/H5PyVOL/blob/master/docker) contains instructions to build a container for testing purposes (shipped with all dependencies). All the project's docker images - including one client image for each supported object store - can be built by executing the script [docker-build.sh](https://github.com/pierlauro/H5PyVOL/blob/master/docker-build.sh).

## Install

#### Prerequisites
- HDF5 (develop version)
- MPI (recommended: mpich)
- Python 3.7
- NumPy

The H5PyVOL plugin will be installed in the path specified by the environment variable `$HDF5_PLUGIN_PATH` if set, otherwise in the HDF5 plugin default directory (`/usr/local/hdf5/lib/plugin/`). Make sure the install path is writable.

#### Cmake install (version >= 3.15)
```bash
mkdir build &&
cd build &&
cmake .. &&
make install
```

#### Makefile install (NB: review include paths in the Makefile)
```bash
make &&
make install
```
The `H5PyVol` module can be installed by following the instructions in the [python folder](https://github.com/pierlauro/H5PyVOL/blob/master/src/python).

## Usage
Once installed both plugin and python package, is it needed to set the following environment variables:
- `HDF5_VOL_CONNECTOR='H5PyVOL'`
- `H5PyVOLModule='package_name_of_developed_VOL'`
- `H5PyVOLClass='class_name_of_developed_VOL'`

### Demo
[Example](https://github.com/pierlauro/H5PyVOL/tree/master/examples/vol.c) with an in-memory [simple example implementation](https://github.com/pierlauro/H5PyVOL/tree/master/examples/python_vol/__init__.py).

#### After installation with Cmake (version >= 3.15)
```bash
cd build
export HDF5_VOL_CONNECTOR='H5PyVOL'
export H5PyVOLModule='python_vol'
export H5PyVOLClass='VOL'
./vol
```

#### After installation with Makefile
```bash
make apps
cd build
export HDF5_VOL_CONNECTOR='H5PyVOL'
export H5PyVOLModule='python_vol'
export H5PyVOLClass='VOL'
./vol
```
