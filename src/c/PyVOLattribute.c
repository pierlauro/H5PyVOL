#include "PyVOL.h"

herr_t H5VL_python_attribute_close(void *attr, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(attr, dxpl_id, req);
}
