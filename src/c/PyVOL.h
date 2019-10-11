#include <mpi.h>

#include <H5PLextern.h>
#include <H5Spublic.h>
#include <H5VLpublic.h>

#include "datatypes_util.h"
#include "python_util.h"

#define PyHDFVolVersion 1
#define PyHDFVolValue 345
#define PyHDFVol "PyHDFVol"
#define PyHDFVolModule "PyHDFVolModule"
#define PyHDFVolClass "PyHDFVolClass"

typedef struct H5VL_python_fapl_t {
    MPI_Comm    comm; /*communicator*/
    MPI_Info    info; /*file information*/
} H5VL_python_fapl_t;

extern const H5VL_class_t H5VL_python_cls_g;
extern const H5VL_attr_class_t PyHDFVOL_attribute_class;
extern PyObject* VOL_class;

extern herr_t H5VL_python_object_close(void *grp, hid_t dxpl_id, void **req);

extern void H5VL_python_attribute_create(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name, hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id, hid_t dxpl_id, void **req);
extern void H5VL_python_attribute_open(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name, hid_t aapl_id, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_attribute_read(void *attr, hid_t mem_type_id, void *buf, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_attribute_write(void *attr, hid_t mem_type_id, const void *buf, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_attribute_get(void *obj, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_attribute_specific(void *obj, const H5VL_loc_params_t *loc_params, H5VL_attr_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_attribute_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_attribute_close(void *attr, hid_t dxpl_id, void **req);

extern herr_t H5VL_python_datatype_close(void *dt, hid_t dxpl_id, void **req);

extern void* H5VL_python_file_create(const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id, hid_t dxpl_id, void **req);
extern void* H5VL_python_file_open(const char *name, unsigned flags, hid_t fapl_id, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_file_get(void *obj, H5VL_file_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_file_specific(void *obj, H5VL_file_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_file_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_file_close(void *file, hid_t dxpl_id, void **req);

extern void* H5VL_python_group_create(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t gcpl_id, hid_t gapl_id, hid_t dxpl_id, void **req);
extern void* H5VL_python_group_open(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t gapl_id, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_group_get(void *obj, H5VL_group_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_group_specific(void *obj, H5VL_group_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_group_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_group_close(void *grp, hid_t dxpl_id, void **req);

extern void* H5VL_python_dataset_create(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t dcpl_id, hid_t dapl_id, hid_t dxpl_id, void **req);
extern void* H5VL_python_dataset_open(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t dapl_id, hid_t dxpl_id, void **req);
extern herr_t H5VL_python_dataset_read(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t xfer_plist_id, void * buf, void **req);
extern herr_t H5VL_python_dataset_write(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t xfer_plist_id, const void * buf, void **req);
extern herr_t H5VL_python_dataset_get(void *obj, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_dataset_specific(void *obj, H5VL_dataset_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_dataset_optional(void *obj, hid_t dxpl_id, void **req, va_list arguments);
extern herr_t H5VL_python_dataset_close(void *dset, hid_t dxpl_id, void **req);

extern void initialize_vol_class(const char* module_name, const char* class_name);
extern herr_t H5VL_python_init(hid_t vipl_id);
extern herr_t H5VL_python_term(void);
