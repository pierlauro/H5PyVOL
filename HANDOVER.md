## Handover

This document is providing all high-level and low-level details needed to understand this library's concepts, use it or develop a new one based on the same ideas.

#### Preface

This project has been developed in early 2019 when the virtual object layer was quite undocumented and the provided APIs were in continuous evolution.

Since then, many things have changed: in late February 2020 - together with the release of HDF5 1.12 - a [comprehensive official VOL documentation](https://portal.hdfgroup.org/display/HDF5/Virtual+Object+Layer#VirtualObjectLayer-documentation) has been published both for users and connector developers and [I guess] the current APIs are not going to be altered that much in the future.

The following library has been successfully used with [HDF5 1.12-alpha0](https://forum.hdfgroup.org/t/hdf5-1-12-0-alpha0-snapshot-release/6300) , [h5py 2.10.0](https://github.com/h5py/h5py) and the python interpreter version 3.7.4.

As I am not associated in any way to HDF5 and I have just been a sporadic contributor to h5py, please refer to HDF Group and h5py developers if you have questions about APIs compatibility with new stable versions.

#### HDF5 VOL
The virtual object layer interface provided by the HDF library is allowing developers to easily forward all storage calls to external storage systems. A comprehensive list of available callbacks can be found [here](https://portal.hdfgroup.org/display/HDF5/HDF5+VOL+Connector+Authors+Guide).

Traditionally, in HDF5 every storage call follows this flow: the client is invoking an API provided by the HDF library that is then using the file system through the native VOL connector.

```
// usual flow C application
CLIENT --> HDF LIBRARY --> NATIVE VOL CONNECTOR --> FILE SYSTEM

// usual flow python application
CLIENT --> H5PY --> HDF LIBRARY --> NATIVE VOL CONNECTOR --> FILE SYSTEM
```

When using a custom VOL connector, just the last part of the flow changes: storage calls are forwarded to a custom connector that interfaces with external storage resources.

```
// custom connector flow C application
CLIENT --> HDF LIBRARY --> CUSTOM VOL CONNECTOR --> EXTERNAL STORAGE SYSTEM

// custom connector flow of python application
CLIENT --> H5PY --> HDF LIBRARY --> CUSTOM VOL CONNECTOR --> EXTERNAL STORAGE SYSTEM
```

Details on how to specify which custom connector should be used by the HDF5 library can can be found [here](https://portal.hdfgroup.org/display/HDF5/HDF5+VOL+User%27s+Guide).

#### H5PyVOL: motivation
Since the VOL interface is currently available just in C, the overall idea behind h5pyvol is to provide programmers a standard python interface for the development of custom connectors.

To do so, we decided to add an additional abstraction layer - a custom VOL connector simply acting as C-Python bridge - and provide a generic python interface to be filled in for the real implementation of connectors.

The storage calls flow is consequently transformed in the following way:

```
// h5pyvol connector flow C application
CLIENT --> HDF LIBRARY --> H5PYVOL VOL CONNECTOR --> CUSTOM PYTHON VOL CONNECTOR ->  EXTERNAL STORAGE SYSTEM

// h5pyvol connector flow of python application
CLIENT --> H5PY --> HDF LIBRARY --> H5PYVOL VOL CONNECTOR --> CUSTOM PYTHON VOL CONNECTOR ->  EXTERNAL STORAGE SYSTEM
```
To create a CUSTOM PYTHON VOL CONNECTOR, it is just needed to use the APIs provided by the H5PYVOL VOL CONNECTOR.

#### H5PyVOL: high-level overview
From the user point of view, H5PyVOL can be simply intended as a library for writing custom python connectors. The [h5pyvol package](https://github.com/pierlauro/H5PyVOL/tree/master/src/python) is providing some simple interfaces to be filled in for implementing new connectors.

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
  - method create_dataset(name, type, size) -- returning a Dataset

- class Dataset:
  - method read -- returning an array
  - method write(array) -- void
```

That's it! H5PyVOL is exactly providing the over-mentioned interfaces ready to be filled in: creating a new connector simply means implementing the logic of the presented methods (with some additional parameters for metadata, properties, etc... - but that's not the point).

#### H5PyVOL example: an in-memory connector
The following example makes use of [h5pyvol package](https://github.com/pierlauro/H5PyVOL/tree/master/src/python) to implement a simple python in-memory connector supporting the 4 operations mentioned in the previous paragraph: a `File` object will keep a dictionary of named datasets, and each `Dataset` object will keep track of an array.


The abstract classes `H5File` and `H5Dataset` need to be extended in order to provide a concrete implementation of the required methods. Let's look at the interfaces h5pyvol is expecting to be filled in:

```PYTHON
from abc import ABC, abstractmethod

class H5Dataset(ABC):
	@abstractmethod
	def __init__(self, name):
		pass

	@abstractmethod
	def H5VL_python_dataset_read(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, req):
		pass

	@abstractmethod
	def H5VL_python_dataset_write(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buffer, req):
		pass

class H5File(ABC):
	@abstractmethod
	def __init__(self, name):
		pass

	@abstractmethod
	def H5VL_python_dataset_create(self, loc_params, name, gcpl_id, gapl_id, dxpl_id, req) -> H5Dataset:
		pass

```

Let's implement the connector by using the provided interfaces (for simplicity, we are ignoring most of the arguments and accepting arrays of any type and size):

```Python
class Dataset(H5Dataset):
	def __init__(self, name):
		self.name = name
		self.array: []

	def H5VL_python_dataset_read(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, req):
		print('Reading dataset ' + self.name + ' = ' + str(self.array))
		return self.array

	def H5VL_python_dataset_write(self, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buffer, req):
		print('Writing dataset ' + self.name + ' = ' + str(buffer))
		self.array = buffer

class File(H5File):
	def __init__(self, name):
		self.name = name
		self.datasets: dict = {}

	def H5VL_python_dataset_create(self, loc_params, name, gcpl_id, gapl_id, dxpl_id, req) -> Dataset:
		dataset_name = self.name + '/' + name
		print('Creating dataset ' + dataset_name)
		dataset = Dataset(dataset_name)
		self.datasets[dataset_name] = dataset
		return dataset
```

The connector is ready! In order to let HDF5 use it, we just need to put it in a named package (e.g. `in_memory_vol`), and then set the following environment variables:
- `HDF5_VOL_CONNECTOR='H5PyVOL'`: tells HDF5 to use the H5PyVOL bridge
- `H5PyVOLModule='in_memory_vol'`: tells H5PyVOL bridge to use the in-memory connector

There is just a little additional technical detail: as the package need to provide an entrypoint to create files, we also need to provide a concrete implementation of the basic `H5VOL class`:

```Python
class InMemoryVOL(H5VOL):
	def __init__(self):
		self.files: dict = {}

	def H5VL_python_file_create(self, name, flags, fcpl_id, fapl_id, dxpl_id, req) -> H5File:
		print('Creating file ' + name)
		new_file = File(name)
		self.files[name] = new_file
		return new_file
```

After setting the environment variable `H5PyVOLClass='InMemoryVOL'` we're good to go!

NB: the library expects the `in_memory_vol` package folder to be (or be linked) in the same folder you're executing your app into.

#### H5PyVOL shared library: internal structure
The HDF library is expecting a VOL connector to be compiled as HDF plugin (basically a shared library, technical details [here](https://portal.hdfgroup.org/display/HDF5/HDF5+VOL+Connector+Authors+Guide)). As we added the `H5PYVOL VOL CONNECTOR` additional layer, connector developers are not expected to take care of that. This section is just for people wanting to take a look at the internals.

The [h5pyvol shared library](https://github.com/pierlauro/H5PyVOL/tree/master/src/c) is a HDF plugin allowing developers to plug connectors built upon the overmentioned Python module. Its main purpose is handling the interaction between HDF5 apps and user-defined connectors: at HDF lib loading time, it programmatically initializes a Python interpreter to be used for transparently forwarding API calls; at dataset read/write time – instead – it takes care of translating native buffers and numpy arrays into the relative counterparts through the native C-Python interface.

As the library was experimental, there are some important details to take in mind in case a more stable version will be needed in the future. Things to improve:
- Garbage collecting (ATM datasets memory is not freed)
- Managing all types (ATM the library need to be compiled with a specific datasets' expected type)
- Managing all sizes (ATM the library need to be compiled with a specific datasets' expected size)

#### Miscellaneous
- In the [object-stores](https://github.com/pierlauro/H5PyVOL/tree/master/object-stores) folder it is possible to find basic connectors for dataClay, Ceph Rados, Minio, OpenIO (same interface than Minio) and Swift.
- In the [submodules](https://github.com/pierlauro/H5PyVOL/tree/master/submodules) folder, it is possible to find two submodules containing H5Part and VPIC-IO readapted to use H5PyVOL (first used benchmarks - then discarded).
- Containers: it is possible to look into the [docker folder](https://github.com/pierlauro/H5PyVOL/tree/master/docker) for building containers with H5PyVOL built-in (careful with library versions in Dockerfiles).

#### FAQ
> Why did you not directly wrap h5py storage calls?

It would have been much easier and I would have really liked to do that, but that way - unfortunately - custom connectors would just work with python applications and HDF5's multi-language support would be lost.

> Do you recommend to extend the existing library to have a more stable version?

NO! Even I - the person that wrote it - would not to that. This library is the result of a dive into the darkness: when it was written there was no documentation at all about the components it interacts with and this is the reason of increased instability with new APIs. Writing this library from scratch following the same concepts and the [now existing] HDF5 VOL documentation would take anyone much less time and effort.
