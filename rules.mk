# Having a file like this allows you to override Makefile definitions
# for your own particular keymap

AUTOLOG_ENABLE   ?= no

BOOTMAGIC_ENABLE  = no
COMBO_ENABLE      = no
COMMAND_ENABLE    = no  # Commands for debug and configuration
CONSOLE_ENABLE    = no
DEBUG_ENABLE      = no
FORCE_NKRO        = yes
KEYLOGGER_ENABLE ?= yes
MIDI_ENABLE       = no
RGBLIGHT_ENABLE   = yes
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
TAP_DANCE_ENABLE  = yes

# TODO: enable it macOS can not recognize it, but can input password when system boot
MOUSEKEY_ENABLE   = no

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
endif

ifeq (${AUTOLOG_ENABLE},yes)
KEYLOGGER_ENABLE = yes
OPT_DEFS += -DAUTOLOG_ENABLE
endif

ifeq (${KEYLOGGER_ENABLE},yes)
OPT_DEFS += -DKEYLOGGER_ENABLE
CONSOLE_ENABLE = yes
endif

OPT_DEFS += -DUSER_PRINT

KEYMAP_VERSION = $(shell \
 if [ -d "${KEYMAP_PATH}/.git" ]; then \
  cd "${KEYMAP_PATH}" && git describe --abbrev=6 --dirty --always --tags --match 'v*' 2>/dev/null; \
 else echo QMK; fi)

KEYMAP_BRANCH = $(shell \
 if [ -d "${KEYMAP_PATH}/.git" ]; then \
  cd "${KEYMAP_PATH}"; \
 fi; \
 git rev-parse --abbrev-ref HEAD 2>/dev/null)

OPT_DEFS += -DKEYMAP_VERSION=\"$(KEYMAP_VERSION)\\\#$(KEYMAP_BRANCH)\"



ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
