#include <Python.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

void py_initialize();
void py_finalize();
PyObject* py_import_module(const char *name);
PyObject* py_get_class(PyObject* module, const char *name);

