# PyVOL

This is a prototype of generic Python virtual object layer (VOL) for HDF5. It is providing some easily implementable APIs to create new python VOLs.

The library is built upon the [hyperslab_updates](https://bitbucket.hdfgroup.org/projects/HDFFV/repos/hdf5/browse?at=refs%2Fheads%2Fhyperslab_updates) branch of HDF5 (currently under development).

NB: at moment, not all VOL functions are implemented. (All the capabilities of [sci-swift](https://github.com/valiantljk/sci-swift) are currently supported, it is in the roadmap to implement all the functionalities).

### Python part (module [CPyVOL](https://github.com/pierlauro/PyVOL/tree/master/src/python))
In order to develop an easily pluggable python VOL, an [abstract data model](https://github.com/pierlauro/PyVOL/tree/master/src/python/CPyVOL/__init__.py) and one [basic example implementation](https://github.com/pierlauro/PyVOL/tree/master/examples/python_vol/__init__.py) are provided.


### C part
Once implemented a python VOL, it is possible to bind the HDF library on it by simply calling the function [initialize_vol_class](https://github.com/pierlauro/PyVOL/blob/19cb12a7f663f2dd726acdf20daeb383250ff486/src/c/VOL.c#L177) as in the [provided example](https://github.com/pierlauro/PyVOL/blob/19cb12a7f663f2dd726acdf20daeb383250ff486/examples/vol.c#L10).

## Compile and try example

Before running the example, it is needed to install:
- HDF5 (version hyperslabs_updates)
- MPI
- Python3
- NumPy

In alternative, in the [docker folder](https://github.com/pierlauro/PyVOL/blob/master/docker) it is possible to build a container for testing purposes (shipped with HDF5, MPI, Python3 and NumPy). 

In both cases (local or containerized environment), the CPyVol module needs to be installed by following the instructions in the [python folder](https://github.com/pierlauro/PyVOL/blob/master/src/python).

- With Cmake
```bash
mkdir build
cd build
cmake ..
make
./vol python_vol VOL # Usage: ./vol <python_module> <python_class>
```

- With Makefile (NB: review include paths in the Makefile)
```bash
make
cd build
./vol python_vol VOL # Usage: ./vol <python_module> <python_class>
```
