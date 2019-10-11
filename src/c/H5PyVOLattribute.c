#include "H5PyVOL.h"

void H5VL_python_attribute_create(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name, hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id, hid_t dxpl_id, void **req){
	fprintf(stderr, "attribute create not currently supported");
	exit(-1);
}

void H5VL_python_attribute_open(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name, hid_t aapl_id, hid_t dxpl_id, void **req){
	fprintf(stderr, "attribute open not currently supported");
	exit(-1);
}

herr_t H5VL_python_attribute_read(void *attr, hid_t mem_type_id, void *buf, hid_t dxpl_id, void **req){
	fprintf(stderr, "attribute read not currently supported");
	exit(-1);
}

herr_t H5VL_python_attribute_write(void *attr, hid_t mem_type_id, const void *buf, hid_t dxpl_id, void **req){
	fprintf(stderr, "attribute write not currently supported");
	exit(-1);
	return -1;
}

herr_t H5VL_python_attribute_get(void *obj, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, va_list arguments){
	fprintf(stderr, "attribute get not currently supported");
	exit(-1);
	return -1;
}

herr_t H5VL_python_attribute_specific(void *obj, const H5VL_loc_params_t *loc_params, H5VL_attr_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments){
	fprintf(stderr, "attribute specific not currently supported");
	exit(-1);
}

herr_t H5VL_python_attribute_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments){
	fprintf(stderr, "attribute optional not currently supported");
	exit(-1);
}

herr_t H5VL_python_attribute_close(void *attr, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(attr, dxpl_id, req);
}
