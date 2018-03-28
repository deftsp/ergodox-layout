#ifndef CONFIG_ERGOPALORY_H
#define CONFIG_ERGOPALORY_H

/* adjust the hold/tap delay */
#undef TAPPING_TERM
#define TAPPING_TERM    180  // 200ms by default

#undef COMBO_TERM
#define COMBO_TERM 7

#undef COMBO_COUNT
#define COMBO_COUNT 1

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2

/* makes it easier for fast typists to use dual-function keys. */
#define PERMISSIVE_HOLD


#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 40

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 7

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 100

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 20

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 16

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 60

#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 300

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 1000

#undef MANUFACTURER
#define MANUFACTURER    Palory Inc.

#undef PRODUCT
#define PRODUCT         ErgoDox ergonomic keyboard

#undef DESCRIPTION
#define DESCRIPTION     QMK Firmware for Ergodox


#endif
