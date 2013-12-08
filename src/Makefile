objects = test_analog.o test_serial.o led_blink.o

all:  libs led_blink.hex test_analog.hex test_serial.hex

include Makefile.common
-include $(objects:.o=.d)

CPPFLAGS += -Irawuno
LDFLAGS  += -Lrawuno
LDLIBS   += -lrawuno

libs:
	make -C rawuno

clean::
	make -C rawuno clean

.PHONY: all libs
