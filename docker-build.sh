#! /bin/bash
docker build --no-cache -f docker/Dockerfile-hdf5_hyperslab_updates -t hdf5-hyperslabs_updates .
docker build --no-cache -f docker/Dockerfile -t pyvol .
docker build --no-cache -f object-stores/docker/Dockerfile-dataClay-client -t dataclay_client .
docker build --no-cache -f object-stores/docker/Dockerfile-swift-client -t swift_client .
docker build --no-cache -f object-stores/docker/Dockerfile-rados-client -t rados_client .

