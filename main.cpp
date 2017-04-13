#include <Python.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
	Py_Initialize();
	if (!Py_IsInitialized()) {
		cout << "init error" << endl;
		return -1;
	}
	
	PyObject* pFile(0);
	pFile = PyString_FromString("leap");
	
	PyObject* pModule(0);
	pModule = PyImport_Import(pFile);
	if (!pModule) {
		cout << "can not find py file" << endl;
		return -1;
	}
	
	PyObject* pDct(0);
	pDct = PyModule_GetDict(pModule);
	if (!pDct) {
		cout << "pDct error" << endl;
	}
	
	PyObject* pStart(0);
	pStart = PyDict_GetItemString(pDct, "start");
	
	PyObject* pUpdate(0);
	pUpdate = PyDict_GetItemString(pDct, "update");
	
	//s 字符串 , 均是C 风格的字符串
	//i 整型
	//f 浮点数
	//o 表示一个 python 对象
	
	PyObject* pStartArgs(0);
	pStartArgs = PyTuple_New(0);
	PyObject_CallObject(pStart, pStartArgs);
	
	PyObject* pUpdateArgs(0);
	pUpdateArgs = PyTuple_New(2);
	PyTuple_SetItem(pUpdateArgs, 0, Py_BuildValue("i", 1));
	PyTuple_SetItem(pUpdateArgs, 1, Py_BuildValue("i", 2));
	PyObject* ret = PyObject_CallObject(pUpdate, pUpdateArgs);
	
	int result = PyInt_AS_LONG(ret);
	cout << result << endl;
	
	return 0;
}
