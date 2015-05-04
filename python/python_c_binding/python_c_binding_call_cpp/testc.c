#include <stdio.h>
#include <Python.h>
#include "cppm.h"


static PyObject *Call_testc(PyObject *self, PyObject *args)
{
    cpp_method();
    Py_RETURN_TRUE;
}

static struct PyMethodDef testc_method[] = 
{
    {"testc", Call_testc, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

/* 
    In python the usage
    import testc from test
    testc()
*/

void inittestc(void)
{
    Py_InitModule("testc", testc_method);
}

