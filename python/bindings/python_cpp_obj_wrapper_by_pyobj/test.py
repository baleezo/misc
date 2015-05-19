#!/usr/bin/env python
#import sys
#sys.path.append("build/lib.linux-x86_64-2.7")

import noddy


def q():
    a = noddy.Noddy(first="Qoo", last="QQ", number=12)
    print a.first
    a.first = 1
    print a.last
    print a.name()
    print a.number

q()

print 'over'
