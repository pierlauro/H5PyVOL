##### stdarg
cdef extern from "<stdarg.h>":
    ctypedef struct va_list:
        pass
    ctypedef struct fake_type:
        pass
    void va_start(va_list, void* arg)
    void* va_arg(va_list, fake_type)
    void va_end(va_list)
    fake_type int_type "int"
#####

### TO IMPORT
ctypedef long H5ES_status_t
ctypedef long H5I_type_t
ctypedef long H5_index_t
ctypedef long H5_iter_order_t

ctypedef long hsize_t
ctypedef long hid_t
ctypedef long herr_t
ctypedef long uint64_t
### /TO IMPORT

cdef extern from "<H5VLconnector.h>":
    cdef const int H5VL_MAX_TOKEN_SIZE = 16
    ctypedef unsigned char H5VL_token_t[H5VL_MAX_TOKEN_SIZE];
    
    # types for attribute GET callback #
    ctypedef enum H5VL_attr_get_t:
        H5VL_ATTR_GET_ACPL,                     # creation property list              #
        H5VL_ATTR_GET_INFO,                     # info                                #
        H5VL_ATTR_GET_NAME,                     # access property list                #
        H5VL_ATTR_GET_SPACE,                    # dataspace                           #
        H5VL_ATTR_GET_STORAGE_SIZE,             # storage size                        #
        H5VL_ATTR_GET_TYPE                      # datatype                            #
    
    # types for attribute SPECFIC callback #
    ctypedef enum H5VL_attr_specific_t:
        H5VL_ATTR_DELETE,                       # H5Adelete(_by_name/idx)             #
        H5VL_ATTR_EXISTS,                       # H5Aexists(_by_name)                 #
        H5VL_ATTR_ITER,                         # H5Aiterate(_by_name)                #
        H5VL_ATTR_RENAME                        # H5Arename(_by_name)                 #
    
    # types for dataset GET callback #
    ctypedef enum H5VL_dataset_get_t:
        H5VL_DATASET_GET_DAPL,                  # access property list                #
        H5VL_DATASET_GET_DCPL,                  # creation property list              #
        H5VL_DATASET_GET_OFFSET,                # offset                              #
        H5VL_DATASET_GET_SPACE,                 # dataspace                           #
        H5VL_DATASET_GET_SPACE_STATUS,          # space  status                       #
        H5VL_DATASET_GET_STORAGE_SIZE,          # storage size                        #
        H5VL_DATASET_GET_TYPE                   # datatype                            #
    
    # types for dataset SPECFIC callback #
    ctypedef enum H5VL_dataset_specific_t:
        H5VL_DATASET_SET_EXTENT,                # H5Dset_extent                       #
        H5VL_DATASET_FLUSH,                     # H5Dflush                            #
        H5VL_DATASET_REFRESH                    # H5Drefresh                          #
    
    # types for datatype GET callback #
    ctypedef enum H5VL_datatype_get_t:
        H5VL_DATATYPE_GET_BINARY,               # get serialized form of transient type    #
        H5VL_DATATYPE_GET_TCPL                  # datatype creation property list          #
    
    # types for datatype SPECFIC callback #
    ctypedef enum H5VL_datatype_specific_t:
        H5VL_DATATYPE_FLUSH,
        H5VL_DATATYPE_REFRESH

    # types for file GET callback #
    ctypedef enum H5VL_file_get_t:
        H5VL_FILE_GET_CONT_INFO,                # file get container info              #
        H5VL_FILE_GET_FAPL,                     # file access property list            #
        H5VL_FILE_GET_FCPL,                     # file creation property list          #
        H5VL_FILE_GET_FILENO,                   # file number                          #
        H5VL_FILE_GET_INTENT,                   # file intent                          #
        H5VL_FILE_GET_NAME,                     # file name                            #
        H5VL_FILE_GET_OBJ_COUNT,                # object count in file                 #
        H5VL_FILE_GET_OBJ_IDS                   # object ids in file                   #
    
    
    # types for file SPECIFIC callback #
    ctypedef enum H5VL_file_specific_t:
        H5VL_FILE_FLUSH,                        # Flush file                       #
        H5VL_FILE_REOPEN,                       # Reopen the file                  #
        H5VL_FILE_MOUNT,                        # Mount a file                     #
        H5VL_FILE_UNMOUNT,                      # Unmount a file                   #
        H5VL_FILE_IS_ACCESSIBLE,                # Check if a file is accessible    #
        H5VL_FILE_DELETE                        # Delete a file                    #
    
    
    # types for group GET callback #
    ctypedef enum H5VL_group_get_t:
        H5VL_GROUP_GET_GCPL,                    # group creation property list     #
        H5VL_GROUP_GET_INFO                     # group info                       #
    
    
    # types for group SPECFIC callback #
    ctypedef enum H5VL_group_specific_t:
        H5VL_GROUP_FLUSH,
        H5VL_GROUP_REFRESH

    
    # link create types for VOL #
    ctypedef enum H5VL_link_create_type_t:
        H5VL_LINK_CREATE_HARD,
        H5VL_LINK_CREATE_SOFT,
        H5VL_LINK_CREATE_UD
    
    
    # types for link GET callback #
    ctypedef enum H5VL_link_get_t:
        H5VL_LINK_GET_INFO,        # link info                         #
        H5VL_LINK_GET_NAME,        # link name                         #
        H5VL_LINK_GET_VAL          # link value                        #
    
    
    # types for link SPECIFIC callback #
    ctypedef enum H5VL_link_specific_t:
        H5VL_LINK_DELETE,          # H5Ldelete(_by_idx)                #
        H5VL_LINK_EXISTS,          # link existence                    #
        H5VL_LINK_ITER             # H5Literate/visit(_by_name)              #
    
    
    # types for object GET callback #
    ctypedef enum H5VL_object_get_t:
        H5VL_OBJECT_GET_NAME,              # object name                       #
        H5VL_OBJECT_GET_TYPE               # object type                       #
    
    
    # types for object SPECIFIC callback #
    ctypedef enum H5VL_object_specific_t:
        H5VL_OBJECT_CHANGE_REF_COUNT,       # H5Oincr/decr_refcount             #
        H5VL_OBJECT_EXISTS,                 # H5Oexists_by_name                 #
        H5VL_OBJECT_LOOKUP,                 # Lookup object                     #
        H5VL_OBJECT_VISIT,                  # H5Ovisit(_by_name)                #
        H5VL_OBJECT_FLUSH,                  # H5{D|G|O|T
        H5VL_OBJECT_REFRESH                 # H5{D|G|O|T
    
    
    # types for async request SPECIFIC callback #
    ctypedef enum H5VL_request_specific_t:
        H5VL_REQUEST_WAITANY,               # Wait until any request completes #
        H5VL_REQUEST_WAITSOME,              # Wait until at least one requesst completes #
        H5VL_REQUEST_WAITALL                # Wait until all requests complete #
    
    
    # types for 'blob' SPECIFIC callback #
    ctypedef enum H5VL_blob_specific_t:
        H5VL_BLOB_DELETE,                   # Delete a blob (by ID) #
        H5VL_BLOB_GETSIZE,                  # Get size of blob #
        H5VL_BLOB_ISNULL,                   # Check if a blob ID is "null" #
        H5VL_BLOB_SETNULL                   # Set a blob ID to the connector's "null" blob ID value #

    ctypedef enum H5VL_loc_type_t:
        H5VL_OBJECT_BY_SELF,
        H5VL_OBJECT_BY_NAME,
        H5VL_OBJECT_BY_IDX,
        H5VL_OBJECT_BY_TOKEN

    ctypedef struct H5VL_loc_by_name_t:
        const char *name;
        hid_t lapl_id;
    ctypedef H5VL_loc_by_name_t H5VL_loc_by_name
    
    ctypedef struct H5VL_loc_by_idx_t:
        const char *name;
        H5_index_t idx_type;
        H5_iter_order_t order;
        hsize_t n;
        hid_t lapl_id;
    ctypedef H5VL_loc_by_idx_t H5VL_loc_by_idx
    
    ctypedef struct H5VL_loc_by_token_t:
        void *token;
    ctypedef H5VL_loc_by_token_t H5VL_loc_by_token
    
    #
    # Structure to hold parameters for object locations.
    # Either: BY_SELF, BY_NAME, BY_IDX, BY_TOKEN
    #
    # Note: Leave loc_by_token as the first union member so we
    #       can perform the simplest initialization of the struct
    #       without raising warnings.
    #
    # Note: BY_SELF requires no union members.
    #
    ctypedef union H5VL_loc_params_t_union:
        H5VL_loc_by_token_t     loc_by_token;
        H5VL_loc_by_name_t      loc_by_name;
        H5VL_loc_by_idx_t       loc_by_idx;
    
    ctypedef struct H5VL_loc_params_t:
        H5I_type_t      obj_type;
        H5VL_loc_type_t type;
        H5VL_loc_params_t_union H5VL_loc_params_t

    
    # Info for H5VL_FILE_GET_CONT_INFO #
    ctypedef struct H5VL_file_cont_info_t:
        unsigned version;                   # version information (keep first) #
        uint64_t feature_flags;             # Container feature flags          #
                                            # (none currently defined)         #
        size_t token_size;                  # Size of tokens                   #
        size_t blob_id_size;                # Size of blob IDs                 #

    
    # VOL connector info fields & callbacks #
    ctypedef struct H5VL_info_class_t:
        size_t size;                                    # Size of the VOL info                         #
        void * (*copy)(const void *info);               # Callback to create a copy of the VOL info    #
        herr_t (*cmp)(int *cmp_value, const void *info1, const void *info2); # Callback to compare VOL info #
        herr_t (*free)(void *info);                     # Callback to release a VOL info               #
        herr_t (*to_str)(const void *info, char **str); # Callback to serialize connector's info into a string #
        herr_t (*from_str)(const char *str, void **info); # Callback to deserialize a string into connector's info #

    
    # VOL object wrap / retrieval callbacks #
    # (These only need to be implemented by "pass through" VOL connectors) #
    ctypedef struct H5VL_wrap_class_t:
        void * (*get_object)(const void *obj);          # Callback to retrieve underlying object       #
        herr_t (*get_wrap_ctx)(const void *obj, void **wrap_ctx); # Callback to retrieve the object wrapping context for the connector #
        void * (*wrap_object)(void *obj, H5I_type_t obj_type, void *wrap_ctx); # Callback to wrap a library object #
        void * (*unwrap_object)(void *obj);             # Callback to unwrap a library object #
        herr_t (*free_wrap_ctx)(void *wrap_ctx);        # Callback to release the object wrapping context for the connector #

    
    # H5A routines #
    ctypedef struct H5VL_attr_class_t:
        void *(*create)(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name,
                hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id,
                hid_t dxpl_id, void **req);
        void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char *attr_name,
                      hid_t aapl_id, hid_t dxpl_id, void **req);
        herr_t (*read)(void *attr, hid_t mem_type_id, void *buf, hid_t dxpl_id, void **req);
        herr_t (*write)(void *attr, hid_t mem_type_id, const void *buf, hid_t dxpl_id, void **req);
        herr_t (*get)(void *obj, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_attr_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*close) (void *attr, hid_t dxpl_id, void **req);

    
    # H5D routines #
    ctypedef struct H5VL_dataset_class_t:
        void *(*create)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
                hid_t lcpl_id, hid_t type_id, hid_t space_id, hid_t dcpl_id,
                hid_t dapl_id, hid_t dxpl_id, void **req);
        void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
                      hid_t dapl_id, hid_t dxpl_id, void **req);
        herr_t (*read)(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id,
                       hid_t xfer_plist_id, void * buf, void **req);
        herr_t (*write)(void *dset, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id,
                        hid_t xfer_plist_id, const void * buf, void **req);
        herr_t (*get)(void *obj, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, H5VL_dataset_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*close) (void *dset, hid_t dxpl_id, void **req);

    
    # H5T routines#
    ctypedef struct H5VL_datatype_class_t:
        void *(*commit)(void *obj, const H5VL_loc_params_t *loc_params, const char *name, hid_t type_id,
                        hid_t lcpl_id, hid_t tcpl_id, hid_t tapl_id, hid_t dxpl_id, void **req);
        void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char * name,
                      hid_t tapl_id, hid_t dxpl_id, void **req);
        herr_t (*get)   (void *obj, H5VL_datatype_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, H5VL_datatype_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*close) (void *dt, hid_t dxpl_id, void **req);

    
    # H5F routines #
    ctypedef struct H5VL_file_class_t:
        void *(*create)(const char *name, unsigned flags, hid_t fcpl_id,
                        hid_t fapl_id, hid_t dxpl_id, void **req);
        void *(*open)(const char *name, unsigned flags, hid_t fapl_id, hid_t dxpl_id, void **req);
        herr_t (*get)(void *obj, H5VL_file_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, H5VL_file_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*close) (void *file, hid_t dxpl_id, void **req);

    
    # H5G routines #
    ctypedef struct H5VL_group_class_t:
        void *(*create)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
            hid_t lcpl_id, hid_t gcpl_id, hid_t gapl_id, hid_t dxpl_id, void **req);
        void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, const char *name,
                      hid_t gapl_id, hid_t dxpl_id, void **req);
        herr_t (*get)(void *obj, H5VL_group_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, H5VL_group_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*close) (void *grp, hid_t dxpl_id, void **req);

    
    # H5L routines #
    ctypedef struct H5VL_link_class_t:
        herr_t (*create)(H5VL_link_create_type_t create_type, void *obj, const H5VL_loc_params_t *loc_params,
                hid_t lcpl_id, hid_t lapl_id, hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*copy)(void *src_obj, const H5VL_loc_params_t *loc_params1,
                       void *dst_obj, const H5VL_loc_params_t *loc_params2,
                       hid_t lcpl, hid_t lapl, hid_t dxpl_id, void **req);
        herr_t (*move)(void *src_obj, const H5VL_loc_params_t *loc_params1,
                       void *dst_obj, const H5VL_loc_params_t *loc_params2,
                       hid_t lcpl, hid_t lapl, hid_t dxpl_id, void **req);
        herr_t (*get)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_link_get_t get_type,
                      hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_link_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);

    
    # H5O routines #
    ctypedef struct H5VL_object_class_t:
        void *(*open)(void *obj, const H5VL_loc_params_t *loc_params, H5I_type_t *opened_type,
                      hid_t dxpl_id, void **req);
        herr_t (*copy)(void *src_obj, const H5VL_loc_params_t *loc_params1, const char *src_name,
                       void *dst_obj, const H5VL_loc_params_t *loc_params2, const char *dst_name,
                       hid_t ocpypl_id, hid_t lcpl_id, hid_t dxpl_id, void **req);
        herr_t (*get)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_object_get_t get_type,
                      hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*specific)(void *obj, const H5VL_loc_params_t *loc_params, H5VL_object_specific_t specific_type,
                           hid_t dxpl_id, void **req, va_list arguments);
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments);

    
    # Asynchronous request 'notify' callback #
    ctypedef herr_t (*H5VL_request_notify_t)(void *ctx, H5ES_status_t status);
    
    # Async request operation routines #
    ctypedef struct H5VL_request_class_t:
        herr_t (*wait)(void *req, uint64_t timeout, H5ES_status_t *status);
        herr_t (*notify)(void *req, H5VL_request_notify_t cb, void *ctx);
        herr_t (*cancel)(void *req);
        herr_t (*specific)(void *req, H5VL_request_specific_t specific_type, va_list arguments);
        herr_t (*optional)(void *req, va_list arguments);
        herr_t (*free)(void *req);

    
    # 'blob' routines #
    ctypedef struct H5VL_blob_class_t:
        herr_t (*put)(void *obj, const void *buf, size_t size, void *blob_id, void *ctx);
        herr_t (*get)(void *obj, const void *blob_id, void *buf, size_t *size, void *ctx);
        herr_t (*specific)(void *obj, void *blob_id, H5VL_blob_specific_t specific_type, va_list arguments);
        herr_t (*optional)(void *obj, void *blob_id, va_list arguments);

    
    #
    # VOL connector identifiers.  Values 0 through 255 are for connectors defined
    # by the HDF5 library.  Values 256 through 511 are available for testing new
    # filters.  Subsequent values should be obtained from the HDF5 development
    # team at help@hdfgroup.org.
    #
    ctypedef int H5VL_class_value_t;
    
    # Class information for each VOL connector #
    ctypedef struct H5VL_class_t:
        # Overall connector fields & callbacks #
        unsigned int version;                   # VOL connector class struct version #     #
        H5VL_class_value_t value;               # Value to identify connector              #
        const char *name;                       # Connector name (MUST be unique!)         #
        unsigned cap_flags;                     # Capability flags for connector           #
        herr_t (*initialize)(hid_t vipl_id);    # Connector initialization callback        #
        herr_t (*terminate)();              # Connector termination callback           #
    
        # VOL framework #
        H5VL_info_class_t       info_cls;       # VOL info fields & callbacks  #
        H5VL_wrap_class_t       wrap_cls;       # VOL object wrap / retrieval callbacks #
    
        # Data Model #
        H5VL_attr_class_t       attr_cls;       # Attribute (H5A*) class callbacks #
        H5VL_dataset_class_t    dataset_cls;    # Dataset (H5D*) class callbacks   #
        H5VL_datatype_class_t   datatype_cls;   # Datatype (H5T*) class callbacks  #
        H5VL_file_class_t       file_cls;       # File (H5F*) class callbacks      #
        H5VL_group_class_t      group_cls;      # Group (H5G*) class callbacks     #
        H5VL_link_class_t       link_cls;       # Link (H5L*) class callbacks      #
        H5VL_object_class_t     object_cls;     # Object (H5O*) class callbacks    #
    
        # Infrastructure / Services #
        H5VL_request_class_t    request_cls;    # Asynchronous request class callbacks #
        H5VL_blob_class_t       blob_cls;       # 'blob' callbacks #
    
        # Catch-all #
        herr_t (*optional)(void *obj, hid_t dxpl_id, void **req, va_list arguments); # Optional callback #

