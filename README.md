# PyVOL

This is an embryonic prototype of generic Python virtual object layer (VOL) for HDF5. It is providing some easily implementable APIs to create new python VOLs.

NB: at moment, not all VOL functions are implemented.

### Python part
In order to develop an easily pluggable python VOL, an [abstract data model](https://github.com/pierlauro/PyVOL/tree/master/src/python_vol/abstract.py) and one [basic example implementation](https://github.com/pierlauro/PyVOL/tree/master/src/python_vol/__init__.py) are provided.


### C part
Once implemented a python VOL, it is possible to bind the HDF library on it by simply calling the function [initialize_vol_class](https://github.com/pierlauro/PyVOL/blob/d7ee5a2f901e0890b3c21cc0342574b08190bbfd/src/VOL.c#L173) as in [the provided example](https://github.com/pierlauro/PyVOL/blob/d7ee5a2f901e0890b3c21cc0342574b08190bbfd/examples/vol.c#L10).


## Compile and try example
The example is built upon the [hyperslab_updates](https://bitbucket.hdfgroup.org/projects/HDFFV/repos/hdf5/browse?at=refs%2Fheads%2Fhyperslab_updates) branch of HDF5.

A precompiled version can be used by building the attached [Dockerfile](https://github.com/pierlauro/PyVOL/blob/master/Dockerfile) (shipped with HDF5, MPI, Python3 and NumPy). 

- With Cmake
```bash
mkdir build
cd build
cmake ..
make
./vol
```

- With Makefile (NB: review include paths in the Makefile)
```
make
cd build
./vol
```
