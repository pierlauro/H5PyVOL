#FROM pierlauro/hdf5-hyperslab_updates_numpy
FROM hdf5-hyperslabs_updates

# Install python and its utilities
RUN apt-get install -y python3-dev python-numpy python3-numpy python3-pip

# Installing build automation systems
RUN apt-get update && apt-get install -y cmake make

COPY . /PyVOL

WORKDIR /PyVOL
