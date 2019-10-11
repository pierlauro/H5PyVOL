#include "H5PyVOL.h"

void* H5VL_python_group_create(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t gcpl_id, hid_t gapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_group_create";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lsllll", loc_params, name, gcpl_id, gapl_id, dxpl_id, req);
	PyErr_Print();
	return ret;
}

void* H5VL_python_group_open(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t gapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_group_open";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lslll", loc_params, name, gapl_id, dxpl_id, req);
	PyErr_Print();
	return ret;
}

herr_t H5VL_python_group_get(void *obj, H5VL_group_get_t get_type, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_group_get";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llll", get_type, dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_group_specific(void *obj, H5VL_group_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_group_specific";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llll", specific_type, dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_group_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments){
	char *method_name = "H5VL_python_group_optional";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "lll", dxpl_id, req, arguments);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_group_close(void *grp, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(grp, dxpl_id, req);
}
