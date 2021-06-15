#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "print.h"
#include "sendstring_swedish.h"

// Layer definitions
enum layers {
    _QWERTY,
    _SYMBOLS,
    _MACRO, // As well as Mouse Keys
    _EMPTY,
};

// Custom keycodes (M_ prefix for macros)
enum custom_keycodes {
    M_HOME = SAFE_RANGE,
};

// Tap Dance definitions
enum tap_dances {
    TD_HOME_WIN
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /**********************************************************************************************************************
  *
  * Keymap: Default Layer in Qwerty
  *
  * ,-------------------------------------------------------------------------------------------------------------------.
  * |StopMac |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS | KPAD |StaMacro|
  * |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
  * | `´     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | ?+     |
  * |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
  * | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | Å      |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * | Escape |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |   Ö  | Ä      |
  * |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
  * | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ;   |  :   |  -_  | Shift  |
  * `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
  *          |  §   | <>|  | Left | Right|                                         | Up   | Down |  *'  |  ~¨^ |
  *          `---------------------------'                                         `---------------------------'
  *                                       ,---------------.          ,-------------.
  *                                       | Ctrl | RAlt   |          | Ctrl  | Alt |
  *                                ,------|------|--------|          |------+------+------.
  *                                |      |      |Home/Win|          | PgUp |      |      |
  *                                | BkSp | Del  |--------|          |------|Return| Space|
  *                                |      |      | kp/End |          | PgDn |      |      |
  *                                `----------------------'          `--------------------'
  */
  [_QWERTY] = LAYOUT_pretty(
    DM_RSTP,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SLCK,  KC_PAUS,  TG(_SYMBOLS),  DM_REC1,
    SE_ACUT,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          SE_PLUS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          SE_ARNG,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     SE_ODIA,       SE_ADIA,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   SE_MINS,       KC_RSFT,
              SE_SECT,  SE_LABK,  KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_BSLS,  SE_DIAE,
                                                      CTL_T(KC_ESC), KC_RALT,                                          KC_RCTL,  KC_LALT,
                                                                     TD(TD_HOME_WIN),                                  KC_PGUP,
                              LT(_SYMBOLS, KC_BSPC),  KC_DEL,        LT(_MACRO, KC_END),                               KC_PGDN,  KC_ENTER, KC_SPC
  ),

  /**********************************************************************************************************************
  *
  * Symbols layer
  *
  * ┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
  * │         │       │       │       │       │       │       │       │       │       │       │       │       │       │       │  RESET  │
  * │─────────┼───────┼───────┼───────┼───────┼───────┼───────────────────────────────┼───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │       │       │       │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │  tab  │   _   │   [   │  ]    │   ^   │                               │   !   │   <   │   >   │   =   │   &   │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │   \   │   /   │   {   │   }   │   *   │                               │   ?   │   (   │   )   │   -   │   :   │    @    │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │  #    │   $   │   |   │   ~   │   `   │                               │   +   │   %   │   "   │    '  │   ;   │         │
  * └─────────┼───────┼───────┼───────┼───────┼───────┘                               └───────┼───────┼───────┼───────┼───────┼─────────┘
  *           │  Ins  │       │       │       │                                               │       │       │       │       │
  *           └───────┴───────┴───────┴───────┘                                               └───────┴───────┴───────┴───────┘
  *                                            ┌──────┬────────┐              ┌────────┬──────┐
  *                                            │      │        │              │        │      │
  *                                     ┌──────┼──────┼────────┤              ├────────┼──────┼──────┐
  *                                     │      │      │        │              │        │      │      │
  *                                     │      │      ├────────┤              ├────────┤      │      │
  *                                     │      │      │        │              │        │      │      │
  *                                     └──────┴──────┴────────┘              └────────┴──────┴──────┘
  */
  [_SYMBOLS] = LAYOUT_pretty(
  //  esc       f1        f2        f3        f4          f5        f6          f7        f8      |   f9         f10        f11        f12        prnt      sclck      pause      keypad   program
    _______,  _______,  _______,  _______,  _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  RESET,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
    _______,  KC_TAB,   SE_UNDS,  SE_LBRC,  SE_RBRC,   SE_CIRC,                                                                      SE_EXLM,   SE_LABK,   SE_RABK,   SE_EQL,    SE_AMPR,  _______,
    _______,  SE_BSLS,  SE_SLSH,  SE_LCBR,  SE_RCBR,   SE_ASTR,                                                                      SE_QUES,   SE_LPRN,   SE_RPRN,   SE_MINS,   SE_COLN,  SE_AT,
    _______,  SE_HASH,  SE_DLR,   SE_PIPE,  SE_TILD,   SE_GRV,                                                                       SE_PLUS,   SE_PERC,   SE_DQUO,   SE_QUOT,   SE_SCLN,  _______,
              KC_INS,   _______,  _______,  _______,                                                                                            _______,   _______,   _______,   _______,
                                                      _______,  _______,                                                   _______,  _______,
                                                                _______,                                                   _______,
                                            _______,  _______,  _______,                                                   _______,  _______,   _______
  ),
  /**********************************************************************************************************************
  *
  * Macro layer
  *
  * ┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
  * │         │       │       │       │       │       │       │       │       │       │       │       │       │       │       │  RESET  │
  * │─────────┼───────┼───────┼───────┼───────┼───────┼───────────────────────────────┼───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │ Acc0  │ Acc1  │ Acc2  │       │       │                               │       │       │       │       │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │       │       │       │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │  ~/   │       │       │       │       │                               │   ⇐   │   ⇓   │   ⇑   │   ⇒   │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │ PlayM │       │       │       │         │
  * └─────────┼───────┼───────┼───────┼───────┼───────┘                               └───────┼───────┼───────┼───────┼───────┼─────────┘
  *           │       │       │       │       │                                               │       │       │       │       │
  *           └───────┴───────┴───────┴───────┘                                               └───────┴───────┴───────┴───────┘
  *                                            ┌──────┬────────┐              ┌────────┬──────┐
  *                                            │      │        │              │        │ btn3 │
  *                                     ┌──────┼──────┼────────┤              ├────────┼──────┼──────┐
  *                                     │      │      │        │              │WheelUp │      │      │
  *                                     │      │      ├────────┤              ├────────┤ btn2 │ btn1 │
  *                                     │      │      │        │              │WheelDo │      │      │
  *                                     └──────┴──────┴────────┘              └────────┴──────┴──────┘
  */
  [_MACRO] = LAYOUT_pretty(
  //  esc       f1        f2        f3        f4          f5        f6          f7        f8      |   f9         f10        f11        f12        prnt      sclck      pause      keypad   program
    _______,  _______,  _______,  _______,  _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  RESET,
    _______,  KC_ACL0,  KC_ACL1,  KC_ACL2,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
    _______,  M_HOME,   _______,  _______,  _______,   _______,                                                                      KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R,   _______,  _______,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   DM_PLY1,   _______,   _______,   _______,  _______,
              _______,  _______,  _______,  _______,                                                                                            _______,   _______,   _______,   _______,
                                                      _______,  _______,                                                   _______,  KC_BTN3,
                                                                _______,                                                   KC_WH_U,
                                            _______,  _______,  _______,                                                   KC_WH_D,  KC_BTN2,   KC_BTN1
  ),

