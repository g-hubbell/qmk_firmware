/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


/*
* AVERY
* LAYER DEFINITION https://docs.qmk.fm/#/feature_layers
* Ok so doing this isn't strictly necessary, but I like to name my layers something a little more useful
* So if you wanted to add a layer just for escape sequences, you could add ESCAPE_LAYER to the enum and define lists
*/
enum custom_keycodes {
    BASE_LAYER = SAFE_RANGE,
    RAISE_LAYER_1,
    RAISE_LAYER_2,
    /*
    * AVERY
    * MACRO KEYCODES
    * See comment below on line 50
    CURLYBRACK,
    SQUAREBRACK,
    */

};



#define BASE_LAYER 0
#define RAISE_LAYER_1 1
#define RAISE_LAYER_2 2



/*
* AVERY
* MACRO FUNCTIONS https://docs.qmk.fm/#/feature_macros
* Ok this is another thing I've found very useful, these are a couple of super simple macros for adding a pair of curly braces and then putting
* your cursor in between them.
* You can see the structure here pretty easily, your SEND_STRING function just prints whatever you tell it to, and the SS_TAP will throw a
* keycode (a non plain text keycode, like left arrow or ctrl or whatever).
* If nothing else, you should definitely give yourself an escape layer or a series of escape COMBO sequences, so that way you can throw
* one keypress for anything you're in that you need to escape.
* Once you have your definitions set, (in the enum above and then what those keycodes should do with the below function), you would
* just add the code to your layout. See line 165 for implementation.
* Last thing to mention, you can also throw full strings with this; ex: "cd /home/avery/Documents"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CURLYBRACK:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("{}"SS_TAP(X_LEFT));
        }
        break;

    case SQUAREBRACK:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            SEND_STRING("[]"SS_TAP(X_LEFT));
        }
    }
}

*/







/*
* AVERY
* DEBUGGING
* Uncomment this block if you need to debug the board for some reason.
* These functions will dump debug output to either QMK Toolbox or Console/Terminal

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}
*/



/*
* AVERY
* COMBOS https://docs.qmk.fm/#/feature_combo
* Ok, another thing I've found super useful. Essetially what you can do here is define if you want a combo of keys to throw a new keypress
* One thing to keep in mind, is the keys have to be pressed at exactly the same time (within 40ms) for the combo to register.
* This means its really difficult to throw a combo accidentally, which is awesome.
* The below example will throw Escape when you press H an J at the same time.
* The nice thing about this is that you don't have to add any custom macro keycodes to your layout, you can just define a combo and say what
* it should throw. You can also have it throw a custom keycode, so if you want to define a macro that throws your VIM exit keys and tie that
* to a combo, you can totally do that.
*
const uint16_t PROGMEM right_hand_left_click[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM example[] = {keycode1, keycode2, COMBO_END};
combo_t key_combos[7] = {
    COMBO(right_hand_left_click, KC_ESC),
    COMBO(example, keycode_that_the_combo_should_throw),
};

*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* AVERY - KEYCODE LIST: https://docs.qmk.fm/#/keycodes  */

  [BASE_LAYER] = LAYOUT_split_4x6_5(
    KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,			            KC_6, KC_7, KC_8,    KC_9,   KC_0,     KC_BSPC,
//-------------------------------------------------//-----------------------------------------------------------//
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,			            KC_Y, KC_U, KC_I,    KC_O,   KC_P,     KC_MINS,
//-------------------------------------------------//-----------------------------------------------------------//
    KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,	                KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,  KC_QUOT,
//-------------------------------------------------//-----------------------------------------------------------//
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_BSLS,
//-------------------------------------------------//-----------------------------------------------------------//
                        KC_LCTL, KC_SPC, MO(1),		     MO(2),  KC_ENT, KC_RGUI,
                                 KC_HOME,  KC_BSPC,      KC_DEL, KC_RALT
  ),

  [RAISE_LAYER_1] = LAYOUT_split_4x6_5(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,			  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
//---------------------------------------------------------//-----------------------------------------------------------//
    RESET,   _______, _______, _______, _______, KC_LBRC,			  KC_RBRC, KC_P7,   KC_P8,   KC_P9,   _______,  KC_PLUS,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LPRN,	      KC_RPRN, KC_P4,   KC_P5,   KC_P6,   KC_MINS,  KC_PIPE,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______, _______, _______, _______, _______, _______,       _______, KC_P1,   KC_P2,   KC_P3,   KC_EQL,   KC_UNDS,
//---------------------------------------------------------//-----------------------------------------------------------//
                               KC_LCTL, KC_HOME, KC_TRNS,		    KC_TRNS, KC_RALT, KC_RGUI,
                                        KC_SPC,  KC_BSPC,       KC_RCTL, KC_ENT
  ),

  [RAISE_LAYER_2] = LAYOUT_split_4x6_5(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,			    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
//---------------------------------------------------------//--------------------------------------------------------------//
_______, _______, RGB_RMOD, RGB_TOG, RGB_MOD, KC_LBRC,			  KC_RBRC, _______, KC_NLCK, KC_INS,  KC_SLCK,  KC_MUTE,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, KC_LEFT, KC_UP,    KC_DOWN, KC_RGHT, KC_LPRN,	      KC_RPRN, KC_MPRV, KC_MPLY, KC_MNXT, _______,  KC_VOLU,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______,  _______, _______, _______,        _______, _______, _______, _______, _______,  KC_VOLD,
//---------------------------------------------------------//--------------------------------------------------------------//
                               KC_LCTL, KC_HOME, KC_TRNS,		    KC_TRNS, KC_RALT, RESET,
                                        KC_SPC,  KC_BSPC,       KC_RCTL, KC_ENT
  ),
};
