#include <Python.h>
#include <iostream>

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
        PyObject * method_c(const char *in_str);
        PyObject * method_d();
};


PyObject *foo::method_a()
{
    std::cout << "method a return None => ";
    Py_RETURN_NONE;
}


PyObject *foo::method_b(PyObject *obj)
{
    std::cout << "method b return obj => ";
    return obj;
}


PyObject *foo::method_c(const char *in_str)
{
    std::cout << "method c return str(" << in_str << ") => ";
    return PyString_FromString(in_str);
}


PyObject *foo::method_d()
{
    std::cout << "method d return dict => ";
    return Py_BuildValue("{s:s}", "key", "val");
}

extern "C" {
    foo *new_foo(){return new foo();}
    void release_foo(foo *f){delete f;}
    PyObject *foo_method_a(foo *f){return f->method_a();}
    PyObject *foo_method_b(foo *f, PyObject *obj){return f->method_b(obj);}
    PyObject *foo_method_c(foo *f, const char *in_str){return f->method_c(in_str);}
    PyObject *foo_method_d(foo *f){return f->method_d();}
}
