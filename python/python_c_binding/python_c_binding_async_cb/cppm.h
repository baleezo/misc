#ifndef __CPP_M_H
#define __CPP_M_H
#include <Python.h>
#ifdef __cplusplus
extern "C"
{
#endif

extern PyObject *testcErr;

PyObject *cpp_method(PyObject *cb);

#ifdef __cplusplus
}
#endif
#endif
