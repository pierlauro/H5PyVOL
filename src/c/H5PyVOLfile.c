#include "H5PyVOL.h"
#include <stdarg.h>

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
	if(get_type == H5VL_FILE_GET_NAME){
		H5I_type_t type = (H5I_type_t)va_arg(arguments, int); /* enum work-around */
		size_t size = va_arg(arguments, size_t);
		char *name = va_arg(arguments, char *);
		ssize_t *ret  = va_arg(arguments, ssize_t *);

		PyObject *name_attribute = PyObject_GetAttr(obj, PyUnicode_FromString("name"));
		char *tmp_name = PyBytes_AsString(PyUnicode_AsUTF8String(name_attribute));
		size_t len = strlen(tmp_name);

		if(name) {
			memcpy(name, tmp_name, len + 1);
		}

		*ret = (ssize_t)len;
	}
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
