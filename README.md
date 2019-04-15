# PyVOL

This is an embryonic prototype of generic Python virtual object layer (VOL) for HDF5. It is providing some easily implementable APIs to create new python VOLs.

NB: at moment, only some example functions are implemented (e.g. file open, dataset r/w) and only datasets of integer data type are supported.

### Python part
In order to develop an easily pluggable python VOL, an [abstract data model](https://github.com/pierlauro/PyVOL/tree/master/src/python_vol/abstract.py) and one [basic example implementation](https://github.com/pierlauro/PyVOL/tree/master/src/python_vol/__init__.py) are provided.


### C part
Once implemented a python VOL, it is possible to bind the HDF library on it by simply calling the function [initialize_vol_class](https://github.com/pierlauro/PyVOL/blob/d7ee5a2f901e0890b3c21cc0342574b08190bbfd/src/VOL.c#L173) as in [the provided example](https://github.com/pierlauro/PyVOL/blob/d7ee5a2f901e0890b3c21cc0342574b08190bbfd/examples/vol.c#L10).
