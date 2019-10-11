#include "H5PyVOL.h"

herr_t H5VL_python_datatype_close(void *dt, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(dt, dxpl_id, req);
}
