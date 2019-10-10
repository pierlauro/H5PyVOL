#include "PyVOL.h"

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

herr_t H5VL_python_group_close(void *grp, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(grp, dxpl_id, req);
}

void initialize_vol_class(const char* module_name, const char* class_name){
	// TODO check that class is instance of CPyVOL's VOL
	PyObject* module = py_import_module(module_name);
	VOL_class = py_get_class(module, class_name);
}
