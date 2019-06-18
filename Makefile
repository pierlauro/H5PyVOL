all: clean install-shared copy-python main test-native copy-swift copy-rados copy-dataclay

clean:
	rm -rf build/*

copy-python:
	mkdir -p build
	cp -r examples/python_vol build/

main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -I/usr/include/pyvol examples/vol.c  -lpython3.6m -lhdf5 -lm -lrt -lpyvol -o build/vol

install-shared:
	# http://codechunks.org/blog/2012/10/24/a-makefile-for-the-simplest-shared-library/
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc/c src/c/*.c -lpython3.6m -lhdf5 -lm -lrt -shared -Wl,-soname,libpyvol.so.1 -fPIC -O3 -g -o libpyvol.so.1
	cp libpyvol.so.1 /usr/lib/
	ln -s /usr/lib/libpyvol.so.1 /usr/lib/libpyvol.so
	mkdir /usr/include/pyvol
	cp src/c/*h /usr/include/pyvol

test-native:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -I/usr/include/pyvol test/test_native.c -lpython3.6m -lhdf5 -lm -lrt -lpyvol -o build/test

copy-swift:
	mkdir -p build
	cp -r object-stores/swift/swift_vol build/

copy-rados:
	mkdir -p build
	cp -r object-stores/rados/rados_vol build/

copy-dataclay:
	mkdir -p build
	cp -r object-stores/dataClay/dataClay_vol build/
