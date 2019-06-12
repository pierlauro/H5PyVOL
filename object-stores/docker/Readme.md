## Client containers

The dockerfiles in this directory are allowing to use **PyVOL** with the supported object-stores (dataClay, rados, swift).

A prior build of the [*pyvol* image](https://github.com/pierlauro/PyVOL/tree/master/docker) is required.

To build, initialize the variable `OBJECT_STORE` with the desired object store name (`dataClay`, `rados` or `swift`) and then execute:
```bash
docker build -f Dockerfile-$OBJECT_STORE-client -t pyvol_client .
```
