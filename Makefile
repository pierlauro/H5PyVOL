all:
	gcc -I/usr/include/python3.6m -I/usr/include/mpich -I/usr/include/hdf5 python_util.c VOL.c -lpython3.6m
