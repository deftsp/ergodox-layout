#ifndef CONFIG_ERGOPALORY_H
#define CONFIG_ERGOPALORY_H

#include "../../config.h"

/*
 * #undef COMBO_COUNT
 * #define COMBO_COUNT 2
 * #undef COMBO_TERM
 * #define COMBO_TERM 20
 */


/* adjust the hold/tap delay */
#undef TAPPING_TERM
#define TAPPING_TERM    180  // 200ms by default

/* #ifdef RGBLIGHT_ENABLE */
/* #undef RGBLIGHT_SAT_STEP  */
/* #define RGBLIGHT_SAT_STEP 12 */
/* #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 7 */
/* #define RGBLIGHT_EFFECT_SNAKE_LENGTH 7 */
/* #define RGBLIGHT_EFFECT_BREATHE_CENTER 1 */
/* #endif // RGBLIGHT_ENABLE */

/* #define FORCE_NKRO */
/* #ifdef FORCE_NKRO */
/* #define NKRO_EPSIZE 32 */
/* #endif */

/* #define PERMISSIVE_HOLD */


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
