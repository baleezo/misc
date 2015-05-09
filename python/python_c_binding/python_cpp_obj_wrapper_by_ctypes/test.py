#!/usr/bin/env python
from foo_wrapper import Foo

def run():
    foo = Foo()

    a = foo.method_a()
    print type(a), a
    b = foo.method_b({1:2})
    print type(b), b
    c = foo.method_b({3:4})
    print type(b), b
    print type(c), c
    c = foo.method_c("Qoo")
    print type(c), c
    c2 = foo.method_c("Qoo2")
    print type(c2), c2
    d = foo.method_d()
    print type(d), d


if __name__ == '__main__':
    run()
