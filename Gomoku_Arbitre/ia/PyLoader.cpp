#include"stdafx.h"

#include "PyLoader.h"

PyLoader::PyLoader()
{
	Py_Initialize();
	PyRun_SimpleString("import sys; sys.path.insert(0, '.')");
}

PyLoader::~PyLoader()
{
	Py_DECREF(_module);
	Py_DECREF(_function);
	Py_DECREF(_value);
	Py_Finalize();
}

void PyLoader::PyLoadModule(std::string pyfile)
{
    _module = PyImport_Import(PyUnicode_DecodeFSDefault(pyfile.c_str()));
}

void PyLoader::PyLoadFunction(std::string function)
{
	_function = PyObject_GetAttrString(_module, function.c_str());
}

void PyLoader::PyCallFunction(PyObject* args)
{
	_value = PyObject_CallObject(_function, args);
}

long PyLoader::PyReturnFunctionLong()
{
	return (PyLong_AsLong(_value));
}

char* PyLoader::PyReturnFunctionString()
{
	return (PyBytes_AsString(_value));
}

int* PyLoader::PyReturnFunctionTuple()
{
	int* xy = new int;
	
	xy[0] = PyLong_AsLong(PyTuple_GetItem(_value, 0));
	xy[1] = PyLong_AsLong(PyTuple_GetItem(_value, 1));
	
	return (xy);
}

/*int main(int ac, char **av)
{
	PyLoader* pl = new PyLoader();
	
	pl->PyLoadModule("test");
	
	pl->PyLoadFunction("add");
	pl->PyCallFunction(PyTuple_Pack(2, PyLong_FromLong(3), PyLong_FromLong(4)));
	std::cout << "Return of function : " << pl->PyReturnFunctionLong() << std::endl;
	
	pl->PyLoadFunction("str");
	pl->PyCallFunction(PyTuple_Pack(1, PyBytes_FromString("Je test une fonction qui renvoit str")));
	std::cout << "Return of function : " << pl->PyReturnFunctionString() << std::endl;
	
	pl->PyLoadFunction("sendtuple");
	pl->PyCallFunction(PyTuple_Pack(0, NULL));
	int* xy = pl->PyReturnFunctionTuple();
	std::cout << "Return of function : " << xy[0] << ", " << xy[1] << std::endl;
	
	while (1);
	
	return 0;
}*/