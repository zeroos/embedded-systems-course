objects = serial.o

all:  libs serial.hex

serial.elf: serial.o

include Makefile.common
-include $(objects:.o=.d)

CPPFLAGS += -Irawuno
LDFLAGS  += -Lrawuno
LDLIBS   += -lrawuno

libs:
	make -C rawuno

clean::
	make -C rawuno clean

.PHONY: libs
