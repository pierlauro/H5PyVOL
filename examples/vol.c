#include "VOL.h"
#include "timing.h"

#include <H5Ppublic.h>
#include <H5Spublic.h>

void write_read(int num_datasets, hid_t acc);

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Please, specify python module and vol class.\nUsage: %s <python_VOL_module> <python_VOL_class>\n", argv[0]);
		exit(1);
	}

	py_initialize();
	const char *module_name = argv[1];
	const char *class_name = argv[2];
	initialize_vol_class(module_name, class_name);
	
	hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
	hid_t vol_id = H5VLregister_connector(&H5VL_python_cls_g, H5P_DEFAULT);
	hid_t acc = H5Pcreate(H5P_FILE_ACCESS);
	H5VL_python_fapl_t fa;
	fa.comm = MPI_COMM_WORLD;
	fa.info = MPI_INFO_NULL;
	H5Pset_vol(acc, vol_id, &fapl);

	write_read(1001, acc);

	py_finalize();
	return 0;
}

void write_read(int num_datasets, hid_t acc){
	const int BUFFER_SIZE = 16;
	
	// Maximum number of digits to represent datasets indexes
	int digits = (int)(floor (log10 (num_datasets))) + 2;
	int names_size = 7 + digits;
	char dataset_names[num_datasets][names_size];

	int datasets[num_datasets][BUFFER_SIZE];
	int read_buffers[num_datasets][BUFFER_SIZE];

	hid_t dataset_ids[num_datasets];

	// Initialize dataset names and fill datasets with their index
	for(int i = 0; i < num_datasets; i++){
		snprintf(dataset_names[i], names_size, "DATASET%d", i);
		for(int j = 0; j < BUFFER_SIZE; j++){
			datasets[i][j] = i;
		}
	}

	hid_t file_id = H5Fcreate("FILENAME.h5", H5F_ACC_TRUNC, H5P_DEFAULT, acc);
	hid_t group_id = H5Gcreate(file_id, "/GROUP", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	hsize_t dims[1] = {BUFFER_SIZE};
	hid_t space = H5Screate_simple (1, dims, NULL);

	for(int i = 0; i < num_datasets; i++){
		dataset_ids[i] = H5Dcreate(group_id, dataset_names[i], H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

timing(write,
	for(int i = 0; i < num_datasets; i++){
		H5Dwrite(dataset_ids[i], H5T_NATIVE_INT, space, space, H5P_DEFAULT, datasets[i]);
	}
)

timing(read,
	for(int i = 0; i < num_datasets; i++){
		H5Dread(dataset_ids[i], H5T_NATIVE_INT, space, space, H5P_DEFAULT, read_buffers[i]);
	}
)

	for(int i = 0; i < num_datasets; i++){
		H5Dclose(dataset_ids[i]);
	}

	H5Gclose(group_id);
	H5Fclose(file_id);
}
