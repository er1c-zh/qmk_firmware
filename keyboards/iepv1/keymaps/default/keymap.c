// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "print.h"
#include "platforms/gpio.h"

enum layer_names {
    _COLEMAK,
    _QWERTY,
    _MAC,
    _CO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_default(
        QK_GESC,        KC_Q,           KC_W,          KC_E,           KC_R,          KC_T,
        KC_BACKSPACE,   KC_A,           KC_S,          KC_D,           KC_F,          KC_G,
        KC_LEFT_SHIFT,  KC_Z,           KC_X,          KC_C,           KC_V,          KC_B,
        KC_LEFT_CTRL,   XXXXXXX,        KC_LWIN,       KC_LALT,        KC_TAB,        LT(_CO, KC_SPACE),

        KC_Y,               KC_U,           KC_I,           KC_O,            KC_P,           KC_DELETE,
        KC_H,               KC_J,           KC_K,           KC_L,            KC_SCLN,        KC_QUOT,
        KC_N,               KC_M,           KC_COMM,        KC_DOT,          KC_SLASH,       KC_RIGHT_SHIFT,
        LT(_CO, KC_ENTER),  KC_SPACE,       A(KC_LSFT),     KC_CAPS,         DF(_COLEMAK),   TG(_CO)
    ),
    [_CO] = LAYOUT_default(
        _______,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,

        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BACKSLASH,
        _______,        KC_LBRC,        KC_RBRC,        _______,        KC_MINS,        KC_EQL,
        _______,        _______,        KC_HOME,        KC_UP,          KC_END,         _______,
        _______,        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       _______
    ),
    [_MAC] = LAYOUT_default(
        KC_ESC,         _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        KC_LOPT,        KC_LCMD,        _______,        _______,

        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        S(KC_CAPS),     KC_CAPS,        _______,        _______
    ),
    [_COLEMAK] = LAYOUT_default(
        QK_GESC,        KC_Q,           KC_W,          KC_F,           KC_P,          KC_G,
        KC_BACKSPACE,   KC_A,           KC_R,          KC_S,           KC_T,          KC_D,
        KC_LEFT_SHIFT,  KC_Z,           KC_X,          KC_C,           KC_V,          KC_B,
        KC_LEFT_CTRL,   XXXXXXX,        KC_LWIN,       KC_LALT,        KC_TAB,        LT(_CO, KC_SPACE),

        KC_J,               KC_L,           KC_U,           KC_Y,            KC_SCLN,         KC_DELETE,
        KC_H,               KC_N,           KC_E,           KC_I,            KC_O,            KC_QUOT,
        KC_K,               KC_M,           KC_COMM,        KC_DOT,          KC_SLASH,        KC_RIGHT_SHIFT,
        LT(_CO, KC_ENTER),  KC_SPACE,       A(KC_LSFT),     KC_CAPS,         DF(_QWERTY),     TG(_CO) 
    ),
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;

  setPinOutputPushPull(B13);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 1:
        writePin(B13, true);
        break;
    default: //  for any other layers, or the default layer
        writePin(B13, false);
        break;
    }
  return state;
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
            layer_on(_MAC);
            break;
        case OS_IOS:
            break;
        case OS_WINDOWS:
            layer_off(_MAC);
            break;
        case OS_LINUX:
            break;
        case OS_UNSURE:
            break;
    }
    
    return true;
}

/*
    better grave
*/
// Shift + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRV));

// GUI + esc = `
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_CTRL, KC_ESC, KC_GRV);

const key_override_t **key_overrides = (const key_override_t *[]){
    &tilde_esc_override,
    &grave_esc_override,
    NULL
};
