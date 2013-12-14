objects = led_blink.o test_analog.o test_eeprom.o test_serial.o test_spi.o \
	  test_temp_sensor.o test_timer0.o

all: 	libs led_blink.hex test_analog.hex test_eeprom.hex test_serial.hex \
	test_spi.hex test_temp_sensor.hex test_timer0.hex

include Makefile.common
-include $(objects:.o=.d)

CPPFLAGS += -Ihal
LDFLAGS  += -Lhal
LDLIBS   += -lhal

libs:
	make -C hal

clean::
	make -C hal clean

.PHONY: all libs
