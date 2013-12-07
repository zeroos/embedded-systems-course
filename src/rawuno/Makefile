objects = Analog.o EEPROM.o Serial.o

librawuno.a: $(objects)

include ../Makefile.common
-include $(objects:.o=.d)
