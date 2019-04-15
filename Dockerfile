FROM pierlauro/hdf5-hyperslab_updates_numpy

RUN apt-get update && apt-get install -y cmake make

COPY . /PyVOL

WORKDIR /PyVOL
