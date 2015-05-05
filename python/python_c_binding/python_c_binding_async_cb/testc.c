#include <stdio.h>
#include <glib.h>
#include "cppm.h"

static PyObject *Call_testc(PyObject *self, PyObject *args)
{
    PyObject *cb;
    if (!PyArg_ParseTuple(args, "O:set_callback", &cb))
    {
        return NULL;
    }

    if (!PyCallable_Check(cb))
    {
        PyErr_SetString(PyExc_TypeError, "Parameter must be callable");
        g_warning("Parameter must be callable");
        return NULL;
    }

    Py_XINCREF(cb);
    return cpp_method(cb);
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

