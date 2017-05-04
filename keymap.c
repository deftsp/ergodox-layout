/*
 * shihpin's ErgoDox layout
 * https://github.com/algernon/ergodox-layout
 * https://implementsblog.com/2016/10/16/my-ergodox-ezs-custom-layout/
 */

#include <stdarg.h>
#include "ergodox.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "timer.h"
#include "keymap_plover.h"
#include "eeconfig.h"
#include "wait.h"
#include "version.h"

#define TD_PRESSED_EVENT 0xFF


#define ACTION_TAP_DANCE_MOD_TAP(kc1, kc2) {                        \
    .fn = { NULL, _td_mod_tap_finished, _td_mod_tap_reset },        \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),     \
  }

#define ACTION_TAP_DANCE_DOUBLE_MOD(kc1, kc2, kc3) {                    \
    .fn = { NULL, _td_double_mod_finished, _td_double_mod_reset },      \
    .user_data = (void *)&((td_tap_dance_triple_t) { kc1, kc2, kc3 }),  \
    }

typedef struct {
    uint16_t kc1;
    uint16_t kc2;
    uint16_t kc3;
} td_tap_dance_triple_t;


/* Layers */
enum {
    BASE = 0,
    ARRW,
    PROG, // Numbers, Symbols, and Function Keys
};

/* Macros */
enum {
    NONE = 0,
    A_MPN,

    // number/symbol keys
    A_1, // 1
    A_2, // 2
    A_3, // ...
    A_4,
    A_5,
    A_6,
    A_7,
    A_8,
    A_9,
    A_0,

    // Fx
    Fx,
};

/* Fn keys */
enum {
    F_BSE = 0,
    F_GUI,
    F_SFT,
    F_ALT,
    F_CTRL
};

/* Custom keycodes */
enum {
    CT_QUDQ = 0,
    CT_GRTI,
    CT_MUG,  // -, _, LGUI
    CT_CSG,  // :, ;, RGUI
    CT_FGUI,
    CT_DALT,
    CT_EA,
    CT_LBP,
    CT_RBP,
    CT_SR,
};

// user defined combo
/*
 * enum process_combo_event {
 *     CC_ESC = 0,
 *     CC_COPY,
 * };
 *
 * const uint16_t PROGMEM esc_combo[] = {KC_E, KC_R, COMBO_END};
 * const uint16_t PROGMEM copy_combo[] = {KC_C, KC_V, COMBO_END};
 * combo_t key_combos[COMBO_COUNT] = {
 *     [CC_ESC]  = COMBO_ACTION(esc_combo),
 *     [CC_COPY] = COMBO_ACTION(copy_combo),
 * };
 */

/* States & timers */
uint16_t gui_timer = 0;

#if KEYLOGGER_ENABLE
    # ifdef AUTOLOG_ENABLE
        bool log_enable = true;
    # else
        bool log_enable = false;
    # endif
#endif

bool skip_leds = false;

static uint8_t default_layer = 0;


