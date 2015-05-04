#include <iostream>
#include <pthread.h>
#include <glib.h>
#include "cppm.h"

using namespace std;

// Wrapper for g_main_loop
gboolean cb_wrapper(gpointer userdata)
{
    PyObject *cb = (PyObject *)userdata;
    
    PyObject *arglist = Py_BuildValue("(s)", "exec overed");
    cout << "Ready to callback" << endl;
    if (!PyCallable_Check(cb))
    {
        cout << "cb is not callable" << endl;
        return FALSE;;
    }
    PyObject *result = PyObject_CallObject(cb, arglist);
    cout << "after cb" << endl;
    Py_DECREF(arglist);
    if (result == NULL)
    {
        cout << "cb result is NULL" << endl;
        return FALSE;
    }

    cout << "cb overed" << endl;
    return FALSE;
}

void *worker(void *data)
{
    // Wrapper for g_main_loop
    g_timeout_add(0, cb_wrapper, (gpointer)data);
    return NULL;

    /*
    PyObject *cb = (PyObject *)data;
    PyObject *arglist = Py_BuildValue("(s)", "exec overed");
    cout << "Ready to callback" << endl;
    if (!PyCallable_Check(cb))
    {
        cout << "cb is not callable" << endl;
        return NULL;;
    }

    PyObject *result = PyObject_CallObject(cb, arglist);
    cout << "after cb" << endl;

    Py_DECREF(arglist);
    if (result == NULL)
    {
        cout << "cb result is NULL" << endl;
        return NULL;
    }

    cout << "cb overed" << endl;
    return NULL;
    */
}


PyObject *cpp_method(PyObject *cb)
{
    pthread_t tid = 0;
    pthread_attr_t attr = {0};
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&tid, &attr, worker, (void *)cb))
    {
        printf("Failed to create thread\n");
        return 0;
    }

    pthread_detach(tid);

    Py_RETURN_TRUE;
}
