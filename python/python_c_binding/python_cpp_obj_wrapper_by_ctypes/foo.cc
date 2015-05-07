#include <Python.h>
#include <iostream>

using namespace std;

class foo {
    public:
        PyObject * method_a();
        PyObject * method_b();
        PyObject * method_c();
        PyObject * method_d();
        foo(){
            cout << "foo ctor" << endl;
        }
        ~foo(){
            cout << "foo dtor" << endl;
        };
};


PyObject *foo::method_a()
{
    Py_INCREF(Py_None);
    return Py_None;
}


PyObject *foo::method_b()
{
    Py_INCREF(Py_None);
    return Py_None;
}


PyObject *foo::method_c()
{
    Py_INCREF(Py_None);
    return Py_None;
}


PyObject *foo::method_d()
{
    Py_INCREF(Py_None);
    return Py_None;
}

extern "C" {
    foo *new_foo(){return new foo();}
    void release_foo(foo *f){f->~foo();}
    PyObject *foo_method_a(foo *f){return f->method_a();}
    PyObject *foo_method_b(foo *f){return f->method_b();}
    PyObject *foo_method_c(foo *f){return f->method_c();}
    PyObject *foo_method_d(foo *f){return f->method_d();}
}
