#!/bin/sh

set -e

cd ~/opt/qmk_firmware/
make ergodox_ez:shihpin

teensy_loader_cli -v --mcu atmega32u4 -w ~/opt/qmk_firmware/ergodox_ez_shihpin.hex
