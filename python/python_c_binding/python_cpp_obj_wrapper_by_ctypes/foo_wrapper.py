from ctypes import cdll, py_object
lib = cdll.LoadLibrary('./libfoo.so')
lib.foo_method_a.restype = py_object
lib.foo_method_b.restype = py_object
lib.foo_method_c.restype = py_object
lib.foo_method_d.restype = py_object

class Foo:

    def __init__(self):
        try:
            self.obj = lib.new_foo()
        except:
            self.obj = None
            raise

    def __del__(self):
        if self.obj:
            lib.release_foo(self.obj)

    def method_a(self):
        return lib.foo_method_a(self.obj)

    def method_b(self):
        return lib.foo_method_b(self.obj)

    def method_c(self):
        return lib.foo_method_c(self.obj)

    def method_d(self):
        return lib.foo_method_d(self.obj)
