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

enum my_keycodes {
  EC_BASE = SAFE_RANGE,
  EC_MTX_UP,
  EC_MTX_DOWN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_default(
        QK_GESC,        KC_Q,           KC_W,          KC_E,           KC_R,          KC_T,
        KC_BACKSPACE,   KC_A,           KC_S,          KC_D,           KC_F,          KC_G,
        KC_LEFT_SHIFT,  KC_Z,           KC_X,          KC_C,           KC_V,          KC_B,
        KC_LEFT_CTRL,   XXXXXXX,        KC_LWIN,       KC_LALT,        KC_TAB,        MO(_CO),

        KC_Y,               KC_U,           KC_I,           KC_O,            KC_P,           KC_DELETE,
        KC_H,               KC_J,           KC_K,           KC_L,            KC_SCLN,        KC_QUOT,
        KC_N,               KC_M,           KC_COMM,        KC_DOT,          KC_SLASH,       KC_RIGHT_SHIFT,
        LT(_CO, KC_ENTER),  KC_SPACE,       A(KC_LSFT),     KC_CAPS,         DF(_COLEMAK),   TG(_CO)
    ),
    [_CO] = LAYOUT_default(
        _______,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,
        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,   
        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
        _______,        _______,        _______,        _______,        _______,        _______,

        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BACKSLASH,
        KC_VOLU,        KC_LBRC,        KC_RBRC,        _______,        KC_MINS,        KC_EQL,
        KC_VOLD,        _______,        KC_HOME,        KC_UP,          KC_END,         _______,
        _______,        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       _______
    ),
    [_MAC] = LAYOUT_default(
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        KC_LOPT,        KC_LCMD,        _______,        _______,

        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        KC_CAPS,        S(KC_CAPS),     _______,        _______
    ),
    [_COLEMAK] = LAYOUT_default(
        QK_GESC,        KC_Q,           KC_W,          KC_F,           KC_P,          KC_G,
        KC_BACKSPACE,   KC_A,           KC_R,          KC_S,           KC_T,          KC_D,
        KC_LEFT_SHIFT,  KC_Z,           KC_X,          KC_C,           KC_V,          KC_B,
        KC_LEFT_CTRL,   XXXXXXX,        KC_LWIN,       KC_LALT,        KC_TAB,        MO(_CO),

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

bool ec_up_pressed = false;
bool ec_down_pressed = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EC_MTX_DOWN:
      if (record->event.pressed) {
        // Do something when pressed
        if (ec_up_pressed) {
            ec_up_pressed = false;
            unregister_code(KC_UP);
        }
        ec_down_pressed = true;
        register_code(KC_DOWN);
      } else {
        if (ec_down_pressed) {
            unregister_code(KC_DOWN);
        } else {
            // do nothing
        }
      }
      return false; // Skip all further processing of this key
    case EC_MTX_UP:
      if (record->event.pressed) {
        // Do something when pressed
        if (ec_down_pressed) {
            ec_down_pressed = false;
            unregister_code(KC_DOWN);
        }
        ec_up_pressed = true;
        register_code(KC_UP);
      } else {
        if (ec_up_pressed) {
            unregister_code(KC_UP);
        } else {
            // do nothing
        }
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, _CO)) {
        writePin(B13, true);
    } else {
        writePin(B13, false);
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
