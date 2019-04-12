#include "python_util.h"

void py_initialize(){
	// Initiale the Python interpreter
	Py_Initialize();

	// Add python_vol module to the system path
	char *module_path = ".";
	PyObject *sysPath = PySys_GetObject("path");
	PyObject *path = PyUnicode_FromString(module_path);
	int result = PyList_Insert(sysPath, 0, path);
	if(result != 0){
		printf("Python interpreter initialization failed, cannot add %s to the system path\n", module_path);
		exit(result);
	}
}

void py_finalize(){
	// Finalize the Python interpreter
	int result = Py_FinalizeEx();
	if(result != 0){
		printf("Python interpreter finalization failed");
		exit(result);
	}
}

PyObject* py_import_module(const char *name){
	// Import a Python module
	PyObject* module = PyImport_ImportModule(name);
	if(module == NULL){
		printf("Python module %s import failed", name);
		exit(1);
	}
	return module;
}

PyObject* py_get_class(PyObject* module, const char *name){
	// Get a Python class
	PyObject* class = PyObject_CallMethod(module, name, NULL, NULL);
	if(class == NULL){
		printf("New class instance failed\n");
		exit(0);
	}
	return class;
}