  /**********************************************************************************************************************
  *
  * Empty layer (useful for copy-pasting
  * ┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
  * │         │       │       │       │       │       │       │       │       │       │       │       │       │       │       │  RESET  │
  * │─────────┼───────┼───────┼───────┼───────┼───────┼───────────────────────────────┼───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │       │       │       │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │       │       │       │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │       │       │       │       │         │
  * │─────────┼───────┼───────┼───────┼───────┼───────┤                               ├───────┼───────┼───────┼───────┼───────┼─────────│
  * │         │       │       │       │       │       │                               │       │       │       │       │       │         │
  * └─────────┼───────┼───────┼───────┼───────┼───────┘                               └───────┼───────┼───────┼───────┼───────┼─────────┘
  *           │  Ins  │       │       │       │                                               │       │       │       │       │
  *           └───────┴───────┴───────┴───────┘                                               └───────┴───────┴───────┴───────┘
  *                                            ┌──────┬────────┐              ┌────────┬──────┐
  *                                            │      │        │              │        │      │
  *                                     ┌──────┼──────┼────────┤              ├────────┼──────┼──────┐
  *                                     │      │      │        │              │        │      │      │
  *                                     │      │      ├────────┤              ├────────┤      │      │
  *                                     │      │      │        │              │        │      │      │
  *                                     └──────┴──────┴────────┘              └────────┴──────┴──────┘
  */
  [_EMPTY] = LAYOUT_pretty(
  //  esc       f1        f2        f3        f4          f5        f6          f7        f8      |   f9         f10        f11        f12        prnt      sclck      pause      keypad   program
    _______,  _______,  _______,  _______,  _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
    _______,  _______,  _______,  _______,  _______,   _______,                                                                      _______,   _______,   _______,   _______,   _______,  _______,
              _______,  _______,  _______,  _______,                                                                                            _______,   _______,   _______,   _______,
                                                      _______,  _______,                                                   _______,  _______,
                                                                _______,                                                   _______,
                                            _______,  _______,  _______,                                                   _______,  _______,   _______
  ),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_HOME:
	    // If shifted, remove shift since it crashes the computer otherwise....
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
            }
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            break;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Note that high is off, and low is on
    if (!IS_LAYER_ON_STATE(state, _QWERTY)) {
        // Keypad led
        writePinLow(LED_COMPOSE_PIN);
        writePinLow(LED_SCROLL_LOCK_PIN);
    } else {
        writePinHigh(LED_COMPOSE_PIN);
        writePinHigh(LED_SCROLL_LOCK_PIN);
    }
    return state;
}


void led_set_user(uint8_t usb_led) {
}

bool led_update_user(led_t led_state) {
    // Keep these working as normally
    writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
    writePin(LED_NUM_LOCK_PIN, !led_state.num_lock);

    return false;
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
            // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t home_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void home_finished(qk_tap_dance_state_t *state, void *user_data) {
    home_tap_state.state = cur_dance(state);
    switch (home_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LGUI); break;
        case TD_SINGLE_HOLD: register_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: register_code(KC_HOME); break;
        case TD_DOUBLE_HOLD: register_code(KC_HOME); break;
            // Last case is for fast typing. Assuming your key is `f`:
            // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
            // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.

        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_HOME); register_code(KC_HOME); break;
        case TD_NONE:
        case TD_TRIPLE_HOLD:
        case TD_TRIPLE_TAP:
        case TD_UNKNOWN:
            break;
    }
}

void home_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (home_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LGUI); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: unregister_code(KC_HOME); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_HOME);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_HOME);
        case TD_NONE:
        case TD_TRIPLE_HOLD:
        case TD_TRIPLE_TAP:
        case TD_UNKNOWN:
            break;
    }
    home_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Home, hold for win/super/rgui
    //[TD_HOME_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, home_finished, home_reset)
    [TD_HOME_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_HOME),
};
