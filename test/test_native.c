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

	write_read(1030, acc);

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
	int buffer_reads[num_datasets][BUFFER_SIZE];
	int buffer_reads2[num_datasets][BUFFER_SIZE];

	hid_t dataset_ids[num_datasets];
	hid_t dataset_ids2[num_datasets];

	// Initialize dataset names and fill datasets with their index
	for(int i = 0; i < num_datasets; i++){
		snprintf(dataset_names[i], names_size, "DATASET%d", i);
		for(int j = 0; j < BUFFER_SIZE; j++){
			datasets[i][j] = i;
		}
		printf("\n");
	}

	hid_t file_id = H5Fcreate("FILENAME.h5", H5F_ACC_TRUNC, H5P_DEFAULT, acc);
	hid_t acc2 = H5Pcreate(H5P_FILE_ACCESS);
	hid_t file_id2 = H5Fcreate("FILENAME.h5", H5F_ACC_TRUNC, H5P_DEFAULT, acc2);
	hid_t group_id = H5Gcreate(file_id, "/GROUP", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	hid_t group_id2 = H5Gcreate(file_id2, "/GROUP", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	hsize_t dims[1] = {BUFFER_SIZE};
	hid_t space = H5Screate_simple (1, dims, NULL);

	for(int i = 0; i < num_datasets; i++){
		dataset_ids[i] = H5Dcreate(group_id, dataset_names[i], H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		dataset_ids2[i] = H5Dcreate(group_id2, dataset_names[i], H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

timing(write,
	for(int i = 0; i < num_datasets; i++){
		H5Dwrite(dataset_ids[i], H5T_NATIVE_INT, space, space, H5P_DEFAULT, datasets[i]);
		H5Dwrite(dataset_ids2[i], H5T_NATIVE_INT, space, space, H5P_DEFAULT, datasets[i]);
	}
)

timing(read,
	for(int i = 0; i < num_datasets; i++){
		H5Dread(dataset_ids[i], H5T_NATIVE_INT, space, space, H5P_DEFAULT, buffer_reads[i]);
		H5Dread(dataset_ids2[i], H5T_NATIVE_INT, space, space, H5P_DEFAULT, buffer_reads2[i]);
	}
)

	for(int i = 0; i < num_datasets; i++){
		H5Dclose(dataset_ids[i]);
		H5Dclose(dataset_ids2[i]);
	}

	H5Gclose(group_id);
	H5Gclose(group_id2);
	H5Fclose(file_id);
	H5Fclose(file_id2);
	
	// Initialize dataset names and fill datasets with their index
	for(int i = 0; i < num_datasets; i++){
		for(int j = 0; j < BUFFER_SIZE; j++){
			if(buffer_reads[i][j] != buffer_reads2[i][j]){
				printf("[ERROR] DATASET%d[%d] = %d != %d\n", i, j, buffer_reads[i][j], buffer_reads2[i][j]);
			}
		}
	}

}
