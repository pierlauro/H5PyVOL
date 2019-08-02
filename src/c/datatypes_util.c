#include <stdlib.h>

#include "datatypes_util.h" 
#include "python_util.h"

void build_mapping();
int get_mapping(hid_t type_id);

#define NTYPES 128

/*
	Those very ugly procedures are needed in order to build at runtime a
	constant-time lookup structure for HDF5 -> numpy datatypes mapping.
	
	The most reasonable solution - that would have been a simple switch
	over the types - is not applicable since types are declared through
	preprocessor definitions (label does not reduce to an integer constant).
*/

static int *numpy_mapping = NULL;

int get_numpy_type(hid_t type_id){
	if(numpy_mapping == NULL){
		// Lazy initialization
		build_mapping();
	}
	return numpy_mapping[(int)type_id];
}

/* Read the explanation in the head if you're wondering why such an unusual design */
void build_mapping(){
	hid_t types[NTYPES] = {H5T_IEEE_F32BE, H5T_IEEE_F32LE, H5T_IEEE_F64BE, H5T_IEEE_F64LE, H5T_STD_I8BE, H5T_STD_I8LE, H5T_STD_I16BE, H5T_STD_I16LE, H5T_STD_I32BE, H5T_STD_I32LE, H5T_STD_I64BE, H5T_STD_I64LE, H5T_STD_U8BE, H5T_STD_U8LE, H5T_STD_U16BE, H5T_STD_U16LE, H5T_STD_U32BE, H5T_STD_U32LE, H5T_STD_U64BE, H5T_STD_U64LE, H5T_STD_B8BE, H5T_STD_B8LE, H5T_STD_B16BE, H5T_STD_B16LE, H5T_STD_B32BE, H5T_STD_B32LE, H5T_STD_B64BE, H5T_STD_B64LE, H5T_STD_REF_OBJ, H5T_STD_REF_DSETREG, H5T_UNIX_D32BE, H5T_UNIX_D32LE, H5T_UNIX_D64BE, H5T_UNIX_D64LE, H5T_C_S1, H5T_FORTRAN_S1, H5T_INTEL_I8, H5T_INTEL_I16, H5T_INTEL_I32, H5T_INTEL_I64, H5T_INTEL_U8, H5T_INTEL_U16, H5T_INTEL_U32, H5T_INTEL_U64, H5T_INTEL_B8, H5T_INTEL_B16, H5T_INTEL_B32, H5T_INTEL_B64, H5T_INTEL_F32, H5T_INTEL_F64, H5T_ALPHA_I8, H5T_ALPHA_I16, H5T_ALPHA_I32, H5T_ALPHA_I64, H5T_ALPHA_U8, H5T_ALPHA_U16, H5T_ALPHA_U32, H5T_ALPHA_U64, H5T_ALPHA_B8, H5T_ALPHA_B16, H5T_ALPHA_B32, H5T_ALPHA_B64, H5T_ALPHA_F32, H5T_ALPHA_F64, H5T_MIPS_I8, H5T_MIPS_I16, H5T_MIPS_I32, H5T_MIPS_I64, H5T_MIPS_U8, H5T_MIPS_U16, H5T_MIPS_U32, H5T_MIPS_U64, H5T_MIPS_B8, H5T_MIPS_B16, H5T_MIPS_B32, H5T_MIPS_B64, H5T_MIPS_F32, H5T_MIPS_F64, H5T_VAX_F32, H5T_VAX_F64, H5T_NATIVE_CHAR, H5T_NATIVE_SCHAR, H5T_NATIVE_UCHAR, H5T_NATIVE_SHORT, H5T_NATIVE_USHORT, H5T_NATIVE_INT, H5T_NATIVE_UINT, H5T_NATIVE_LONG, H5T_NATIVE_ULONG, H5T_NATIVE_LLONG, H5T_NATIVE_ULLONG, H5T_NATIVE_FLOAT, H5T_NATIVE_DOUBLE, H5T_NATIVE_LDOUBLE, H5T_NATIVE_B8, H5T_NATIVE_B16, H5T_NATIVE_B32, H5T_NATIVE_B64, H5T_NATIVE_OPAQUE, H5T_NATIVE_HADDR, H5T_NATIVE_HSIZE, H5T_NATIVE_HSSIZE, H5T_NATIVE_HERR, H5T_NATIVE_HBOOL, H5T_NATIVE_INT8, H5T_NATIVE_UINT8, H5T_NATIVE_INT_LEAST8, H5T_NATIVE_UINT_LEAST8, H5T_NATIVE_INT_FAST8, H5T_NATIVE_UINT_FAST8, H5T_NATIVE_INT16, H5T_NATIVE_UINT16, H5T_NATIVE_INT_LEAST16, H5T_NATIVE_UINT_LEAST16, H5T_NATIVE_INT_FAST16, H5T_NATIVE_UINT_FAST16, H5T_NATIVE_INT32, H5T_NATIVE_UINT32, H5T_NATIVE_INT_LEAST32, H5T_NATIVE_UINT_LEAST32, H5T_NATIVE_INT_FAST32, H5T_NATIVE_UINT_FAST32, H5T_NATIVE_INT64, H5T_NATIVE_UINT64, H5T_NATIVE_INT_LEAST64, H5T_NATIVE_UINT_LEAST64, H5T_NATIVE_INT_FAST64, H5T_NATIVE_UINT_FAST64};
	numpy_mapping = malloc(sizeof(int) * NTYPES);
	int i;
	for(i = 0; i < NTYPES; i++){
		numpy_mapping[(int)types[i]] = get_mapping(types[i]);
	}
}

