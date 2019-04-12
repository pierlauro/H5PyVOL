main:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich python_util.c VOL.c main.c -lpython3.6m -lhdf5

test:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich python_util.c VOL.c test.c -lpython3.6m -lhdf5
