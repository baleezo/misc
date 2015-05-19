from distutils.core import setup, Extension
setup(name="foo_wrapper", version="1.0",
      ext_modules=[Extension("foo_wrapper", ["foo_wrapper.c", "foo.cc"])])
