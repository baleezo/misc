#include <iostream>
#include <glib.h>
#include <glib-object.h>
#include <pthread.h>
#include "cppm.h"

using namespace std;

typedef struct {
    PyObject *cb;
    gpointer data;
} cb_info_t;

// Wrapper for g_main_loop
gboolean cb_wrapper(gpointer userdata)
{
    cb_info_t *cb_info = (cb_info_t *)userdata;
    PyObject *cb = cb_info->cb;
    
    PyObject *arglist = Py_BuildValue("(s)", (char *)cb_info->data);
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

void free_cb_info(gpointer data)
{
    cb_info_t *cb_info = (cb_info_t *)data;
    g_free(cb_info->data);
    g_free(data);
}

void *worker(void *data)
{
    // Wrapper for g_main_loop
    cb_info_t *cb_info = g_new0(cb_info_t, 1);
    cb_info->cb = (PyObject *)data;
    cb_info->data = g_strdup("async job exec overed");
    g_timeout_add_full(G_PRIORITY_HIGH, 0, cb_wrapper, (gpointer)data, free_cb_info);
    return NULL;

    /* callback directly
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
