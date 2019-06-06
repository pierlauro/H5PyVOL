all: clean copy-python main cpy copy-swift copy-rados

clean:
	rm -rf build/*

copy-python:
	mkdir -p build
	cp -r examples/python_vol build/

main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc/c src/c/*.c examples/vol.c -lpython3.6m -lhdf5 -lm -lrt -o build/vol

cpy:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc/c src/c/*.c examples/c-py.c -lpython3.6m -lhdf5 -o build/c-py

copy-swift:
	mkdir -p build
	cp -r object-stores/swift/swift_vol build/

copy-rados:
	mkdir -p build
	cp -r object-stores/rados/rados_vol build/
