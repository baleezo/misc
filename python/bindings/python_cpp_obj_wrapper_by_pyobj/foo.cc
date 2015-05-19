#include <Python.h>
#include <iostream>
#include "foo.h"

class foo {
    public:
        foo(){
            std::cout << "foo ctor" << std::endl;
        }
        ~foo(){
            std::cout << "foo dtor" << std::endl;
        };

        PyObject * method_a();
        PyObject * method_b(PyObject *obj);
};


PyObject *foo::method_a()
{
    std::cout << "method a return None\n";
    Py_RETURN_NONE;
}


PyObject *foo::method_b(PyObject *obj)
{
    std::cout << "method b return obj\n";
    Py_INCREF(obj);
    return obj;
}

void *new_foo()
{
    return (void *)(new foo());
}

void release_foo(void *f)
{
    ((foo *)f)->~foo();
}

PyObject *foo_method_a(void *f)
{
    return ((foo *)f)->method_a();
}

PyObject *foo_method_b(void *f, PyObject *obj)
{
    return ((foo *)f)->method_b(obj);
}
