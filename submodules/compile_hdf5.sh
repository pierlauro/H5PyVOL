#!/bin/bash
# Usage: ./compile_hdf5.sh [branch|tag|commit]

git submodule init && git submodule update

BRANCH=${1:-develop}

cd hdf5

# Checking out specific branch/tag/commit
git checkout $BRANCH

# Preparing hdf5 folders
rm -rf build
mkdir -p build

# Configuring, compiling and installing hdf lib
make clean

./autogen.sh && \
./configure --prefix=$PWD/build --enable-parallel && \

make -j `nproc` && make install
