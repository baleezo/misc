#include <iostream>
#include "cppm.h"

using namespace std;

class Q
{
public:
    Q(){};
    void x()
    {
        cout << "call method x of Q" << endl;
    };
};

void *new_Q()
{
    cout << __func__ << ": must free Q by yourself" << endl;
    return (void *)new Q();
}

#define GET_Q(self) ((Q *)(self->q))

void method_x(q_wrapper_t *self)
{
    if (!GET_Q(self))
    {
        cout << "Q is freed, can not call Q.x()" << endl;
        return;
    }

    GET_Q(self)->x();
}

void free_q(q_wrapper_t *self)
{
    cout << "free Q" << endl;
    delete GET_Q(self);
    self->q = NULL;
}

void only_call_x()
{
    cout << __func__ << endl;
    Q q;
    q.x();
}

void h_method_x(Q_HANDLE q_handle)
{
    if (!q_handle)
    {
        cout << "Q is freed, can not call Q.x()" << endl;
        return;
    }

    ((Q *)q_handle)->x();
}

void h_free_q(Q_HANDLE *q_handle)
{
    cout << "handle free Q" << endl;
    delete (Q *)*q_handle;
    *q_handle = NULL;
}
