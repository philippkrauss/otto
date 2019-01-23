# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    = uno
MONITOR_PORT = /dev/cu.usbserial-14120

USER_LIB_PATH=lib

ARDUINO_LIBS=Servo ArduSnake

include /usr/local/opt/arduino-mk/Arduino.mk
