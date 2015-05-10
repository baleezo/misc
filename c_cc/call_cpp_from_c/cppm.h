#ifndef __CPP_M_H
#define __CPP_M_H

typedef void* Q_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct q_wrapper q_wrapper_t;

void *new_Q();
void method_x(q_wrapper_t *self);
void free_q(q_wrapper_t *self);

struct q_wrapper {
    void *q;
    void (*method_x)(q_wrapper_t *self);
    void (*free_q)(q_wrapper_t *self);
};

void only_call_x();

void h_method_x(Q_HANDLE q_handle);
void h_free_q(Q_HANDLE *q_handle);
#ifdef __cplusplus
}
#endif
#endif