/* The Keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |     `     | 1  ! | 2  @ | 3  # | 4  $ | 5  % | 6  ^ |           |  Fx  | 6  ^ | 7  & | 8  & | 9  ( | 0  ) |  Backsp   |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |  KC_TAB   |   Q  |   W  |   E  |   R  |   T  |   (  |           |  )   |   Y  |   U  |   I  |   O  |  P   |     \     |
 * |-----------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+-----------|
 * | Tab/ARROW |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |     '     |
 * |-----------+------+------+------+------+------|   -  |           |  =   |------+------+------+------+------+-----------|
 * |   SHIFT   |Z/CTRL|   X  |   C  |   V  |   B  | LT->1|           | LT->1|   N  |   M  |   ,  |   .  |//CTRL|   SHIFT   |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |      | LALT |-_/GUI|                                       |:;/GUI| RALT |      |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | Del  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | LEAD |      |      |
 *                                  |Basksp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | Del  |      |      |
 *                                  `--------------------'           `--------------------'
 */
    [BASE] = KEYMAP(
        // left hand
        TD(CT_GRTI),         KC_1,          KC_2,          KC_3,         KC_4,         KC_5,                KC_6,
        KC_TAB,              KC_Q,          KC_W,          KC_E,         KC_R,         KC_T,                TD(CT_LBP),
        TD(CT_EA),           KC_A,          KC_S,          KC_D,         KC_F,         KC_G,
        KC_LSFT,             LCTL_T(KC_Z),  KC_X,          KC_C,         KC_V,         KC_B,                LT(PROG, KC_MINUS),
        KC_NO,               KC_NO,         KC_NO,         KC_LALT,      TD(CT_MUG),

        F(F_ALT), F(F_GUI),
        F(F_CTRL),
        KC_BSPC, F(F_SFT), KC_ESC,

        // right hand
        M(Fx),               KC_6,          KC_7,         KC_8,          KC_9,         KC_0,                KC_BSPC,
        TD(CT_RBP),          KC_Y,          KC_U,         KC_I,          KC_O,         KC_P,                KC_BSLS,
                             KC_H,          KC_J,         KC_K,          KC_L,         KC_SCLN,             TD(CT_QUDQ),
        LT(PROG, KC_EQL),    KC_N,          KC_M,         KC_COMM,       KC_DOT,       RCTL_T(KC_SLSH),     KC_RSFT,
        TD(CT_CSG),          KC_RALT,       KC_NO,        KC_NO,         TD(CT_SR),

        OSL(PROG), KC_DEL,
        KC_LEAD,
        KC_DEL, KC_ENT, KC_SPC
        ),

/* Keymap 1: Arrow layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------| Left | Down |  Up  | Right |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  | Enter|      |------|           |------| PgUp | PgDn |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

    [ARRW] = KEYMAP(
        // left hand
        KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,

        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_ENT,  KC_TRNS, KC_TRNS,

        // right hand
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_PGUP, KC_PGDN
        ),

/* Keymap 2: Navigation & Media layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |    F11    |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   1  |   2  |   3  |   4  |  5   |------|           |------|   6  |  7   |   8  |   9  |   0  |    F12    |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | VlDn | VlUp |           | BASE |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Mute |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
    [PROG] = KEYMAP(
        // left hand
        KC_NO,      KC_NO,       KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,      KC_F1,       KC_F2,      KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
        KC_NO,      KC_1,        KC_2,       KC_3,    KC_4,    KC_5,
        KC_TRNS,    KC_NO,       KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
        KC_NO,      KC_NO,       KC_NO,      KC_NO,   KC_NO,

        KC_VOLD, KC_VOLU,
        KC_MUTE,
        KC_NO, KC_NO,   KC_TRNS,

        // right hand
        KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        KC_TRNS,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
                   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_F12,
        KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_TRNS,
        KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,

        KC_TRNS,   KC_NO,
        KC_NO,
        KC_NO,     KC_NO,   KC_NO
        ),
};

const uint16_t PROGMEM fn_actions[] = {
    [F_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),
    [F_GUI]  = ACTION_MODS_ONESHOT (MOD_LGUI),
    [F_SFT]  = ACTION_MODS_ONESHOT (MOD_LSFT),
    [F_ALT]  = ACTION_MODS_ONESHOT (MOD_LALT),
    [F_CTRL] = ACTION_MODS_ONESHOT (MOD_LCTL)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case A_MPN:
            if (record->event.pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
                    ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
                    int oneshot = ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out());

                    if (oneshot)
                        clear_oneshot_mods ();
                    unregister_code (KC_LSFT);

                    register_code (KC_MPRV);
                    unregister_code (KC_MPRV);

                    if (!oneshot)
                        register_code (KC_LSFT);
                } else {
                    return MACRO (T(MNXT), END);
                }
            }
            break;

        case Fx:          /* Fx */
            if (record->event.pressed) {
                set_oneshot_mods (MOD_LSFT);
                set_oneshot_layer (PROG, ONESHOT_START);
            } else {
                clear_oneshot_layer_state (ONESHOT_PRESSED);
            }
            break;
    }

    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef DEBUG_ENABLE
    debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = false;
