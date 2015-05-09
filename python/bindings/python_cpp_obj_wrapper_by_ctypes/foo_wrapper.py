from ctypes import cdll, py_object
lib = cdll.LoadLibrary('./libfoo.so')
lib.foo_method_a.restype = py_object
lib.foo_method_b.restype = py_object
lib.foo_method_c.restype = py_object
lib.foo_method_d.restype = py_object
import copy

class Foo:

    def __init__(self):
        print 'foo wrapper ctor'
        try:
            self.obj = lib.new_foo()
        except:
            self.obj = None
            raise

    def __del__(self):
        if self.obj:
            lib.release_foo(self.obj)

        print 'foo wrapper dtor'

    def method_a(self):
        return lib.foo_method_a(self.obj)

    def method_b(self, obj=None):
        ''' copy the result to handle the obj arg is created in the arg list '''
        return copy.deepcopy(lib.foo_method_b(self.obj, py_object(obj)))

    def clear_arg(self):
        self.b_arg = None

    def method_c(self, in_str):
        return lib.foo_method_c(self.obj, in_str)

    def method_d(self):
        return lib.foo_method_d(self.obj)
