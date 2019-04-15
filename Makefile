all: clean copy-python main tests

clean:
	rm -rf target/*

copy-python:
	mkdir -p target
	cp -r src/python_vol target/

main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc src/python_util.c src/VOL.c examples/vol.c -lpython3.6m -lhdf5 -o target/vol.out

tests:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -Isrc src/python_util.c src/VOL.c examples/c-py.c -lpython3.6m -lhdf5 -o target/c-py.out
