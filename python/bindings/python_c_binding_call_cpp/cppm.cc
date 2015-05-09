#include <iostream>
#include "cppm.h"

using namespace std;

class Q
{
public:
    Q(){};
    void x()
    {
        cout << "Q" << endl;
    };
};

void cpp_method()
{
    Q q;
    q.x();
}
