#!/bin/sh

set -e

make

teensy_loader_cli -v --mcu atmega32u4 -w ~/opt/qmk_firmware/.build/ergodox_ez_shihpin.hex