/* Read the explanation in the head if you're wondering why such an unusual design */
int get_mapping(hid_t type_id){
	// TODO assign numpy type to unassigned type ids (-1)
	// TODO manage endianess in numpy arrays
	if(type_id == H5T_IEEE_F32BE) return NPY_FLOAT32;
	if(type_id == H5T_IEEE_F32LE) return NPY_FLOAT32;
	if(type_id == H5T_IEEE_F64BE) return NPY_FLOAT64;
	if(type_id == H5T_IEEE_F64LE) return NPY_FLOAT64;
	if(type_id == H5T_STD_I8BE) return NPY_INT8;
	if(type_id == H5T_STD_I8LE) return NPY_INT8;
	if(type_id == H5T_STD_I16BE) return NPY_INT16;
	if(type_id == H5T_STD_I16LE) return NPY_INT16;
	if(type_id == H5T_STD_I32BE) return NPY_INT32;
	if(type_id == H5T_STD_I32LE) return NPY_INT32;
	if(type_id == H5T_STD_I64BE) return NPY_INT64;
	if(type_id == H5T_STD_I64LE) return NPY_INT64;
	if(type_id == H5T_STD_U8BE) return NPY_UINT8;
	if(type_id == H5T_STD_U8LE) return NPY_UINT8;
	if(type_id == H5T_STD_U16BE) return NPY_UINT16;
	if(type_id == H5T_STD_U16LE) return NPY_UINT16;
	if(type_id == H5T_STD_U32BE) return NPY_UINT32;
	if(type_id == H5T_STD_U32LE) return NPY_UINT32;
	if(type_id == H5T_STD_U64BE) return NPY_UINT64;
	if(type_id == H5T_STD_U64LE) return NPY_UINT64;
	if(type_id == H5T_STD_B8BE) return NPY_UINT8;
	if(type_id == H5T_STD_B8LE) return NPY_UINT8;
	if(type_id == H5T_STD_B16BE) return NPY_UINT16;
	if(type_id == H5T_STD_B16LE) return NPY_UINT16;
	if(type_id == H5T_STD_B32BE) return NPY_UINT32;
	if(type_id == H5T_STD_B32LE) return NPY_UINT32;
	if(type_id == H5T_STD_B64BE) return NPY_UINT64;
	if(type_id == H5T_STD_B64LE) return -1;
	if(type_id == H5T_STD_REF_OBJ) return -1;
	if(type_id == H5T_STD_REF_DSETREG) return -1;
	if(type_id == H5T_UNIX_D32BE) return -1;
	if(type_id == H5T_UNIX_D32LE) return -1;
	if(type_id == H5T_UNIX_D64BE) return -1;
	if(type_id == H5T_UNIX_D64LE) return -1;
	if(type_id == H5T_C_S1) return -1;
	if(type_id == H5T_FORTRAN_S1) return -1;
	if(type_id == H5T_INTEL_I8) return NPY_INT8;
	if(type_id == H5T_INTEL_I16) return NPY_INT16;
	if(type_id == H5T_INTEL_I32) return NPY_INT32;
	if(type_id == H5T_INTEL_I64) return NPY_INT64;
	if(type_id == H5T_INTEL_U8) return NPY_UINT8;
	if(type_id == H5T_INTEL_U16) return NPY_UINT16;
	if(type_id == H5T_INTEL_U32) return NPY_UINT32;
	if(type_id == H5T_INTEL_U64) return NPY_UINT64;
	if(type_id == H5T_INTEL_B8) return NPY_UINT8;
	if(type_id == H5T_INTEL_B16) return NPY_UINT16;
	if(type_id == H5T_INTEL_B32) return NPY_UINT32;
	if(type_id == H5T_INTEL_B64) return NPY_UINT64;
	if(type_id == H5T_INTEL_F32) return NPY_FLOAT32;
	if(type_id == H5T_INTEL_F64) return NPY_FLOAT64;
	if(type_id == H5T_ALPHA_I8) return NPY_INT8;
	if(type_id == H5T_ALPHA_I16) return NPY_INT16;
	if(type_id == H5T_ALPHA_I32) return NPY_INT32;
	if(type_id == H5T_ALPHA_I64) return NPY_INT64;
	if(type_id == H5T_ALPHA_U8) return NPY_UINT8;
	if(type_id == H5T_ALPHA_U16) return NPY_UINT16;
	if(type_id == H5T_ALPHA_U32) return NPY_UINT32;
	if(type_id == H5T_ALPHA_U64) return NPY_UINT64;
	if(type_id == H5T_ALPHA_B8) return NPY_UINT8;
	if(type_id == H5T_ALPHA_B16) return NPY_UINT16;
	if(type_id == H5T_ALPHA_B32) return NPY_UINT32;
	if(type_id == H5T_ALPHA_B64) return NPY_UINT64;
	if(type_id == H5T_ALPHA_F32) return NPY_FLOAT32;
	if(type_id == H5T_ALPHA_F64) return NPY_FLOAT64;
	if(type_id == H5T_MIPS_I8) return NPY_INT8;
	if(type_id == H5T_MIPS_I16) return NPY_INT16;
	if(type_id == H5T_MIPS_I32) return NPY_INT32;
	if(type_id == H5T_MIPS_I64) return NPY_INT64;
	if(type_id == H5T_MIPS_U8) return NPY_UINT8;
	if(type_id == H5T_MIPS_U16) return NPY_UINT16;
	if(type_id == H5T_MIPS_U32) return NPY_UINT32;
	if(type_id == H5T_MIPS_U64) return NPY_UINT64;
	if(type_id == H5T_MIPS_B8) return NPY_UINT8;
	if(type_id == H5T_MIPS_B16) return NPY_UINT16;
	if(type_id == H5T_MIPS_B32) return NPY_UINT32;
	if(type_id == H5T_MIPS_B64) return NPY_UINT64;
	if(type_id == H5T_MIPS_F32) return NPY_FLOAT32;
	if(type_id == H5T_MIPS_F64) return NPY_FLOAT64;
	if(type_id == H5T_VAX_F32) return NPY_FLOAT32;
	if(type_id == H5T_VAX_F64) return NPY_FLOAT64;
	if(type_id == H5T_NATIVE_CHAR) return -1;
	if(type_id == H5T_NATIVE_SCHAR) return -1;
	if(type_id == H5T_NATIVE_UCHAR) return -1;
	if(type_id == H5T_NATIVE_SHORT) return NPY_INT16;
	if(type_id == H5T_NATIVE_USHORT) return NPY_UINT16;
	if(type_id == H5T_NATIVE_INT) return NPY_INT32;
	if(type_id == H5T_NATIVE_UINT) return NPY_UINT32;
	if(type_id == H5T_NATIVE_LONG) return NPY_INT64;
	if(type_id == H5T_NATIVE_ULONG) return NPY_UINT64;
	if(type_id == H5T_NATIVE_LLONG) return NPY_INT64;
	if(type_id == H5T_NATIVE_ULLONG) return NPY_UINT64;
	if(type_id == H5T_NATIVE_FLOAT) return NPY_FLOAT32;
	if(type_id == H5T_NATIVE_DOUBLE) return NPY_FLOAT64;
	if(type_id == H5T_NATIVE_LDOUBLE) return NPY_FLOAT64;
	if(type_id == H5T_NATIVE_B8) return NPY_UINT8;
	if(type_id == H5T_NATIVE_B16) return NPY_UINT16;
	if(type_id == H5T_NATIVE_B32) return NPY_UINT32;
	if(type_id == H5T_NATIVE_B64) return NPY_UINT64;
	if(type_id == H5T_NATIVE_OPAQUE) return -1;
	if(type_id == H5T_NATIVE_HADDR) return -1;
	if(type_id == H5T_NATIVE_HSIZE) return -1;
	if(type_id == H5T_NATIVE_HSSIZE) return -1;
	if(type_id == H5T_NATIVE_HERR) return -1;
	if(type_id == H5T_NATIVE_HBOOL) return NPY_BOOL;
	if(type_id == H5T_NATIVE_INT8) return NPY_INT8;
	if(type_id == H5T_NATIVE_UINT8) return NPY_UINT8;
	if(type_id == H5T_NATIVE_INT_LEAST8) return NPY_INT8;
	if(type_id == H5T_NATIVE_UINT_LEAST8) return NPY_UINT8;
	if(type_id == H5T_NATIVE_INT_FAST8) return NPY_INT8;
	if(type_id == H5T_NATIVE_UINT_FAST8) return NPY_UINT8;
	if(type_id == H5T_NATIVE_INT16) return NPY_INT16;
	if(type_id == H5T_NATIVE_UINT16) return NPY_UINT16;
	if(type_id == H5T_NATIVE_INT_LEAST16) return NPY_INT16;
	if(type_id == H5T_NATIVE_UINT_LEAST16) return NPY_UINT16;
	if(type_id == H5T_NATIVE_INT_FAST16) return NPY_INT16;
	if(type_id == H5T_NATIVE_UINT_FAST16) return NPY_UINT16;
	if(type_id == H5T_NATIVE_INT32) return NPY_INT32;
	if(type_id == H5T_NATIVE_UINT32) return NPY_UINT32;
	if(type_id == H5T_NATIVE_INT_LEAST32) return NPY_INT32;
	if(type_id == H5T_NATIVE_UINT_LEAST32) return NPY_UINT32;
	if(type_id == H5T_NATIVE_INT_FAST32) return NPY_INT32;
	if(type_id == H5T_NATIVE_UINT_FAST32) return NPY_UINT32;
	if(type_id == H5T_NATIVE_INT64) return NPY_INT64;
	if(type_id == H5T_NATIVE_UINT64) return NPY_UINT64;
	if(type_id == H5T_NATIVE_INT_LEAST64) return NPY_INT64;
	if(type_id == H5T_NATIVE_UINT_LEAST64) return NPY_UINT64;
	if(type_id == H5T_NATIVE_INT_FAST64) return NPY_INT64;
	if(type_id == H5T_NATIVE_UINT_FAST64) return NPY_UINT64;
}
