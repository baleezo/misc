#include "cppm.h"
#include <cstdlib>
#include <pthread.h>
#include <glib.h>

typedef struct {
    PyObject *cb;
    PyObject *errb;
    PyObject *userdata;
    gpointer data;
} cb_info_t;

typedef struct {
    PyObject *cb;
    PyObject *errb;
    PyObject *userdata;
} worker_args_t;

void handle_err(PyObject *errb, PyObject *userdata)
{
    if (!errb)
    {
        return;
    }

    PyObject *err_type = NULL, *err_value = NULL, *err_traceback = NULL;
    PyErr_Fetch(&err_type, &err_value, &err_traceback);
    PyObject *err_args = Py_BuildValue("((OOO)O)", err_type, err_value, err_traceback, userdata);
    PyObject_CallObject(errb, err_args);
    Py_XDECREF(err_args);
    PyErr_Clear();
}

// Wrapper for g_main_loop
gboolean cb_wrapper(gpointer userdata)
{
    cb_info_t *cb_info = (cb_info_t *)userdata;
    PyObject *cb_userdata = cb_info->userdata;
    if (!cb_userdata)
    {
        cb_userdata = Py_None;
    }

    PyObject *arglist = Py_BuildValue("(sO)", (char *)cb_info->data, cb_userdata);
    if (arglist == NULL)
    {
        PyErr_Print();
    }

    PyObject *result = PyObject_CallObject(cb_info->cb, arglist);
    Py_XDECREF(arglist);
    if (result == NULL)
    {
        handle_err(cb_info->errb, cb_userdata);
        PyErr_Clear();
    }

    Py_XDECREF(result);
    Py_XDECREF(cb_info->userdata);
    Py_XDECREF(cb_info->errb);
    Py_XDECREF(cb_info->cb);

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
    int work_time = (rand() % 5) + 1;

    cb_info_t *cb_info = g_new0(cb_info_t, 1);
    cb_info->cb = args->cb;
    cb_info->errb = args->errb;
    cb_info->userdata = args->userdata;
    cb_info->data = g_strdup_printf("async job exec overed in %d secs", work_time);

    sleep(work_time);

    g_timeout_add_full(G_PRIORITY_HIGH, 0, cb_wrapper, (gpointer)cb_info, free_cb_info);
    return NULL;
}

PyObject *cpp_method(PyObject *cb, PyObject *errb, PyObject *userdata)
{
    pthread_t tid = 0;
    pthread_attr_t attr = {0};
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    worker_args_t *args = g_new0(worker_args_t, 1);
    args->cb = cb;
    args->errb = errb;
    args->userdata = userdata;

    if (pthread_create(&tid, &attr, worker, (void *)args))
    {
        Py_XDECREF(userdata);
        Py_XDECREF(errb);
        Py_XDECREF(cb);
        PyErr_SetString(PyExc_RuntimeError, "Failed to create thread");
        return NULL;
    }

    pthread_detach(tid);

    Py_RETURN_TRUE;
}
