# Allow CROSS_COMPILE to specify compiler base
CC := arm-sdc-linux-gnueabi-gcc

CFLAGS += -c -Wall -I. -fPIC

LIB = liblrd_pil_wf
_OBJS = example.o

.PHONY: all clean
.DEFAULT: all

all: $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

$(LIB): $(_OBJS)
	$(CC) -shared -Wl,-soname,$(LIB).so.1 \
	-o $(LIB).so.1.0 $(_OBJS) -lc $(LIBS)
	ln -fs $(LIB).so.1.0 $(LIB).so

clean:
	rm -f *.o  $(LIB).*  
