#!/bin/bash
# Usage: ./compile_h5part.sh [branch|tag|commit]

git submodule init && git submodule update

BRANCH=${1:-master}

cd h5part

# Checking out specific branch/tag/commit
git checkout $BRANCH

rm -rf build
mkdir -p build
make clean

./configure --prefix=$PWD/build --with-hdf5=$PWD/../hdf5/build --enable-parallel && make install