#endif

    ergodox_led_all_on();
    for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
        ergodox_led_all_set (i);
        wait_ms (5);
    }
    wait_ms(1000);
    for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
        ergodox_led_all_set (i);
        wait_ms (10);
    }
    ergodox_led_all_off();

    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    uint8_t dl = eeconfig_read_default_layer ();
    switch (dl) {
        case 1UL << BASE:
            default_layer = BASE;
            break;
        case 1UL << ARRW:
            default_layer = BASE;
            break;
        case 1UL << PROG:
            default_layer = PROG;
            break;
    }
};

LEADER_EXTERNS();

static void tap_keycodes (uint16_t code, ...) {
    uint16_t kc = code;
    va_list ap;

    va_start(ap, code);

    do {
        register_code16(kc);
        unregister_code16(kc);
        wait_ms(50);
        kc = va_arg(ap, int);
    } while (kc != 0);
    va_end(ap);
}

#define TAP_ONCE(code)                          \
    register_code (code);                       \
    unregister_code (code)

typedef struct {
    bool layer_toggle;
    bool sticky;
} td_ta_state_t;

static void _td_ea_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

    if (td_ta->sticky) {
        td_ta->sticky = false;
        td_ta->layer_toggle = false;
        layer_off (ARRW);

        return;
    }

    // press down -> press up
    if (state->count == 1 && !state->pressed) {
        register_code (KC_ESC);
        td_ta->sticky = false;
        td_ta->layer_toggle = false;
    } else {
        td_ta->layer_toggle = true;
        layer_on (ARRW);
        td_ta->sticky = (state->count == 2);
    }
}

static void _td_ea_reset (qk_tap_dance_state_t *state, void *user_data) {
    td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

    if (!td_ta->layer_toggle)
        unregister_code (KC_ESC);
    if (!td_ta->sticky)
        layer_off (ARRW);
}


static void _td_double_mod_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_tap_dance_triple_t *tripple = (td_tap_dance_triple_t *) user_data;
    if (state->pressed && state->count == 1) {
        register_mods(tripple->kc3);
        state->count = TD_PRESSED_EVENT; // magic number for reset
    } else if (state->count == 1) {
        register_code16(tripple->kc1);
    } else if (state->count >= 2) {
        register_code16(tripple->kc2);
    }
}

static void _td_double_mod_reset (qk_tap_dance_state_t *state, void *user_data) {
    td_tap_dance_triple_t *tripple = (td_tap_dance_triple_t *) user_data;

    if (state->count == TD_PRESSED_EVENT) {
        unregister_mods(tripple->kc3);
    } else if (state->count == 1) {
        unregister_code16(tripple->kc1);
    } else if (state->count >=2) {
        unregister_code16(tripple->kc2);
    }
}


void _td_mod_tap_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    if (state->pressed && state->count == 1) {
        register_mods(pair->kc2);
        state->count = TD_PRESSED_EVENT; // magic number for reset
    } else if (state->count >= 1) {
        register_code16(pair->kc1);
    }
}

void _td_mod_tap_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == TD_PRESSED_EVENT) {
        unregister_mods(pair->kc2);
    } else if (state->count >= 1) {
        unregister_code16(pair->kc1);
    }
}

static void
_td_sr_each (qk_tap_dance_state_t *state, void *user_data) {
    skip_leds = true;

    switch (state->count) {
        case 1:
            ergodox_right_led_3_on ();
            break;
        case 2:
            ergodox_right_led_2_on ();

            break;
        case 3:
            ergodox_right_led_1_on ();
            break;
        case 4:
            ergodox_right_led_3_off ();
            wait_ms (50);
            ergodox_right_led_2_off ();
            wait_ms (50);
            ergodox_right_led_1_off ();
            break;
    }
}

static void
_td_sr_finished (qk_tap_dance_state_t *state, void *user_data) {
    uprintf("_td_sr_finished: %d\n", state->count);

    if (state->count == 1) {
        register_code (KC_MSTP);
    }

    if (state->count >= 4) {
        uprintf("_td_sr_finished: reset_keyboard\n");
        // wait_ms (1000);
        reset_tap_dance (state);
        reset_keyboard ();
    }
}

