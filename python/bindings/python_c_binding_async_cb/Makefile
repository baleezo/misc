PY_CFLAGS := $(shell python-config --cflags)
PY_LDFLAGS := $(shell python-config --ldflags)
GLIB_CFLAGS := $(shell pkg-config --cflags glib-2.0)
GLIB_LDFLAGS := $(shell pkg-config --libs glib-2.0)

CFLAGS += $(PY_CFLAGS) -fPIC $(GLIB_CFLAGS)
CXXFLAGS += $(PY_CFLAGS) -fPIC $(GLIB_CFLAGS)
LDFLAGS += $(PY_LDFLAGS) $(GLIB_LDFLAGS)

CFLAGS := $(filter-out -Wstrict-prototypes,$(CFLAGS))
CXXFLAGS := $(filter-out -Wstrict-prototypes,$(CXXFLAGS))

all: testc.so

testc.so: testc.o cppm.o
		g++ -shared $(CXXFLAGS) -o testc.so $^ $(LDFLAGS)

clean:
		rm -f *.so *.o
