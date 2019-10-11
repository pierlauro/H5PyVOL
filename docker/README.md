# H5PyVOL docker
This folder contains 2 Dockerfiles aimed to build and install both hdf5 (branch *develop*) and H5PyVOL in a fully autocontained single-machine environment. Their use is recommended for testing purposes.

- [Dockerfile-hdf5\_develop](https://github.com/pierlauro/H5PyVOL/blob/master/docker/Dockerfile-hdf5_develop) downloads, builds and installs the updated version of HDF5 develop branch.
- [Dockerfile](https://github.com/pierlauro/H5PyVOL/blob/master/docker/Dockerfile) installs H5PyVOL's dependencies and copies the local repository in the container.

### Build containers
Execute the following commands to build the containers:

```bash
docker build --no-cache -f Dockerfile-hdf5_develop -t hdf5-develop .
cd .. # Change directory needed to copy local repository
docker build --no-cache -f docker/Dockerfile-h5pyvol -t h5pyvol .
```

### Use H5PyVOL container
```bash
docker run -it h5pyvol bash
```
