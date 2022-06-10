LIBNAME:=sakk
LIB:=lib$(LIBNAME).a
SRCS:=sakk.c
OBJS:=$(patsubst %.c,%.o,$(SRCS))
TEST:=utest
TSRC:=utest.c utest-sakk.c
TOBJ:=$(patsubst %.c,%.o,$(TSRC))
DEPS:=$(patsubst %.c,%.d,$(SRCS) $(TSRC))

CPPFLAGS:=$(CPPFLAGS)
CFLAGS:=$(CFLAGS) -Wall
LDFLAGS:=-L. $(LDFLAGS)
LDLIBS:=-lcunit -l$(LIBNAME) $(LDLIBS)
ARFLAGS:=$(ARFLAGS)

all: $(LIB)

$(OBJS) $(TOBJ): %.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(DEPS): %.d: %.c
	$(CC) -MM $(CPPFLAGS) $< -MF $@

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

utest: $(TOBJ) $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

test: $(TEST)
	./$<

clean:
	rm -rf $(OBJS) $(TOBJ) $(DEPS) $(LIB) $(TEST)

.PHONY: all clean test

include $(DEPS)