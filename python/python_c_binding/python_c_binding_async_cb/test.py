#!//usr/bin/env python
import dbus, sys, gobject, os, traceback
import dbus.service
import gc
import dbus.mainloop.glib
from dbus.mainloop.glib import DBusGMainLoop
import logging
from testc import testc

Handler = logging.StreamHandler()
FORMAT = '%(asctime)s - %(name)s -%(levelname)s - %(message)s'
formatter = logging.Formatter(FORMAT)
Handler.setLevel(logging.DEBUG)
Handler.setFormatter(formatter)
logger=logging.getLogger(__name__)
logger.addHandler(Handler)


def err_cb(err, userdata):
    logger.error('Error:', exc_info=err)
    #with open('err.log', 'w') as errlog:
        #traceback.print_exception(err, file=errlog)
        #traceback.print_exception(err, file=sys.stderr)


def cb(s, userdata):
    print s, userdata[1]
    return

    #try:
    #    print s[a]
    #except Exception as e:
    #    logger.exception('err[%s]', e)


def test():
    def run():
        testc(cb, err_cb)
        #testc(cb, err_cb, "QQ")
        return True

    gobject.timeout_add(1000, run)


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    test()
    mainloop = gobject.MainLoop()
    mainloop.run()
