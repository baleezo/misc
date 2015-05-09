#include <stdio.h>
#include "cppm.h"

int main()
{
    q_wrapper_t q_w = {
        .q = new_Q(),
        .method_x = method_x,
        .free_q = free_q
    };

    q_w.method_x(&q_w);
    q_w.free_q(&q_w);
    q_w.method_x(&q_w);

    only_call_x();

    return 0;
}
