#include <pthread.h>
#include <glib.h>
#include "cppm.h"

typedef struct {
    PyObject *cb;
    PyObject *errb;
    gpointer data;
} cb_info_t;

typedef struct {
    PyObject *cb;
    PyObject *errb;
} worker_args_t;

void handle_err(PyObject *errb)
{
    if (!errb)
    {
        return;
    }

    PyObject *type = NULL, *value = NULL, *traceback = NULL;
    PyErr_Fetch(&type, &value, &traceback);
    PyObject *err_args = Py_BuildValue("(OOO)", type, value, traceback);
    PyObject_CallObject(errb, err_args);
    Py_XDECREF(err_args);
    PyErr_Clear();
}

// Wrapper for g_main_loop
gboolean cb_wrapper(gpointer userdata)
{
    cb_info_t *cb_info = (cb_info_t *)userdata;
    PyObject *arglist = Py_BuildValue("(s)", (char *)cb_info->data);
    if (arglist == NULL)
    {
        PyErr_Clear();
    }

    PyObject *result = PyObject_CallObject(cb_info->cb, arglist);
    Py_XDECREF(arglist);
    if (result == NULL)
    {
        handle_err(cb_info->errb);
        PyErr_Clear();
    }

    Py_XDECREF(result);
    Py_XDECREF(cb_info->cb);
    Py_XDECREF(cb_info->errb);

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
    // Wrapper for attaching cb to g_main_loop
    worker_args_t *args = (worker_args_t *)data;
    cb_info_t *cb_info = g_new0(cb_info_t, 1);
    cb_info->cb = args->cb;
    cb_info->errb = args->errb;
    cb_info->data = g_strdup("async job exec overed");

    g_timeout_add_full(G_PRIORITY_HIGH, 0, cb_wrapper, (gpointer)cb_info, free_cb_info);
    return NULL;
}

PyObject *cpp_method(PyObject *cb, PyObject *errb)
{
    pthread_t tid = 0;
    pthread_attr_t attr = {0};
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    worker_args_t *args = g_new0(worker_args_t, 1);
    args->cb = cb;
    args->errb = errb;

    if (pthread_create(&tid, &attr, worker, (void *)args))
    {
        g_warning("Failed to create thread");
        Py_XDECREF(cb);
        Py_XDECREF(errb);
        Py_RETURN_FALSE;
    }

    pthread_detach(tid);

    Py_RETURN_TRUE;
}
