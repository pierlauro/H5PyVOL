## Handover

This document is providing all high-level and low-level details needed to use this library or develop a new one based on the same concepts.

#### Preface

This project has been developed in early 2019 when the virtual object layer was quite undocumented and the provided APIs were in continuous evolution.

Since then, many things have changed: in late February 2020 - together with the release of HDF5 1.12 - a [comprehensive official VOL documentation](https://portal.hdfgroup.org/display/HDF5/Virtual+Object+Layer#VirtualObjectLayer-documentation) has been published both for users and connector developers and [I guess] the current APIs are not going to be altered that much in the future.

The following library has been successfully used with [HDF5 1.12-alpha0](https://forum.hdfgroup.org/t/hdf5-1-12-0-alpha0-snapshot-release/6300) , [h5py 2.10.0](https://github.com/h5py/h5py) and the python interpreter version 3.7.4.

As I am not associated in any way to HDF5 and I have just been a sporadic contributor to h5py, please refer to HDF Group and h5py developers if you have questions about APIs compatibility with new stable versions.

#### HDF5 VOL
The virtual object layer interface provided by the HDF library is allowing developers to easily forward all storage calls to external storage systems. A comprehensive list of available callbacks can be found [here](https://portal.hdfgroup.org/display/HDF5/HDF5+VOL+Connector+Authors+Guide).

Every storage call usually follows this flow: the client is invoking an API provided by the HDF library that is then using the file system through the native VOL connector.

```
// usual flow C application
CLIENT --> HDF LIBRARY --> NATIVE VOL CONNECTOR --> FILE SYSTEM

// usual flow python application
CLIENT --> H5PY --> HDF LIBRARY --> NATIVE VOL CONNECTOR --> FILE SYSTEM
```

When using a custom VOL connector, just the last part of the flow changes: instead of using the native VOL connector, storage calls are forwarded to a custom connector that interfaces with external storage resources.

```
// custom connector flow C application
CLIENT --> HDF LIBRARY --> CUSTOM VOL CONNECTOR --> EXTERNAL STORAGE SYSTEM

// custom connector flow of python application
CLIENT --> H5PY --> HDF LIBRARY --> CUSTOM VOL CONNECTOR --> EXTERNAL STORAGE SYSTEM
```

Details on how to let the HDF5 library use a custom connector can can be found [here](https://portal.hdfgroup.org/display/HDF5/HDF5+VOL+User%27s+Guide).

#### H5PyVOL: motivation
Since the VOL interface is currently available just in C, the overall idea behind h5pyvol is to provide HDF5 connector developers a standard python interface for the development of custom connectors.

To do so, we decided to add an additional abstraction layer - a custom VOL connector simply acting as C-Python bridge - and provide a generic python interface to be filled in for the real implementation of connectors.

The storage calls flow is consequently transformed in the following way:

```
// h5pyvol connector flow C application
CLIENT --> HDF LIBRARY --> H5PYVOL VOL CONNECTOR --> CUSTOM PYTHON VOL CONNECTOR ->  EXTERNAL STORAGE SYSTEM

// h5pyvol connector flow of python application
CLIENT --> H5PY --> HDF LIBRARY --> H5PYVOL VOL CONNECTOR --> CUSTOM PYTHON VOL CONNECTOR ->  EXTERNAL STORAGE SYSTEM
```

A question that could pop up when reading about h5pyvol is: why did you not directly wrap h5py storage calls? The reply is: it would have been much easier and I would have really liked to do that, but that way - unfortunately - custom connectors would just work with python applications and HDF5's multi-language support would be lost.

#### H5PyVOL: high-level overview
From the user point of view, H5PyVOL can be simply intended as a library for writing custom python connectors. The h5pyvol pypi package is providing some simple interfaces to be filled in for implementing any new connector.

To better understand why it is needed and how it works, let's build-up an example.

Let's look at the following client app in pseudo-code:
```
a = array containing 100 int numbers
f = create new HDF5 file named FILE.h5
d = create in FILE.h5 a new dataset named DATASET0 of type int with 100 items
d.write(a) // fill-in DATASET0 with the content of a
[....] do something else
new_a = d.read() // read DATASET0 into the variable new_a
```

The HDF library storage calls invoked in the example are four. For a connector to properly handle them, we are therefore expecting it to provide at least the following functions:
```
create a file
create a dataset
write some content to a dataset
read a dataset
```

As H5PyVOL wants to provide an object-oriented way of implementing connectors, let's see how this could be translated in OO-style:


```
- class H5PyVOL
  - method create_file(name) -- returning a File

- class File
  - method create_dataset(name) -- returning a Dataset

- class Dataset:
  - method read -- returning an array
  - method write(array) -- void
```

That's it! H5PyVOL is exactly providing the over-mentioned interfaces ready to be filled in: creating a new connector simply means implementing the logic of the presented methods (with some additional parameters for metadata, properties, etc... - but that's not the point).
