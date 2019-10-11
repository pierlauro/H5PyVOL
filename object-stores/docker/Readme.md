## Client containers

The dockerfiles in this directory are allowing to use **H5PyVOL** with the supported object-stores (dataClay, rados, swift).

A prior build of the [*h5pyvol* image](https://github.com/pierlauro/H5PyVOL/tree/master/docker) is required.

To build, initialize the variable `OBJECT_STORE` with the desired object store name (`dataClay`, `rados` or `swift`) and then execute:
```bash
docker build -f Dockerfile-$OBJECT_STORE-client -t h5pyvol_client .
```
