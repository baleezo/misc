#include <Python.h>
#include <iostream>
#include <string>
#include "foo.h"

class foo {
public:
    foo(const char *name):foo_name(name){
        std::cout << "foo ctor" << std::endl;
    }

    ~foo(){
        std::cout << "foo dtor" << std::endl;
    };

    PyObject * get_name();
    PyObject * method_a();
    PyObject * method_b(PyObject *obj);
private:
    std::string foo_name;
};

PyObject *foo::get_name()
{
    std::cout << "get_name\n";
    return PyString_FromString(foo_name.c_str());
}

PyObject *foo::method_a()
{
    std::cout << "method_a return None\n";
    Py_RETURN_NONE;
}

PyObject *foo::method_b(PyObject *obj)
{
    std::cout << "method_b return obj\n";
    Py_XDECREF(obj);
    Py_XINCREF(obj);
    return obj;
}

void *new_foo(const char *name)
{
    return (void *)(new foo(name));
}

void release_foo(void *f)
{
    delete (foo *)f;
}

PyObject *foo_get_name(void *f)
{
    return ((foo *)f)->get_name();
>>>>>>> [M][python cpp obj wrapper by pyobj] Remove redundant portions
}

PyObject *foo_method_a(void *f)
{
    return ((foo *)f)->method_a();
}

PyObject *foo_method_b(void *f, PyObject *obj)
{
    return ((foo *)f)->method_b(obj);
}
