#!/usr/bin/env python

#import sys
#sys.path.append("build/lib.linux-x86_64-2.7")

import foo_wrapper

import sys

def run():
    foo = foo_wrapper.Foo("QQ")
    print dir(foo)

    print foo.get_name()

    q = foo.method_a()
    print q

    b = foo.method_b(True)
    print type(b), b

    dict_in = {1:2, 3:4}
    print 'ref count of original obj is ', sys.getrefcount(dict_in), 'id is', id(dict_in)

    c = foo.method_b(dict_in)
    print 'after return from method_c, the refcount of original obj is ', sys.getrefcount(dict_in), 'id of the return obj is', id(c)


if __name__ == '__main__':
    run()
