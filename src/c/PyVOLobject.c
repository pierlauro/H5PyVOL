#include "PyVOL.h"

herr_t H5VL_python_object_close(void *obj, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_object_close";
	PyObject_CallMethod(obj, method_name, "ll", dxpl_id, req);
	PyErr_Print();
	return 1;
}
