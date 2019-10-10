#include "PyVOL.h"

void* H5VL_python_file_create(const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_file_create";
	PyObject *ret = PyObject_CallMethod(VOL_class, method_name, "slllll", name, flags, fcpl_id, fapl_id, dxpl_id, req);
	PyErr_Print();
	return ret;
}

void* H5VL_python_file_open(const char *name, unsigned flags, hid_t fapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_file_open";
	PyObject *ret = PyObject_CallMethod(VOL_class, method_name, "sllll", name, flags, fapl_id, dxpl_id, req);
	PyErr_Print();
	return ret;
}

herr_t H5VL_python_file_close(void *file, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(file, dxpl_id, req);
}
