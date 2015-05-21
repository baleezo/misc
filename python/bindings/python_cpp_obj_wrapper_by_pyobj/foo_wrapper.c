#include <Python.h>
#include "structmember.h"
#include "foo.h"

typedef struct {
    PyObject_HEAD
    PyObject *first;
    PyObject *last;
    int number;
    void *foo;
} Foo;

static void Foo_dealloc(Foo* self)
{
    release_foo(self->foo);
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *Foo_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Foo *self = (Foo *)type->tp_alloc(type, 0);

    if (self != NULL) {
        self->first = PyString_FromString("");
        if (self->first == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        self->last = PyString_FromString("");
        if (self->last == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        self->number = 0;
        self->foo = new_foo();
    }
    return (PyObject *)self;
}

static int Foo_init(Foo *self, PyObject *args, PyObject *kwds)
{
    PyObject *first = NULL, *last = NULL, *tmp;

    static char *kwlist[] = {"first", "last", "number", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", kwlist,
                                     &first, &last,
                                     &self->number)) {
        return -1;
    }

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }

    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }

    return 0;
}

static PyMemberDef Foo_members[] = {
    {"number", T_INT, offsetof(Foo, number), 0,
     "foo_wrapper number"},
    {NULL}  /* Sentinel */
};

static PyObject *Foo_getfirst(Foo *self, void *closure)
{
    Py_INCREF(self->first);
    return self->first;
}

static int Foo_setfirst(Foo *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }

    if (! PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The first attribute value must be a string");
        return -1;
    }

    Py_DECREF(self->first);
    Py_INCREF(value);
    self->first = value;

    return 0;
}

static PyObject *Foo_getlast(Foo *self, void *closure)
{
    Py_INCREF(self->last);
    return self->last;
}

static int Foo_setlast(Foo *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }

    if (! PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The last attribute value must be a string");
        return -1;
    }

    Py_DECREF(self->last);
    Py_INCREF(value);
    self->last = value;

    return 0;
}

static PyGetSetDef Foo_getseters[] = {
    {"first",
     (getter)Foo_getfirst, (setter)Foo_setfirst,
     "first name", NULL},
    {"last",
     (getter)Foo_getlast, (setter)Foo_setlast,
     "last name", NULL},
    {NULL}  /* Sentinel */
};

static PyObject *Foo_name(Foo* self)
{
    static PyObject *format = NULL;
    PyObject *args, *result;

    if (format == NULL) {
        format = PyString_FromString("%s %s");
        if (format == NULL) {
            return NULL;
        }
    }

    args = Py_BuildValue("OO", self->first, self->last);
    if (args == NULL) {
        return NULL;
    }

    result = PyString_Format(format, args);
    Py_DECREF(args);

    return result;
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
    {"name", (PyCFunction)Foo_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
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
    Foo_members,               /* tp_members */
    Foo_getseters,             /* tp_getset */
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
