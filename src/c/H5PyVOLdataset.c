#include "H5PyVOL.h"
#include <stdlib.h>

static int get_size(){
	return atoi(getenv("DATASET_SIZE"));
}

static int SIZE;

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
	int rank = 1; //H5Sget_simple_extent_ndims(mem_space_id);
	//fprintf(stderr,"RANK -> %d\n", rank);
	hsize_t *dims = malloc(rank * sizeof(hsize_t)), *max_dims = malloc(rank * sizeof(hsize_t));
	*dims = (hsize_t)get_size();
	H5Sget_simple_extent_dims(mem_space_id, dims, max_dims);
	// max_dims = -1 if size is not limited
	//fprintf(stderr, "buf == NULL -> %d\n", buf == NULL);
	//fprintf(stderr, "mem_type_id = %d\n", mem_type_id);
	float *float_buf = (int*)buf;
	import_array();
	PyObject* array = PyArray_SimpleNewFromData(1, dims, get_numpy_type(H5T_NATIVE_FLOAT), (void*)buf);
	PyErr_Print();

	char *method_name = "H5VL_python_dataset_write";
	PyObject *ret = PyObject_CallMethod(dset, method_name, "llllOl", mem_type_id, mem_space_id, file_space_id, xfer_plist_id, array, req);
	PyErr_Print();
	return 1;
}



herr_t H5VL_python_dataset_get(void *obj, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_dataset_get";
	hid_t   *ret_id = va_arg(arguments, hid_t *);
        *ret_id = H5P_DATASET_CREATE;

	if(get_type == H5VL_DATASET_GET_SPACE){
		hsize_t dims[1] = {(hsize_t)get_size()};
		hid_t space = H5Screate_simple (1, dims, NULL);
		*ret_id = space;
	//	PyObject *dims_attribute = PyObject_GetAttr(obj, PyUnicode_FromString("dims"));
	//	*ret_id = dims_attribute;
	}else if(get_type == H5VL_DATASET_GET_TYPE){
		*ret_id = H5Tcopy(H5T_NATIVE_FLOAT);
		// todo wrap new datatype
	}

	//PyObject *ret = PyObject_CallMethod(obj, method_name, "llll", get_type, dxpl_id, req, arguments);
	//PyErr_Print();
	return 1;
}

herr_t H5VL_python_dataset_specific(void *obj, H5VL_dataset_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_dataset_specific";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llll", specific_type, dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_dataset_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_dataset_optional";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lll", dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}


herr_t H5VL_python_dataset_close(void *dset, hid_t dxpl_id, void **req){
	return 1; //H5VL_python_object_close(dset, dxpl_id, req);
}