static void
_td_sr_reset (qk_tap_dance_state_t *state, void *user_data) {
    uprintf("_td_sr_reset with count: %d\n", state->count);

    if (state->count >= 4) {
        skip_leds = true;

        ergodox_led_all_set (LED_BRIGHTNESS_HI);
        ergodox_led_all_off ();
        ergodox_board_led_on();
        ergodox_right_led_1_on ();
        wait_ms (100);
        ergodox_right_led_2_on ();
        wait_ms (50);
        ergodox_right_led_3_on ();
        wait_ms (100);
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
        wait_ms (100);
        ergodox_right_led_1_on ();
        wait_ms (100);
        ergodox_right_led_2_on ();
        wait_ms (100);
        ergodox_right_led_3_on ();
    } else {
        skip_leds = false;

        ergodox_right_led_1_off ();
        wait_ms (50);
        ergodox_right_led_2_off ();
        wait_ms (50);
        ergodox_right_led_3_off ();

        if (state->count == 1) {
            unregister_code (KC_MSTP);
        }
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_QUDQ] = ACTION_TAP_DANCE_DOUBLE (KC_QUOT, KC_DQUO),
    [CT_GRTI] = ACTION_TAP_DANCE_DOUBLE (KC_GRV,  KC_TILD),
    [CT_EA]   = {
        .fn = { NULL, _td_ea_finished, _td_ea_reset },
        .user_data = (void *)&((td_ta_state_t) { false, false })
    },
    [CT_FGUI] = ACTION_TAP_DANCE_MOD_TAP(KC_F, MOD_LGUI),
    [CT_DALT] = ACTION_TAP_DANCE_MOD_TAP(KC_D, MOD_LALT),
    [CT_MUG]  = ACTION_TAP_DANCE_DOUBLE_MOD(KC_MINS, KC_UNDS, MOD_BIT(KC_LGUI)),
    [CT_CSG]  = ACTION_TAP_DANCE_DOUBLE_MOD(KC_COLN, KC_SCLN, MOD_BIT(KC_RGUI)),
    [CT_LBP]  = ACTION_TAP_DANCE_DOUBLE_MOD(KC_LBRC, KC_LPRN, MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)),
    [CT_RBP]  = ACTION_TAP_DANCE_DOUBLE_MOD(KC_RBRC, KC_RPRN, MOD_BIT(KC_LGUI) | MOD_BIT(KC_RALT) | MOD_BIT(KC_RCTL) | MOD_BIT(KC_RSFT)),
    [CT_SR]   = ACTION_TAP_DANCE_FN_ADVANCED (_td_sr_each, _td_sr_finished, _td_sr_reset)
};


