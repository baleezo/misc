#!/usr/bin/env python
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

import sys


def g_excepthook(*excinfo):
  text = ''.join(traceback.format_exception(*excinfo))
  logger.exception('[%s]', text)


sys.excepthook = g_excepthook


def test():
    try:
        def run():
          print 'Run'
          print q
          return True


        gobject.timeout_add(2000, run)

    except Exception as e:
        logger.exception('error[%s]', e)


if __name__ == '__main__':
  dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

  #session_bus = dbus.SessionBus()
  #bus_name = dbus.service.BusName("com.example.SampleService", session_bus)
  #some_obj = ManagerAgent(bus_name)

  test()
  #objgraph.show_growth()
  mainloop = gobject.MainLoop()
  mainloop.run()



