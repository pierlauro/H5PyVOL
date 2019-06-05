# PyVol docker
This folder contains 2 Dockerfiles aimed to build and install both hdf5 (branch hyperslabs\_updates) and PyVol in a fully autocontained single-machine environment. Their use is recommended for testing purposes.

- **Dockerfile-hdf5\_hyperslab\_updates** takes care of download, build and install the updated version of HDF5's branch *hyperslabs\_updates*.
- **Dockerfile**, requiring prior build of *hyperslabs\_updates* image with name *hdf5-hyperslabs\_updates*, installs PyVol's dependencies and copies the local repository in the container.

### Build containers
Execute the following commands to build the containers:

```bash
docker build --no-cache -t hdf5-hyperslabs_updates -f Dockerfile-hdf5_hyperslab_updates .

docker build --no-cache -t pyvol .
```

### Use PyVol container
```bash
docker run -it pyvol bash
```
