#include "VOL.h"

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

	hid_t f = H5Fcreate("FILENAME.h5", H5F_ACC_TRUNC, H5P_DEFAULT, acc);
	H5Fclose(f);

	py_finalize();
	return 0;
}

