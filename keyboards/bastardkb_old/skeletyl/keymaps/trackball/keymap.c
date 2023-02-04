#include QMK_KEYBOARD_H
#include <stdio.h>

char wpm_str[10];
uint16_t wpm_graph_timer = 0;
bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.



enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5,
    LAYER6,
    LAYER7,
    LAYER8,
    CURLYBRACK,
    SQUAREBRACK,
    PARENTHESIS,
    TRIBRACK,
    ALT_TAB
};






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
        break;

    case PARENTHESIS:
        if (record->event.pressed) {
           SEND_STRING("()"SS_TAP(X_LEFT));// selects all and copies
        }
        break;
    case TRIBRACK:
        if (record->event.pressed) {
           SEND_STRING("<>"SS_TAP(X_LEFT)); // selects all and copies
        }
        break;
     case ALT_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
      break;

    }

    return true;
};

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}





#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
//#define _LAYER6 6
//#define _LAYER7 7
//#define _LAYER8 8
#define _MOUSELAYER 6





static bool scrolling_mode = false;


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LAYER3:  // If we're on the _RAISE layer enable scrolling mode
            scrolling_mode = true;
            pointing_device_set_cpi(2000);
            break;
        default:
            if (scrolling_mode) {  // check if we were scrolling before and set disable if so
                scrolling_mode = false;
                pointing_device_set_cpi(6800);
            }
            break;
    }
    return state;
}



report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    if (scrolling_mode) {
        mouse_report.h = mouse_report.x * 0.4;
        mouse_report.v = mouse_report.y * 0.4;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}





 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_LAYER0] = LAYOUT_split_3x5_3(                        KC_Q, KC_W, KC_E, KC_R, KC_T,							    KC_Y, KC_U, KC_I, KC_O, KC_P,
MT(MOD_LGUI, KC_A), MT(MOD_LALT,KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F), KC_G, 	                            KC_H, MT(MOD_LSFT,KC_J), MT(MOD_LCTL,KC_K), MT(MOD_LALT,KC_L), MT(MOD_LGUI, KC_SCLN),
								                        KC_Z, KC_X, KC_C, KC_V, KC_B, 							    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
								                        OSM(MOD_LCTL), KC_LSFT, LT(1,KC_ENT), 						    LT(2,KC_BSPC), KC_SPC),

[_LAYER1] = LAYOUT_split_3x5_3(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
                               KC_1, KC_2, LT(5,KC_3), LT(3,KC_4), KC_5,                                KC_6, KC_7, KC_8, KC_9, KC_0,
                        KC_MS_WH_UP, KC_MS_WH_DOWN, KC_BTN1, KC_BTN2,KC_NO,                                   KC_NO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
                                                KC_NO, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS),

[_LAYER2] = LAYOUT_split_3x5_3(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, LCTL(LSFT(KC_I)), KC_NO, KC_NO,
                        KC_PIPE, KC_BSLS, KC_GRV, KC_DQUO, KC_QUOT,                                     KC_NO, LT(4,KC_NO), ALT_TAB, KC_DQUO, KC_QUOT,
            CURLYBRACK, SQUAREBRACK, PARENTHESIS, TRIBRACK, KC_NO,                                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_TRNS, KC_TRNS,                                        KC_TRNS, KC_TRNS),

[_LAYER3] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,                                     KC_NO, KC_NO, KC_UP, KC_NO, KC_NO,
                               KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO,                                 KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO,
                                                    KC_NO, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS),

[_LAYER4] = LAYOUT_split_3x5_3(KC_LPRN, KC_RPRN, KC_LT, KC_GT, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_NO,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                    KC_NO, KC_TRNS, KC_TRNS,                                KC_TRNS, KC_TRNS),

[_LAYER5] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_7, KC_8, KC_9, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_4, KC_5, KC_6, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_1, KC_2, KC_3, KC_NO,
                                            KC_NO, KC_NO, KC_NO,                                        KC_PENT, KC_0),


/*
[_LAYER6] = LAYOUT_split_3x5_3(         LCTL(KC_Q), LCTL(KC_W), LCTL(KC_E), LCTL(LSFT(KC_R)), LCTL(KC_T),			LCTL(KC_Y), LCTL(KC_U), LCTL(KC_I), LCTL(KC_O), LCTL(KC_P),
                            LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), LCTL(KC_G), 	                        LCTL(KC_H), LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), LCTL(KC_SCLN),
                LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B), 							LCTL(KC_N), LCTL(KC_M), LCTL(KC_COMM), LCTL(KC_DOT), LCTL(KC_SLSH),
								        KC_LCTL, KC_LSFT, KC_ENT, 						                KC_BSPC, KC_SPC, KC_LALT)

[_LAYER5] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_TAB, KC_LALT, KC_NO,                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_NO, KC_NO, KC_NO,                                    KC_NO, KC_NO, KC_NO),

[_LAYER6] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_PIPE, KC_BSLS, KC_GRV, KC_DQUO, KC_QUOT,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_NO, KC_NO, KC_NO,                                    KC_NO, KC_NO, KC_NO),

[_LAYER7] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_LGUI, LCTL(KC_LEFT), LCTL(KC_D), LCTL(KC_RIGHT), KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_NO, KC_NO, KC_NO,                                    KC_NO, KC_NO, KC_NO),
*/

};
