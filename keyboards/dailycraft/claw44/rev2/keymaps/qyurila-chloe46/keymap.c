/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2022 Hyeon Gu <rea9lizer@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

bool is_spacepunc_tapped = false;
bool is_space_pressed = false;

#include "layers.h"
#include "tap_dance.h"
#include "keycodes.h"
#include "keycodes_custom.c"
#include "g/keymap_combo.h"
#include "auto_shift_config.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_DEL,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    L_S_GRV, M_GUI_A, M_ALT_R, M_SFT_S, M_CTL_T, KC_G,    XXXXXXX, TD_CFG,  KC_M,    M_CTL_N, M_SFT_E, M_ALT_I, M_GUI_O, L_S_QUT,
    LTG_EXT, KC_Z,    KC_X,    TRP_C,   DBL_D,   KC_V,    XXXXXXX, LTO_BS,  KC_K,    DBL_H,   TRP_CMM, KC_DOT,  KC_SLSH, LTG_EXT,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      L_P_ESC, L_N_TAB, L_E_ENT, LMO_MOD,                   L_M_RAL, KC_SPC,  KC_BSPC, KC_DEL
  ),                                                                     // =HANGUL (KC_LNG1)
  [_SWAP] = LAYOUT(
    KC_QUOT, KC_SCLN, KC_Y,    KC_U,    KC_L,    KC_J,                      KC_B,    KC_P,    KC_F,    KC_W,    KC_Q,    KC_GRV,
    _______, M_GUI_O, M_ALT_I, M_SFT_E, M_CTL_N, KC_M,    XXXXXXX, _______, KC_G,    M_CTL_T, M_SFT_S, M_ALT_R, M_GUI_A, _______,
    XXXXXXX, KC_SLSH, KC_DOT,  KC_COMM, KC_H,    KC_K,    XXXXXXX, _______, KC_V,    KC_D,    KC_C,    KC_X,    KC_Z,    XXXXXXX,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      KC_DEL,  KC_BSPC, KC_SPC,  L_M_RAL,                   LMO_MOD, L_E_ENT, L_N_TAB, L_P_ESC
  ),
  [_QWERTY] = LAYOUT(
    KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, TD_CFG,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LTG_EXT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, LTO_BS,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LTG_EXT,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      L_P_ESC, L_N_TAB, L_E_ENT, LMO_MOD,                   L_M_RAL, KC_SPC,  KC_BSPC, KC_DEL
  ),

  [_GAME] = LAYOUT(
    KC_ESC,  KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RSFT,
    KC_LCTL, KC_G,    KC_A,    KC_S,    KC_D,    KC_F,    XXXXXXX, _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL,
    KC_TAB,  KC_B,    KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      KC_LALT, KC_LSFT, KC_SPC,  LMO_NUM,                   LMO_EXT, KC_ENT,  KC_BSPC, KC_DEL
  ),
  [_ARROW] = LAYOUT(
    KC_ESC,  KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                      KC_Y,    KC_U,    KC_UP,   KC_O,    KC_P,    KC_RSFT,
    KC_LCTL, KC_G,    KC_A,    KC_S,    KC_D,    KC_F,    XXXXXXX, _______, KC_H,    KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, KC_RCTL,
    KC_TAB,  KC_B,    KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      KC_LALT, KC_LSFT, KC_SPC,  LMO_NUM,                   LMO_EXT, KC_ENT,  KC_BSPC, KC_DEL
  ),

  [_EXTEND] = LAYOUT(  // TODO: replace Linux ZXCV to some other useful keys
    KC_DEL,  KC_AGIN, KC_CUT,  KC_COPY, KC_UNDO, KC_PSTE,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_CIRC, KC_NUM,
    KC_MEH,  KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_SPC,  XXXXXXX, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_GRV,  KC_CAPS,
    _______, C(KC_Y), C(KC_X), C(KC_C), C(KC_Z), C(KC_V), XXXXXXX, _______, KC_PSCR, CAPSWRD, KC_APP,  KC_INS,  KC_APP,  KC_SCRL,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      L_P_ESC, L_N_TAB, KC_ENT,  XXXXXXX,                   KC_RCTL, _______, _______, _______
  ),                                                                     // = HANGA (KC_LNG2)
  [_NUMBER] = LAYOUT(
    XXXXXXX, KC_F10,  KC_F9,   KC_F8,   KC_F7,   _______,                   _______, KC_7,    KC_8,    KC_9,    _______, XXXXXXX,
    XXXXXXX, KC_F11,  KC_F6,   KC_F5,   KC_F4,   _______, XXXXXXX, _______, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_0,    XXXXXXX,
    XXXXXXX, KC_F12,  KC_F3,   KC_F2,   KC_F1,   _______, XXXXXXX, _______, _______, KC_1,    KC_2,    KC_3,    _______, XXXXXXX,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      _______, _______, _______, _______,                   _______, KC_0,    _______, _______
  ),
  [_NUMPAD] = LAYOUT(
    XXXXXXX, _______, KC_9,    KC_8,    KC_7,    _______,                   KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, XXXXXXX,
    XXXXXXX, KC_0,    KC_6,    KC_5,    KC_4,    KC_DOT,  XXXXXXX, _______, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, XXXXXXX,
    XXXXXXX, _______, KC_3,    KC_2,    KC_1,    _______, XXXXXXX, _______, KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_PENT, XXXXXXX,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      _______, _______, _______, _______,                   _______, KC_P0,   _______, KC_PDOT
  ),

  [_MODEXT] = LAYOUT(
    XXXXXXX, G(KC_Q), A(KC_W), S(KC_F), C(KC_P), C(KC_B),                   C(KC_J), C(KC_L), S(KC_U), A(KC_Y), G_SCLN,  XXXXXXX,
    G_GRV,   G(KC_A), A(KC_R), S(KC_S), C(KC_T), C(KC_G), XXXXXXX, XXXXXXX, C(KC_M), C(KC_N), S(KC_E), A(KC_I), G(KC_O), G_QUOT,
    XXXXXXX, G(KC_Z), A(KC_X), S(KC_C), C(KC_D), C(KC_V), XXXXXXX, XXXXXXX, C(KC_K), C(KC_H), S_COMM,  A_DOT,   G_SLSH,  XXXXXXX,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
  [_CONFIG] = LAYOUT(
    QK_BOOT, LDF_QTY, LDF_CMK, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, LDF_CMK, LDF_QTY, QK_BOOT,
    XXXXXXX, LTO_ARW, KC_ASON, KC_ASOFF,XXXXXXX, LTO_GM,  XXXXXXX, _______, LTO_GM,  XXXXXXX, KC_ASOFF,KC_ASON, LTO_ARW, XXXXXXX,
    XXXXXXX, XXXXXXX, CMB_ON,  CMB_OFF, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CMB_OFF, CMB_ON,  XXXXXXX, XXXXXXX,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [_DOUBLE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
  [_TRIPLE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //--------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+--------+--------+--------
                      _______, _______, _______, _______,                   _______, _______, _______, _______
  ),
};


// Encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:  // Left Upper Knob
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;

        case 1:  // Left Lower Knob
            if (IS_LAYER_ON(_EXTEND)) {
                if (clockwise) {
                    tap_code16(A(KC_TAB));
                } else {
                    tap_code16(A(S(KC_TAB)));
                }
            } else if (IS_LAYER_ON(_MODEXT)) {
                if (clockwise) {
                    tap_code16(G(KC_TAB));
                } else {
                    tap_code16(G(S(KC_TAB)));
                }
            } else {
                if (clockwise) {
                    tap_code16(C(S(KC_TAB)));
                } else {
                    tap_code16(C(KC_TAB));
                }
            }
            break;

        default:
            break;
    }

    return true;
}


