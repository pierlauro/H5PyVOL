all: clean copy-python main tests

clean:
	rm -rf target/*

copy-python:
	mkdir -p target
	cp -r src/python_vol target/

main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich src/python_util.c src/VOL.c src/main.c -lpython3.6m -lhdf5 -o target/main

tests:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich src/python_util.c src/VOL.c src/test.c -lpython3.6m -lhdf5 -o target/tests
