objects = Analog.o EEPROM.o Pin.o Serial.o SPI.o

libhal.a: $(objects)

include ../Makefile.common
-include $(objects:.o=.d)
