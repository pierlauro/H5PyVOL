#include "VOL.h"

PyObject* VOL_class;

/* Generic Python VOL connector class struct */
const H5VL_class_t H5VL_python_cls_g = {
	0,			/* version	*/
	500,			/* value		*/
	PyHDFVol,		/* name		 */
	0,			/* capability flags */
	H5VL_pyvol_init,			/* initialize */
	NULL,			/* terminate	*/
	{ /* info_cls */
		(size_t)sizeof(H5VL_class_t),	/* info size	*/	// TODO adjust to proper size
		NULL,			/* info copy	*/
		NULL,			/* info compare */
		NULL,			/* info free	*/
		NULL,			/* info to str*/
		NULL			/* str to info*/
	},
	{ /* wrap_cls */
		NULL,			/* get_object */
		NULL,			/* get_wrap_ctx */
		NULL,			/* wrap_object*/
		NULL			/* free_wrap_ctx */
	},
	{ /* attribute_cls */
		NULL,			/* create	 */
		NULL,			/* open		 */
		NULL,			/* read		 */
		NULL,			/* write		*/
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		H5VL_python_attribute_close			/* close		*/
	},
	{ /* dataset_cls */
		H5VL_python_dataset_create,			/* create	 */
		H5VL_python_dataset_open,			/* open		 */
		H5VL_python_dataset_read,			/* read		 */
		H5VL_python_dataset_write,			/* write		*/
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		H5VL_python_dataset_close			/* close		*/
	},
	{ /* datatype_cls */
		NULL,			/* commit	 */
		NULL,			/* open		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		H5VL_python_datatype_close			/* close		*/
	},
	{ /* file_cls */
		H5VL_python_file_create,			/* create	 */
		H5VL_python_file_open,			/* open		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		H5VL_python_file_close			/* close		*/
	},
	{ /* group_cls */
		H5VL_python_group_create,			/* create	 */
		H5VL_python_group_open,			/* open		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		H5VL_python_group_close			/* close		*/
	},
	{ /* link_cls */
		NULL,			/* create	 */
		NULL,			/* copy		 */
		NULL,			/* move		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL			/* optional	 */
	},
	{ /* object_cls */
		NULL,			/* open		 */
		NULL,			/* copy		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL			/* optional	 */
	},
	{ /* request_cls */
		NULL,			/* wait		 */
		NULL,			/* notify	 */
		NULL,			/* cancel	 */
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		NULL			/* free		 */
	},
	NULL				/* optional	 */
};

herr_t H5VL_python_object_close(void *obj, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_object_close";
	PyObject_CallMethod(obj, method_name, "ll", dxpl_id, req);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_attribute_close(void *attr, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(attr, dxpl_id, req);
}

herr_t H5VL_python_datatype_close(void *dt, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(dt, dxpl_id, req);
}

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
	int rank = H5Sget_simple_extent_ndims(mem_space_id);
	hsize_t *dims = malloc(rank * sizeof(hsize_t)), *max_dims = malloc(rank * sizeof(hsize_t));
	H5Sget_simple_extent_dims(mem_space_id, dims, max_dims);
	// max_dims = -1 if size is not limited
	import_array();
	PyObject* array = PyArray_SimpleNewFromData(rank, (npy_intp*)dims, get_numpy_type(mem_type_id), (void*) buf);

	char *method_name = "H5VL_python_dataset_write";
	PyObject *ret = PyObject_CallMethod(dset, method_name, "llllOl", mem_type_id, mem_space_id, file_space_id, xfer_plist_id, array, req);
	PyErr_Print();
	return 1;
}

herr_t H5VL_python_dataset_close(void *dset, hid_t dxpl_id, void **req){
	return H5VL_python_object_close(dset, dxpl_id, req);
}

void initialize_vol_class(const char* module_name, const char* class_name){
	// TODO check that class is instance of CPyVOL's VOL
	PyObject* module = py_import_module(module_name);
	VOL_class = py_get_class(module, class_name);
}

static hbool_t H5VL_pyvol_init_g = 0;

herr_t H5VL_pyvol_init(hid_t vipl_id){
	char *module_name = getenv(PyHDFVolModule), *class_name = getenv(PyHDFVolClass);

	/* Check whether already initialized */
	if(H5VL_pyvol_init_g == 1){
		fprintf(stderr, "attempting to initialize connector twice");
		exit(-1);
	}

	/* Initializing python interpreter */
	py_initialize();
	/* Initializing VOL class */
	initialize_vol_class(module_name, class_name);
	H5VL_pyvol_init_g = 1;
	return 1;
}

/*---------------------------------------------------------------------------
 PLUGIN DEFINITION
---------------------------------------------------------------------------*/
H5PL_type_t H5PLget_plugin_type(void) {
    return H5PL_TYPE_VOL;
}

const void *H5PLget_plugin_info(void) {
    return &H5VL_python_cls_g;
}
/*---------------------------------------------------------------------------*/
