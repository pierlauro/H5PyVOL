INSTALL_DIR = /usr/
LIB_INSTALL_DIR = $(INSTALL_DIR)/lib
INCLUDE_INSTALL_DIR = $(INSTALL_DIR)/include

HDF5_INCLUDE   = /usr/include/hdf5
MPICH_INCLUDE  = /usr/lib/x86_64-linux-gnu/mpich/include
PYTHON_INCLUDE = /usr/include/python3.7m
NUMPY_INCLUDE  = /usr/lib/python3/dist-packages/numpy/core/include
PYVOL_INCLUDE  = $(INCLUDE_INSTALL_DIR)

BUILD_DIR = $(CURDIR)/build
LIB_BUILD_DIR = $(BUILD_DIR)/pyvol/lib
INCLUDE_BUILD_DIR = $(BUILD_DIR)/pyvol/include

COMPILE_INCLUDE_DIRS = -I$(HDF5_INCLUDE) -I$(MPICH_INCLUDE) -I$(PYTHON_INCLUDE) -I$(NUMPY_INCLUDE)
MAIN_INCLUDE_DIRS    = $(COMPILE_INCLUDE_DIRS) -I$(PYVOL_INCLUDE)


all: clean setup compile

apps: main test-native copy-vols

copy-vols: copy-python copy-swift copy-rados copy-dataclay

clean:
	rm -rf $(BUILD_DIR)/*

setup:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_BUILD_DIR)
	mkdir -p $(INCLUDE_BUILD_DIR)

main: setup
	h5pcc $(MAIN_INCLUDE_DIRS) -L$(LIB_INSTALL_DIR) examples/vol.c -lpython3.7m -lhdf5 -lm -lrt -lpyvol -o $(BUILD_DIR)/vol
	rm vol.o

compile: setup
	# http://codechunks.org/blog/2012/10/24/a-makefile-for-the-simplest-shared-library/
	gcc $(COMPILE_INCLUDE_DIRS) src/c/*.c -lpython3.7m -lhdf5 -lm -lrt -shared -Wl,-soname,libpyvol.so.1 -fPIC -O3 -g -o $(LIB_BUILD_DIR)/libpyvol.so.1
	cp src/c/*h $(INCLUDE_BUILD_DIR)

install:
	rm -f $(LIB_INSTALL_DIR)/libpyvol*
	mkdir -p $(LIB_INSTALL_DIR)
	cp $(LIB_BUILD_DIR)/libpyvol.so.1 $(LIB_INSTALL_DIR)
	ln -s $(LIB_INSTALL_DIR)/libpyvol.so.1 $(LIB_INSTALL_DIR)/libpyvol.so
	mkdir -p $(INCLUDE_INSTALL_DIR)
	cp $(INCLUDE_BUILD_DIR)/* $(INCLUDE_INSTALL_DIR)

test-native: setup
	h5pcc $(MAIN_INCLUDE_DIRS) -L$(LIB_INSTALL_DIR) test/test_native.c -lpython3.7m -lhdf5 -lm -lrt -lpyvol -o $(BUILD_DIR)/test
	rm test_native.o

copy-python: setup
	cp -r examples/python_vol $(BUILD_DIR)

copy-swift: setup
	cp -r object-stores/swift/swift_vol $(BUILD_DIR)

copy-rados: setup
	cp -r object-stores/rados/rados_vol $(BUILD_DIR)

copy-dataclay: setup
	cp -r object-stores/dataClay/dataClay_vol $(BUILD_DIR)
