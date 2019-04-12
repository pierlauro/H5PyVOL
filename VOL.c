#include <Python.h>
#include <numpy/arrayobject.h>
#include "H5VLpublic.h"
#include "H5Ppublic.h"
#include "python_util.h"

#define BUFFER_SIZE 16

static void* H5VL_python_file_create(const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id, hid_t dxpl_id, void **req);
static herr_t H5VL_python_file_close(void *file, hid_t dxpl_id, void **req);

static void* H5VL_python_group_open(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, const char *name, hid_t gapl_id, hid_t dxpl_id, void **req);

static void* H5VL_python_dataset_create(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, const char *name, hid_t dcpl_id, hid_t dapl_id, hid_t dxpl_id, void **req);

static herr_t H5VL_python_dataset_read(void *dset, hid_t connector_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, void *buf, void **req);
static herr_t H5VL_python_dataset_write(void *dset, hid_t connector_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, const void *buf, void **req);

/* Generic Python VOL connector class struct */
static const H5VL_class_t H5VL_python_cls_g = {
	0,			/* version	*/
	500,			/* value		*/
	"PythonVOL",			/* name		 */
	0,			/* capability flags */
	NULL,			/* initialize */
	NULL,			/* terminate	*/
	{ /* info_cls */
		(size_t)1,			/* info size	*/	// TODO adjust to proper size
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
		NULL			/* close		*/
	},
	{ /* dataset_cls */
		H5VL_python_dataset_create,			/* create	 */
		NULL,			/* open		 */
		H5VL_python_dataset_read,			/* read		 */
		H5VL_python_dataset_write,			/* write		*/
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		NULL			/* close		*/
	},
	{ /* datatype_cls */
		NULL,			/* commit	 */
		NULL,			/* open		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		NULL			/* close		*/
	},
	{ /* file_cls */
		H5VL_python_file_create,			/* create	 */
		NULL,			/* open		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		H5VL_python_file_close			/* close		*/
	},
	{ /* group_cls */
		NULL,			/* create	 */
		H5VL_python_group_open,			/* open		 */
		NULL,			/* get		*/
		NULL,			/* specific	 */
		NULL,			/* optional	 */
		NULL			/* close		*/
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

PyObject* VOL_class;

static void* H5VL_python_file_create(const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id, hid_t dxpl_id, void **req)
{
	char *method_name = "H5VL_python_file_create";
	PyObject *ret = malloc(sizeof(PyObject)); 
	ret = PyObject_CallMethod(VOL_class, method_name, "slllll", name, flags, fcpl_id, fapl_id, dxpl_id, req);
	PyErr_Print();
	if(ret == NULL){
		return NULL;
	}
	return ret;
}

static herr_t H5VL_python_file_close(void *file, hid_t dxpl_id, void **req){
	return 1;
}

static void* H5VL_python_group_open(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, const char *name, hid_t gapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_group_open";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llslll", loc_params, connector_id, name, gapl_id, dxpl_id, req);
	PyErr_Print();
	if(ret == NULL){
		return NULL;
	}
	return ret;
}

static void* H5VL_python_dataset_create(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, const char *name, hid_t dcpl_id, hid_t dapl_id, hid_t dxpl_id, void **req){
	char *method_name = "H5VL_python_dataset_create";
	PyObject *ret = PyObject_CallMethod(obj, method_name, "llsllll", loc_params, connector_id, name, dcpl_id, dapl_id, dxpl_id, req);
	PyErr_Print();
	if(ret == NULL){
		return NULL;
	}
	return ret;
}

static herr_t H5VL_python_dataset_read(void *dset, hid_t connector_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, void *buf, void **req){
	char *method_name = "H5VL_python_dataset_read";
	PyArrayObject* array = PyObject_CallMethod(dset, method_name, "llllll", connector_id, mem_type_id, mem_space_id, file_space_id, plist_id, req);
	PyErr_Print();
	int **p = (int**)buf;
	*p = array->data;
	return 1;
}

static herr_t H5VL_python_dataset_write(void *dset, hid_t connector_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, const void *buf, void **req){
	const npy_intp buffer_size[] = {BUFFER_SIZE};
	char *method_name = "H5VL_python_dataset_write";
	import_array();
	PyObject* array = PyArray_SimpleNewFromData(1, buffer_size, NPY_INT32, buf);
	PyObject *ret = PyObject_CallMethod(dset, method_name, "lllllOl", connector_id, mem_type_id, mem_space_id, file_space_id, plist_id, array, req);
	PyErr_Print();
	return 1;
}

void fill_array(int* array, int size){
	for(int i = 0; i < size; i++){
		array[i] = i;
	}
}

void check_array(int* array, int size){
	for(int i = 0; i < size; i++){
		if(!array[i] == i){
			printf("ERROR: array check failed on index %d: %d", i, array[i]);
			exit(1);
		}
	}
}

// TODO refactorize tests in separate file
void test(){
	const char *module_name = "python_vol"; // TODO move outside
	char *class_name = "VOL"; // TODO move outside
	PyObject *file, *group, *dataset;
	PyObject* module = py_import_module(module_name);
	VOL_class = py_get_class(module, class_name);
	file = H5VL_python_file_create("aaa", 0, 0, 0, 0, 0);
	group = H5VL_python_group_open(file, 0, 0, "/", 0, 0, 0);
	dataset = H5VL_python_dataset_create(group, 0, 0, "dataset0", 0, 0, 0, 0);
	int *buffer = (int *)calloc(sizeof(int), BUFFER_SIZE);
	fill_array(buffer, 16);
	H5VL_python_dataset_write(dataset, 0, 0, 0, 0, 0, buffer, 0);
	int *dataset_buffer;
	H5VL_python_dataset_read(dataset, 0, 0, 0, 0, 0, &dataset_buffer, 0);
	check_array(dataset_buffer, 16);
}

#include <mpi.h>
typedef struct H5VL_python_fapl_t {
    MPI_Comm    comm; /*communicator*/
    MPI_Info    info; /*file information*/
}H5VL_python_fapl_t;

int main(){
	py_initialize();
	const char *module_name = "python_vol"; // TODO move outside
	char *class_name = "VOL"; // TODO move outside
	PyObject* module = py_import_module(module_name);
	VOL_class = py_get_class(module, class_name);

	hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
	hid_t vol_id = H5VLregister_connector(&H5VL_python_cls_g, H5P_DEFAULT);
	hid_t acc = H5Pcreate(H5P_FILE_ACCESS);
	H5VL_python_fapl_t fa;
	fa.comm = MPI_COMM_WORLD;
	fa.info = MPI_INFO_NULL;
	H5Pset_vol(acc, vol_id, &fapl);

	hid_t f = H5Fcreate("FILENAME.h5", H5F_ACC_TRUNC, H5P_DEFAULT, acc);
	H5Fclose(f);

	//test();

	py_finalize();
	return 0;
}

