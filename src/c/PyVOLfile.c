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

herr_t H5VL_python_file_get(void *obj, H5VL_file_get_t get_type, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_file_get";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llll", get_type, dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_file_specific(void *obj, H5VL_file_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_file_specific";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llll", specific_type, dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_file_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_file_optional";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lll", dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_file_close(void *file, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(file, dxpl_id, req);
}
