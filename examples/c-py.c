#include "VOL.h"
#include "python_util.h"

void fill_array(int* array, int size){
	for(int i = 0; i < size; i++){
		array[i] = i;
	}
}

void check_array(int* array, int size){
	for(int i = 0; i < size; i++){
		if(!array[i] == i){
			printf("ERROR: array check failed on index %d: %d", i, array[i]);
			exit(1);
		}
	}
}

int main(){
	py_initialize();
	const char *module_name = "python_vol"; // TODO move outside
	char *class_name = "VOL"; // TODO move outside
	initialize_vol_class(module_name, class_name);
	
	PyObject *file, *group, *dataset;
	file = H5VL_python_file_create("aaa", 0, 0, 0, 0, 0);
	group = H5VL_python_group_create(file, 0, "group", 0, 0, 0, 0);
	dataset = H5VL_python_dataset_create(group, 0, "dataset0", 0, 0, 0, 0);
	int *buffer = (int *)calloc(sizeof(int), BUFFER_SIZE);
	fill_array(buffer, 16);
	H5VL_python_dataset_write(dataset, H5T_NATIVE_INT, 0, 0, 0, buffer, 0);
	int *dataset_buffer;
	H5VL_python_dataset_read(dataset, 0, 0, 0, 0, &dataset_buffer, 0);
	check_array(dataset_buffer, 16);
	
	py_finalize();
	return 0;
}
