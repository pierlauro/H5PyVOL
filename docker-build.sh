#! /bin/bash
docker build --no-cache -f docker/Dockerfile-hdf5_develop -t hdf5-develop .
docker build --no-cache -f docker/Dockerfile -t pyvol .
docker build --no-cache -f object-stores/docker/Dockerfile-dataClay-client -t dataclay_client .
docker build --no-cache -f object-stores/docker/Dockerfile-swift-client -t swift_client .
docker build --no-cache -f object-stores/docker/Dockerfile-rados-client -t rados_client .