// Tap-Hold Config
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L_P_ESC:
        case L_N_TAB:
        case DBL_D:
        case DBL_H:
        case TRP_C:
        case TRP_CMM:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L_E_ENT:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L_N_TAB:
        case L_E_ENT:
            return true;
        default:
            return false;
    }
}


// Combos
#ifdef COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    switch (index) {
        case gt_SPC:
            return false;
    }
    return true;
}
#endif

#ifdef COMBO_SHOULD_TRIGGER
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
        case _QWERTY:
        case _NUMBER:
        case _NUMPAD:
        case _DOUBLE:
        case _TRIPLE:
            return true;

        default:
            return false;
    }
}
#endif


// Tap Dance
// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    }
    if (state->count == 2) {
        return TD_DOUBLE_TAP;
    }
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_move(_GAME);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_CONFIG);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_ARROW);
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_CONFIG);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [LAYER_GAME_ARROW_CONFIG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// Caps Word
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_MINS:
        case CM_MINS:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case CM_UNDS:
        case KC_QUOT:
        case KC_SLSH:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


// Main process
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPC:
            if (record->event.pressed) {
                is_space_pressed = true;
            } else {
                is_space_pressed = false;
                if (!is_spacepunc_tapped) {
                    return true;
                }
                is_spacepunc_tapped = false;
                unregister_code16(KC_SPC);
                tap_code(KC_SPC);
                return false;
            }
    }
    process_custom_keycodes(keycode, record);
    return true;
}
