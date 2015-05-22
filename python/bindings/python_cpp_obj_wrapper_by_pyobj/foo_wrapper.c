#include <Python.h>
#include "structmember.h"
#include "foo.h"

typedef struct {
    PyObject_HEAD
    void *foo;
} Foo;

static void Foo_dealloc(Foo* self)
{
    release_foo(self->foo);
    self->foo = NULL;
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *Foo_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Foo *self = (Foo *)type->tp_alloc(type, 0);
    self->foo = NULL;
    return (PyObject *)self;
}

static int Foo_init(Foo *self, PyObject *args, PyObject *kwds)
{
    const char *name = NULL, *arg2 = NULL, *arg3 = NULL;

    static char *kwlist[] = {"name", "arg2", "arg3", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sss", kwlist,
                                     &name, &arg2, &arg3)) {
        return -1;
    }

    self->foo = new_foo((name ? name : ""));

    return 0;
}

static PyObject *call_get_name(Foo *self)
{
    return foo_get_name(self->foo);
}

static PyObject *call_method_a(Foo *self)
{
    return foo_method_a(self->foo);
}

static PyObject *call_method_b(Foo *self, PyObject *args)
{
    PyObject *arg = NULL;
    if (!PyArg_ParseTuple(args, "O", &arg)) {
        return NULL;
    }

    Py_XINCREF(arg);
    return foo_method_b(self->foo, arg);
}

static PyMethodDef Foo_methods[] = {
    {"get_name", (PyCFunction)call_get_name, METH_NOARGS, NULL},
    {"method_a", (PyCFunction)call_method_a, METH_NOARGS, NULL},
    {"method_b", (PyCFunction)call_method_b, METH_VARARGS, NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject FooType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "foo_wrapper.Foo",         /*tp_name*/
    sizeof(Foo),               /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Foo_dealloc,   /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Foo objects",             /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Foo_methods,               /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Foo_init,        /* tp_init */
    0,                         /* tp_alloc */
    Foo_new,                   /* tp_new */
};

static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

void clean_up_module_resources()
{
    // release module global resources here
    printf("clean up foo wrapper module resources\n");
    return;
}

#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initfoo_wrapper(void)
{
    PyObject* m;

    printf("init foo wrapper module\n");
    // allocate module global resources here

    if (Py_AtExit(clean_up_module_resources) != 0) {
        PyErr_SetString(PyExc_ImportError, "Cannot register the module resource dealloc");
        return;
    }

    if (PyType_Ready(&FooType) < 0) {
        return;
    }

    m = Py_InitModule3("foo_wrapper", module_methods,
                       "Example module that creates an extension type.");

    if (m == NULL) {
        return;
    }

    Py_INCREF(&FooType);
    PyModule_AddObject(m, "Foo", (PyObject *)&FooType);
}
