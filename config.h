#ifndef CONFIG_ERGOPALORY_H
#define CONFIG_ERGOPALORY_H

#include "../../config.h"

/* adjust the hold/tap delay */
#undef TAPPING_TERM
#define TAPPING_TERM    200

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 1

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 2

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000

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
