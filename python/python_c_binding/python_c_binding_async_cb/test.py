#!//usr/bin/env python

import dbus, sys, gobject, os, traceback
import dbus.service
import gc
import dbus.mainloop.glib
from dbus.mainloop.glib import DBusGMainLoop
import logging
Handler = logging.StreamHandler()
FORMAT = '%(asctime)s - %(name)s -%(levelname)s - %(message)s'
formatter = logging.Formatter(FORMAT)
Handler.setLevel(logging.DEBUG)
Handler.setFormatter(formatter)
logger=logging.getLogger(__name__)
logger.addHandler(Handler)

def cb(s):
    print s

from testc import testc

def test():
    def run():
        testc(cb)
        return True

    gobject.timeout_add(1000, run)

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    test()
    mainloop = gobject.MainLoop()
    mainloop.run()
