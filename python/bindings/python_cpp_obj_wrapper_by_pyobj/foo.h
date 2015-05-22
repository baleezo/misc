#ifndef __FOO_H__
#define __FOO_H__

#ifdef __cplusplus
extern "C" {
#endif
    void *new_foo(const char *name);
    void release_foo(void *f);
    PyObject *foo_get_name(void *f);
    PyObject *foo_method_a(void *f);
    PyObject *foo_method_b(void *f, PyObject *obj);
#ifdef __cplusplus
}
#endif

#endif
