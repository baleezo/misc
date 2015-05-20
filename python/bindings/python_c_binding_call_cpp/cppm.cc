#include <iostream>
#include "cppm.h"

using namespace std;

class Q
{
public:
    Q(){};
    void x()
    {
        cout << __func__ << " is called" << endl;
    };
};

void cpp_method()
{
    Q q;
    q.x();
}
