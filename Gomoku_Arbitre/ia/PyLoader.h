#ifndef PYLOADER_H_
# define PYLOADER_H_

#include "include\Python.h"
#include <iostream>
#include <fstream>
#include <string>

class PyLoader
{
	private:
		PyObject* _module;
		PyObject* _function;
		PyObject* _value;
		
	public:
		PyLoader();
		~PyLoader();
		void PyLoadModule(std::string pyfile);
		void PyLoadFunction(std::string function);
		void PyCallFunction(PyObject* args);
		long PyReturnFunctionLong();
		char* PyReturnFunctionString();
		int* PyReturnFunctionTuple();
};

#endif /* PYLOADER_H_ */