#ifndef __CPP_M_H
#define __CPP_M_H

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

#ifdef __cplusplus
}
#endif
#endif
