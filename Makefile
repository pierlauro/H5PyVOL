all: clean copy-python main tests

clean:
	rm -rf build/*

copy-python:
	mkdir -p build
	cp -r src/python_vol build/

main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc src/python_util.c src/VOL.c examples/vol.c -lpython3.6m -lhdf5 -o build/vol

tests:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc src/python_util.c src/VOL.c examples/c-py.c -lpython3.6m -lhdf5 -o build/c-py
