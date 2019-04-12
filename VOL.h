#include <mpi.h>

#include <H5VLpublic.h>
#include <H5Ppublic.h>

#include "python_util.h"

#define BUFFER_SIZE 16

typedef struct H5VL_python_fapl_t {
    MPI_Comm    comm; /*communicator*/
    MPI_Info    info; /*file information*/
}H5VL_python_fapl_t;

extern const H5VL_class_t H5VL_python_cls_g;

extern void* H5VL_python_file_create(const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_file_close(void *file, hid_t dxpl_id, void **req);

extern void* H5VL_python_group_open(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, const char *name, hid_t gapl_id, hid_t dxpl_id, void **req);

extern void* H5VL_python_dataset_create(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, const char *name, hid_t dcpl_id, hid_t dapl_id, hid_t dxpl_id, void **req);

extern herr_t H5VL_python_dataset_read(void *dset, hid_t connector_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, void *buf, void **req);
extern herr_t H5VL_python_dataset_write(void *dset, hid_t connector_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, const void *buf, void **req);

PyObject* VOL_class; // TODO move

static void initialize_vol_class(const char* module_name, const char* class_name){
	PyObject* module = py_import_module(module_name);
	VOL_class = py_get_class(module, class_name);
}
