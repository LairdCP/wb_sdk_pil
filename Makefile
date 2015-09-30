#
# Copyright (c) 2013, Laird
#
# Permission to use, copy, modify, and/or distribute this software for any 
# purpose with or without fee is hereby granted, provided that the above 
# copyright notice and this permission notice appear in all copies.
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF 
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#--------------------------------------------------------------------------

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
	-o $(LIB).so.1.0 $(_OBJS) -lc
	ln -fs $(LIB).so.1.0 $(LIB).so.1

clean:
	rm -f *.o  $(LIB).*  
