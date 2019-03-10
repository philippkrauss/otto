# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    = nano
BOARD_SUB   = atmega328
MONITOR_PORT = /dev/cu.usbserial-14420

USER_LIB_PATH=lib

ARDUINO_LIBS=Servo EEPROM ArduSnake MaxMatrix

include /usr/local/opt/arduino-mk/Arduino.mk
