HDF5_PLUGIN_PATH ?= /usr/local/hdf5/lib/plugin/

HDF5_INCLUDE   = /usr/include/hdf5
MPICH_INCLUDE  = /usr/lib/x86_64-linux-gnu/mpich/include
PYTHON_INCLUDE = /usr/include/python3.7m
NUMPY_INCLUDE  = /usr/lib/python3/dist-packages/numpy/core/include

BUILD_DIR = $(CURDIR)/build

COMPILE_INCLUDE_DIRS = -I$(HDF5_INCLUDE) -I$(MPICH_INCLUDE) -I$(PYTHON_INCLUDE) -I$(NUMPY_INCLUDE)

LIB_NAME = libh5pyvol.so

all: clean setup compile

apps: main copy-vols

copy-vols: copy-python copy-swift copy-rados copy-dataclay

clean:
	rm -rf $(BUILD_DIR)/*

setup:
	mkdir -p $(BUILD_DIR)

main: setup
	gcc $(COMPILE_INCLUDE_DIRS) examples/vol.c -lpython3.7m -lhdf5 -lm -lrt -o $(BUILD_DIR)/vol

compile: setup
	# http://codechunks.org/blog/2012/10/24/a-makefile-for-the-simplest-shared-library/
	gcc $(COMPILE_INCLUDE_DIRS) src/c/*.c -lpython3.7m -lhdf5 -lm -lrt -shared -Wl,-soname,$(LIB_NAME) -fPIC -O3 -g -o $(BUILD_DIR)/$(LIB_NAME)

install:
	cp $(BUILD_DIR)/$(LIB_NAME) $(HDF5_PLUGIN_PATH)

copy-python: setup
	cp -r examples/python_vol $(BUILD_DIR)

copy-swift: setup
	cp -r object-stores/swift/swift_vol $(BUILD_DIR)

copy-rados: setup
	cp -r object-stores/rados/rados_vol $(BUILD_DIR)

copy-dataclay: setup
	cp -r object-stores/dataClay/dataClay_vol $(BUILD_DIR)
