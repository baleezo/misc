#!/usr/bin/env python

#import sys
#sys.path.append("build/lib.linux-x86_64-2.7")

import foo_wrapper

def run():
    #foo = noddy.Noddy(first="Qoo", last="QQ", number=12)
    foo = foo_wrapper.Foo("Qoo", "QQ", 12)
    print dir(foo)
    print foo.name()
    q = foo.method_a()
    print q
    q = foo.method_a()
    b = foo.method_b("a")
    print type(b), b
    c = foo.method_b({1:2})
    print type(c), c


if __name__ == '__main__':
    run()
