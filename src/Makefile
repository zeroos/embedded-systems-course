objects = test_analog.o test_serial.o

all:  libs test_analog.hex test_serial.hex

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
