main_PROG:=play-sakk
main_SRCS:=$(patsubst %,%.c,$(main_PROG))
main_OBJS:=$(patsubst %,%.o,$(main_PROG))
main_DEPS:=$(patsubst %,%.d,$(main_PROG))

CPPFLAGS:=-I../libsakk $(CPPFLAGS)
CFLAGS:=$(CFLAGS) -Wall
LDFLAGS:=-L../libsakk $(LDFLAGS)
LDLIBS:=-lsakk $(LDLIBS)

all: $(main_PROG)

$(main_OBJS): %.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(main_DEPS): %.d: %.c
	$(CC) -MM $(CPPFLAGS) $< -MF $@

$(main_PROG): %: %.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

clean:
	rm -rf $(main_OBJS) $(main_DEPS) $(main_PROG)

.PHONY: all clean

include $(main_DEPS)