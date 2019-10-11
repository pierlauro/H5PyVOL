#include "H5PyVOL.h"

PyObject* VOL_class;

/* Generic Python VOL connector class struct */
const H5VL_class_t H5VL_python_cls_g = {
	PyHDFVolVersion,	/* version */
	PyHDFVolValue,		/* value */
	PyHDFVol,		/* name	*/
	0,			/* capability flags */
	H5VL_python_init,	/* initialize */
	H5VL_python_term,	/* terminate */
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
		H5VL_python_attribute_create,		/* create */
		H5VL_python_attribute_open,		/* open */
		H5VL_python_attribute_read,		/* read */
		H5VL_python_attribute_write,		/* write */
		H5VL_python_attribute_get,		/* get */
		H5VL_python_attribute_specific,		/* specific */
		H5VL_python_attribute_optional,		/* optional */
		H5VL_python_attribute_close		/* close */
	},
	{ /* dataset_cls */
		H5VL_python_dataset_create,		/* create */
		H5VL_python_dataset_open,		/* open	*/
		H5VL_python_dataset_read,		/* read */
		H5VL_python_dataset_write,		/* write */
		H5VL_python_dataset_get,		/* get */
		H5VL_python_dataset_specific,		/* specific */
		H5VL_python_dataset_optional,		/* optional */
		H5VL_python_dataset_close		/* close */
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
		H5VL_python_file_create,	/* create */
		H5VL_python_file_open,		/* open	 */
		H5VL_python_file_get,		/* get */
		H5VL_python_file_specific,	/* specific */
		H5VL_python_file_optional,	/* optional */
		H5VL_python_file_close		/* close */
	},
	{ /* group_cls */
		H5VL_python_group_create,	/* create */
		H5VL_python_group_open,		/* open	*/
		H5VL_python_group_get,		/* get */
		H5VL_python_group_specific,	/* specific */
		H5VL_python_group_optional,	/* optional */
		H5VL_python_group_close		/* close */
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

static hbool_t H5VL_python_init_g = 0;

void initialize_vol_class(const char* module_name, const char* class_name){
	// TODO check that class is instance of H5PyVOL's VOL
	PyObject* module = py_import_module(module_name);
	VOL_class = py_get_class(module, class_name);
}

herr_t H5VL_python_init(hid_t vipl_id){
	char *module_name = getenv(PyHDFVolModule), *class_name = getenv(PyHDFVolClass);

	/* Check whether already initialized */
	if(H5VL_python_init_g == 1){
		fprintf(stderr, "attempting to initialize connector twice");
		exit(-1);
	}

	/* Initializing python interpreter */
	py_initialize();
	/* Initializing VOL class */
	initialize_vol_class(module_name, class_name);
	H5VL_python_init_g = 1;
	return 1;
}

herr_t H5VL_python_term(void){
	py_finalize();
	H5VL_python_init_g = 0;
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
