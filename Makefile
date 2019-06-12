all: clean copy-python main test-native copy-swift copy-rados copy-dataclay

clean:
	rm -rf build/*

copy-python:
	mkdir -p build
	cp -r examples/python_vol build/

main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc/c src/c/*.c examples/vol.c -lpython3.6m -lhdf5 -lm -lrt -o build/vol

test-native:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc/c src/c/*.c test/test_native.c -lpython3.6m -lhdf5 -lm -lrt -o build/test

copy-swift:
	mkdir -p build
	cp -r object-stores/swift/swift_vol build/

copy-rados:
	mkdir -p build
	cp -r object-stores/rados/rados_vol build/

copy-dataclay:
	mkdir -p build
	cp -r object-stores/dataClay/dataClay_vol build/
