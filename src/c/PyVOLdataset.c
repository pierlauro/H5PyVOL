#include "PyVOL.h"

void* H5VL_python_dataset_create(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t dcpl_id, hid_t dapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_dataset_create";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lsllll", loc_params, name, dcpl_id, dapl_id, dxpl_id, req);
	PyErr_Print();
	return ret;
}

void* H5VL_python_dataset_open(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t dapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_dataset_open";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lslll", loc_params, name, dapl_id, dxpl_id, req);
	PyErr_Print();
	return ret;
}

herr_t H5VL_python_dataset_read(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t xfer_plist_id, void *buf, void **req){
	char *method_name = "H5VL_python_dataset_read";
	PyArrayObject_fields* array = (PyArrayObject_fields *)PyObject_CallMethod(dset, method_name, "lllll", mem_type_id, mem_space_id, file_space_id, xfer_plist_id, req);
	PyErr_Print();
	int nbytes = PyArray_NBYTES((PyArrayObject *)array);
	memcpy(&buf[0], &array->data[0], nbytes); // This memcpy should be avoided
	return 1;
}

herr_t H5VL_python_dataset_write(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t xfer_plist_id, const void *buf, void **req){
	int rank = H5Sget_simple_extent_ndims(mem_space_id);
	hsize_t *dims = malloc(rank * sizeof(hsize_t)), *max_dims = malloc(rank * sizeof(hsize_t));
	H5Sget_simple_extent_dims(mem_space_id, dims, max_dims);
	// max_dims = -1 if size is not limited
	import_array();
	PyObject* array = PyArray_SimpleNewFromData(rank, (npy_intp*)dims, get_numpy_type(mem_type_id), (void*) buf);

	char *method_name = "H5VL_python_dataset_write";
	PyObject *ret = PyObject_CallMethod(dset, method_name, "llllOl", mem_type_id, mem_space_id, file_space_id, xfer_plist_id, array, req);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_dataset_close(void *dset, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(dset, dxpl_id, req);
}
