#include <stdio.h>
#include <glib.h>
#include "cppm.h"

PyObject *testcErr = NULL;

static PyObject *Call_testc(PyObject *self, PyObject *args)
{
    PyObject *cb = NULL, *errb = NULL, *userdata = NULL;
    if (!PyArg_ParseTuple(args, "O|O|O", &cb, &errb, &userdata))
    {
        return NULL;
    }

    if (!PyCallable_Check(cb))
    {
        PyErr_SetString(testcErr, "param 1 must be callable");
        return NULL;
    }

    if (errb && !PyCallable_Check(errb))
    {
        PyErr_SetString(testcErr, "param 2 must be callable");
        return NULL;
    }

    Py_XINCREF(cb);
    Py_XINCREF(errb);
    Py_XINCREF(userdata);
    return cpp_method(cb, errb, userdata);
}

static struct PyMethodDef testc_method[] = 
{
    {"testc", Call_testc, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

/* 
    In python the usage
    import testc from test
    testc(callback)
*/

PyMODINIT_FUNC
inittestc(void)
{
    PyObject *m = Py_InitModule("testc", testc_method);
    if (m == NULL)
    {
        return;
    }

    testcErr = PyErr_NewException("testc.error", NULL, NULL);
    Py_INCREF(testcErr);
    PyModule_AddObject(m, "error", testcErr);
}

