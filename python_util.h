void py_initialize();
void py_finalize();
PyObject* py_import_module(const char *name);
PyObject* py_get_class(PyObject* module, const char *name);

