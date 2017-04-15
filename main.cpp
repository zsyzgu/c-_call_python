#include <Python.h>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int FEATURES_LEN = 768;
const int HAND_DATA_LEN = 60;

PyObject *pFunc;

void pyInit() {
	Py_Initialize();
	if (!Py_IsInitialized()) {
		cout << "init error" << endl;
		return;
	}
	
	PyObject *pFile, *pModule, *pDct;
	pFile = PyString_FromString("leap");
	
	pModule = PyImport_Import(pFile);
	if (!pModule) {
		cout << "can not find py file" << endl;
		return;
	}
	
	pDct = PyModule_GetDict(pModule);
	if (!pDct) {
		cout << "pDct error" << endl;
	}
	
	pFunc = PyDict_GetItemString(pDct, "get_hand_data");
}

extern "C" __declspec(dllexport) int* getImageFeatures() {
	static int features[FEATURES_LEN];
	
	//TODO
	for (int i = 0; i < FEATURES_LEN; i++) {
		features[i] = i;
	}
	//END
	
	return features;
}

extern "C" __declspec(dllexport) int* getHandData() {	
	int* features = getImageFeatures();
	PyObject* pUpdateArgs = PyTuple_New(FEATURES_LEN);
	for (int i = 0; i < FEATURES_LEN; i++) {
		PyTuple_SetItem(pUpdateArgs, i, Py_BuildValue("i", features[i]));
	}
	PyObject* pHandData = PyObject_CallObject(pFunc, pUpdateArgs);
	static int handData[HAND_DATA_LEN];
	for (int i = 0; i < HAND_DATA_LEN; i++) {
		PyObject* result = PyList_GetItem(pHandData, i);
		handData[i] = PyInt_AS_LONG(result);
	}
	return handData;
}

int main() {
	pyInit();
	getHandData();
	
	return 0;
}
