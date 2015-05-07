#!/usr/bin/env python
from foo_wrapper import Foo

def run():
    foo = Foo()

    print foo.method_a()
    print foo.method_b()
    print foo.method_c()
    print foo.method_d()


if __name__ == '__main__':
    run()