/*
 * void process_combo_event(uint8_t combo_index, bool pressed) {
 *     switch(combo_index) {
 *     case CC_ESC:
 *         if (pressed) {
 *             register_code(KC_ESC);
 *             unregister_code(KC_ESC);
 *         }
 *         break;
 *     case CC_COPY:
 *         if (pressed) {
 *             add_weak_mods(MOD_BIT(KC_LGUI));
 *             send_keyboard_report();
 *             register_code(KC_C);
 *             unregister_code(KC_C);
 *             del_weak_mods(MOD_BIT(KC_LGUI));
 *             send_keyboard_report();
 *         }
 *         break;
 *     }
 * }
 */


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    bool is_arrow = false;

    if (gui_timer != 0 && timer_elapsed (gui_timer) > TAPPING_TERM) {
        unregister_code (KC_LGUI);
        gui_timer = 0;
    }

    if (!skip_leds) {
        if (layer == PROG) {
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
        }
    }

    if (layer_state & (1UL << ARRW)) {
        if (!skip_leds) {
            ergodox_right_led_1_on ();
            ergodox_right_led_3_on ();
        }

        is_arrow = true;
    }

    if (!skip_leds) {
        uint8_t shift_bits = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);
        bool shift_active = keyboard_report->mods & shift_bits;
        bool oneshot_shift_effective = (get_oneshot_mods() & shift_bits) && !has_oneshot_mods_timed_out();
        if (shift_active || oneshot_shift_effective) {
            ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
            ergodox_right_led_1_on ();
        } else {
            ergodox_right_led_1_set (LED_BRIGHTNESS_LO);
            if (layer != PROG && !is_arrow) {
                ergodox_right_led_1_off ();
            }
        }

        uint8_t alt_bits = MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT);
        bool alt_active = keyboard_report->mods & alt_bits;
        bool oneshot_alt_effective = (get_oneshot_mods() & alt_bits) && !has_oneshot_mods_timed_out();

        uint8_t gui_bits = MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI);
        bool gui_active = keyboard_report->mods & gui_bits;
        bool oneshot_gui_effective = (get_oneshot_mods() & gui_bits) && !has_oneshot_mods_timed_out();


        if (alt_active || oneshot_alt_effective || gui_active || oneshot_gui_effective) {
            ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
            ergodox_right_led_2_on ();
        } else {
            ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
            if (layer != PROG && !is_arrow) {
                ergodox_right_led_2_off ();
            }
        }

        uint8_t ctrl_bits = MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTL);
        bool ctrl_active = keyboard_report->mods & ctrl_bits;
        bool oneshot_ctrl_effective = (get_oneshot_mods() & ctrl_bits) && !has_oneshot_mods_timed_out();
        if (ctrl_active || oneshot_ctrl_effective) {
            ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
            ergodox_right_led_3_on ();
        } else {
            ergodox_right_led_3_set (LED_BRIGHTNESS_LO);
            if (layer != PROG && !is_arrow) {
                ergodox_right_led_3_off ();
            }
        }
    }


    LEADER_DICTIONARY() {
        leading = false;
        leader_end ();

#if KEYLOGGER_ENABLE
        // enable log with blink twice, otherwise once
        SEQ_ONE_KEY (KC_D) {
            ergodox_led_all_on();
            wait_ms(100);
            ergodox_led_all_off();

            if (log_enable == false) {
                wait_ms(100);
                ergodox_led_all_on();
                wait_ms(100);
                ergodox_led_all_off();
            }

            log_enable = !log_enable;
        }
#endif

        SEQ_ONE_KEY (KC_V) {
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ (" QMK_VERSION "/" KEYMAP_VERSION ")");
        }

        SEQ_ONE_KEY (KC_Y) {
            tap_keycodes (KC_BSLS, KC_O, KC_SLSH, 0);
        }


        SEQ_TWO_KEYS (KC_W, KC_M) {
            uprintf("LEADER OF TWO KEY\n");
        }

        SEQ_ONE_KEY (KC_A) {
            default_layer_and (0);
            default_layer_or (1UL << BASE);
            eeconfig_update_default_layer ((1UL << BASE));

            ergodox_led_all_off ();
            ergodox_right_led_1_on ();
            wait_ms (100);
            ergodox_right_led_2_on ();
            wait_ms (100);
            ergodox_right_led_1_off ();
            ergodox_right_led_3_on ();
            wait_ms (100);
            ergodox_right_led_2_off ();
            wait_ms (100);
            ergodox_right_led_3_off ();
        }
    }
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
#if KEYLOGGER_ENABLE
  if (log_enable) {
    uint8_t layer = biton32(layer_state);

    char *layer_name = NULL;
    if (layer == BASE) {
        layer_name = "BASE";
    } else if (layer == ARRW) {
        layer_name = "ARRW";
    } else if (layer == PROG) {
        layer_name = "PROG";
    }

    uprintf ("KL: kc=%02d, pressed=%d, layer=%s\n", keycode, record->event.pressed, layer_name);
  }
#endif

  // pressing ESC to clear oneshot mods
  if (keycode == KC_ESC && record->event.pressed) {
      bool queue = true;

      if ((get_oneshot_mods ()) && !has_oneshot_mods_timed_out ()) {
          clear_oneshot_mods ();
          queue = false;
      }

      return queue;
  }

  return true;
}

/* Local Variables: */
/* eval: (auto-fill-mode -1) */
/* End: */
