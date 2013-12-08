objects = Analog.o EEPROM.o Pin.o Serial.o SPI.o

librawuno.a: $(objects)

include ../Makefile.common
-include $(objects:.o=.d)
