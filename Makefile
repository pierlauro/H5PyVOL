all:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich python_util.c VOL.c -lpython3.6m -lhdf5
