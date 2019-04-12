#include "VOL.h"

#include <H5Ppublic.h>
#include <H5Spublic.h>

int main(){
	py_initialize();
	const char *module_name = "python_vol"; // TODO move outside
	char *class_name = "VOL"; // TODO move outside
	initialize_vol_class(module_name, class_name);
	
	hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
	hid_t vol_id = H5VLregister_connector(&H5VL_python_cls_g, H5P_DEFAULT);
	hid_t acc = H5Pcreate(H5P_FILE_ACCESS);
	H5VL_python_fapl_t fa;
	fa.comm = MPI_COMM_WORLD;
	fa.info = MPI_INFO_NULL;
	H5Pset_vol(acc, vol_id, &fapl);

	hid_t file_id = H5Fcreate("FILENAME.h5", H5F_ACC_TRUNC, H5P_DEFAULT, acc);
	hid_t group_id = H5Gcreate(file_id, "/GROUP", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	hsize_t dims[1] = {16};
	hid_t space = H5Screate_simple (1, dims, NULL);

	hid_t dataset_id = H5Dcreate(group_id, "DATASET", H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	H5Dclose(dataset_id);
	H5Gclose(group_id);
	H5Fclose(file_id);

	py_finalize();
	return 0;
}

