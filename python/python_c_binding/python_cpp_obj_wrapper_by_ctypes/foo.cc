#include <Python.h>
#include <iostream>

class foo {
    public:
        PyObject * method_a();
        PyObject * method_b();
        PyObject * method_c();
        PyObject * method_d();
        foo(){
            std::cout << "foo ctor" << std::endl;
        }
        ~foo(){
            std::cout << "foo dtor" << std::endl;
        };
};


PyObject *foo::method_a()
{
    std::cout << "method a return None => ";
    Py_RETURN_NONE;
}


PyObject *foo::method_b()
{
    std::cout << "method a return True => ";
    Py_RETURN_TRUE;
}


PyObject *foo::method_c()
{
    std::cout << "method a return str => ";
    return PyString_FromString("python str object");
}


PyObject *foo::method_d()
{
    std::cout << "method a return dict => ";
    return Py_BuildValue("{s:s}", "key", "val");
}

extern "C" {
    foo *new_foo(){return new foo();}
    void release_foo(foo *f){f->~foo();}
    PyObject *foo_method_a(foo *f){return f->method_a();}
    PyObject *foo_method_b(foo *f){return f->method_b();}
    PyObject *foo_method_c(foo *f){return f->method_c();}
    PyObject *foo_method_d(foo *f){return f->method_d();}
}
