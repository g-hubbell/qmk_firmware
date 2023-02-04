#include QMK_KEYBOARD_H
#include <stdio.h>

char wpm_str[10];
uint16_t wpm_graph_timer = 0;

bool is_alt_tab_active = false;
static bool scrolling_mode = false;
static bool volume_mode = false; // ADD this near the begining of keymap.c
static bool arrow_mode = false;
static bool window_switch_mode_bool = false;

uint16_t alt_tab_timer = 0;     // we will be using them soon.


uint16_t macos_dpi = 7800;
uint16_t win_dpi= 5400;
uint16_t default_dpi = 5400;

static int8_t scroll_h;
static int8_t scroll_v;


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
    MOUSELAYER,
    ARROWMODE,
    VOL_MODE,
    FAST_SCROLL_MODE,
    SLOW_SCROLL_MODE,
    WINDOW_SWITCH_MODE,
    CURLYBRACK,
    SQUAREBRACK,
    PARENTHESIS,
    TRIBRACK,
    ALT_TAB,
    CPI_MACOS,
    CPI_WIN
};

enum{
    MOUSELAYER_ACTIVATE,
    SLOW_DPI
};

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
    case CPI_MACOS:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            default_dpi = macos_dpi;
            pointing_device_set_cpi(default_dpi);
        }
        break;
    case CPI_WIN:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            default_dpi = win_dpi;
            pointing_device_set_cpi(default_dpi);
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

    case FAST_SCROLL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!arrow_mode){
                arrow_mode = false;
                volume_mode = false;
                scrolling_mode = true;
                window_switch_mode_bool = false;
                pointing_device_set_cpi(4400);
            }

        }
        else {
            pointing_device_set_cpi(default_dpi);
            scrolling_mode = false;
        }
        break;
    case SLOW_SCROLL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!arrow_mode){
                arrow_mode = false;
                volume_mode = false;
                scrolling_mode = true;
                window_switch_mode_bool = false;
                pointing_device_set_cpi(2000);
            }

        }
        else {
            pointing_device_set_cpi(default_dpi);
            scrolling_mode = false;
        }
        break;
    case ARROWMODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!arrow_mode){
                arrow_mode = true;
                volume_mode = false;
                scrolling_mode = false;
                window_switch_mode_bool = false;
                pointing_device_set_cpi(200);
            }

        }
        else {
            pointing_device_set_cpi(default_dpi);
            arrow_mode = false;
        }
        break;
    case VOL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!volume_mode){
                arrow_mode = false;
                volume_mode = true;
                scrolling_mode = false;
                window_switch_mode_bool = false;
                pointing_device_set_cpi(200);
            }

        }
        else {
            pointing_device_set_cpi(default_dpi);
            volume_mode = false;
        }
        break;

    case WINDOW_SWITCH_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!window_switch_mode_bool){
                window_switch_mode_bool = true;
                arrow_mode = false;
                volume_mode = false;
                scrolling_mode = false;
                pointing_device_set_cpi(200);
                if(default_dpi == macos_dpi){
                    register_code(KC_LCTL);
                }
                else{
                    register_code(KC_LALT);
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                }

            }

        }
        else {
            if(default_dpi == macos_dpi){
                unregister_code(KC_LCTL);
            }
            else{
                unregister_code(KC_LALT);
            }

            pointing_device_set_cpi(default_dpi);
            window_switch_mode_bool = false;

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




void pointing_device_init_kb(){
    pointing_device_set_cpi(default_dpi);

}



layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _LAYER3:  // If we're on the _RAISE layer enable scrolling mode
            scrolling_mode = true;
            volume_mode=false;
            window_switch_mode_bool = false;
            arrow_mode = false;
            pointing_device_set_cpi(4400);
            break;
        case _LAYER5:
            scrolling_mode = true;
            volume_mode=false;
            window_switch_mode_bool = false;
            arrow_mode = false;
            pointing_device_set_cpi(2000);
            break;
            /*
        case _MOUSELAYER:
            if(arrow_mode){
                volume_mode = false;
                scrolling_mode=false;
                window_switch_mode_bool = false;
            }
            else if (window_switch_mode_bool){
                volume_mode = false;
                scrolling_mode=false;
                arrow_mode=false;
            }
            else{
                volume_mode = true;
                scrolling_mode=false;
                window_switch_mode_bool = false;
            }

            pointing_device_set_cpi(200);
            break;*/
        default:
            if (scrolling_mode || volume_mode || window_switch_mode_bool || arrow_mode) {  // check if we were scrolling before and set disable if so
                window_switch_mode_bool = false;
                scrolling_mode = false;
                volume_mode = false;
                arrow_mode = false;

            }
            pointing_device_set_cpi(default_dpi);
            break;
    }
    return state;
}



report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    int8_t clamped_x = mouse_report.x, clamped_y = mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;

    if (scrolling_mode) {
        // accumulate scroll
        scroll_h += clamped_x;
        scroll_v += clamped_y;

        int8_t scaled_scroll_h = scroll_h / SCROLL_DIVIDER;
        int8_t scaled_scroll_v = scroll_v / SCROLL_DIVIDER;

        // clear accumulated scroll on assignment

        if (scaled_scroll_h != 0) {
            if(default_dpi == win_dpi){
                mouse_report.h = scaled_scroll_h;
            }
            else{
                mouse_report.h = -scaled_scroll_h;
            }
            scroll_h       = 0;
        }
        if (scaled_scroll_v != 0) {
            if(default_dpi == win_dpi){
                mouse_report.v = -scaled_scroll_v;
            }
            else{
                mouse_report.v = scaled_scroll_v;
            }
            scroll_v       = 0;
        }
    }
    else if(volume_mode){
        scroll_v = clamped_y;
        int8_t scaled_scroll_v = scroll_v;

        if (scaled_scroll_v > 0) {
            register_code(KC_AUDIO_VOL_DOWN);
            unregister_code(KC_AUDIO_VOL_DOWN);
            scroll_v       = 0;
        }
        else if (scaled_scroll_v < 0){
            register_code(KC_AUDIO_VOL_UP);
            unregister_code(KC_AUDIO_VOL_UP);
            scroll_v       = 0;
        }
    }
    else if (arrow_mode){
        scroll_h += clamped_x;
        scroll_v += clamped_y;

        int8_t scaled_scroll_h = scroll_h ;
        int8_t scaled_scroll_v = scroll_v ;

        if (scaled_scroll_v > 3) {
            register_code(KC_DOWN);
            unregister_code(KC_DOWN);
            scroll_v       = 0;
        }
        else if (scaled_scroll_v < -3){
            register_code(KC_UP);
            unregister_code(KC_UP);
            scroll_v       = 0;
        }
        if (scaled_scroll_h > 3) {
            register_code(KC_RIGHT);
            unregister_code(KC_RIGHT);
            scroll_h       = 0;
        }
        else if (scaled_scroll_h < -3){
            register_code(KC_LEFT);
            unregister_code(KC_LEFT);
            scroll_h       = 0;
        }


    }
    else if (window_switch_mode_bool){
        scroll_h += clamped_x;
        scroll_v += clamped_y;

        int8_t scaled_scroll_h = scroll_h ;
        int8_t scaled_scroll_v = scroll_v ;
        if(default_dpi == macos_dpi){
            if (scaled_scroll_h > 5) {
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);
                scroll_h       = 0;
            }
            else if (scaled_scroll_h < -5){
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                scroll_h       = 0;
            }
        }
        else{
            if (scaled_scroll_v > 6) {
                register_code(KC_DOWN);
                unregister_code(KC_DOWN);
                scroll_v       = 0;
            }
            else if (scaled_scroll_v < -6){
                register_code(KC_UP);
                unregister_code(KC_UP);
                scroll_v       = 0;
            }
            if (scaled_scroll_h > 6) {
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);
                scroll_h       = 0;
            }
            else if (scaled_scroll_h < -6){
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                scroll_h       = 0;
            }
        }


    }
    else {
        mouse_report.x = clamped_x;
        mouse_report.y = clamped_y;
    }
    return mouse_report;
}



void matrix_scan_user(void) { // The very important timer.

  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }

}

/*
void start_mouselayer(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_Z);
        unregister_code(KC_Z);
    }
    else if(state->count == 2){
        if(!layer_state_is(_MOUSELAYER)){
            layer_move(_MOUSELAYER);
        }
        else{
            layer_move(_LAYER0);
        }

    }
}


void slow_down_dpi(qk_tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        register_code(KC_Q);
        unregister_code(KC_Q);
    }
    else if(state->count == 2){
        if(pointing_device_get_cpi() == 2800){
            if(default_dpi == macos_dpi){
                pointing_device_set_cpi(macos_dpi);
            }
            else{
                pointing_device_set_cpi(win_dpi);
            }
        }
        else{
            pointing_device_set_cpi(2800);
        }

    }
}


qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [MOUSELAYER_ACTIVATE] = ACTION_TAP_DANCE_FN(start_mouselayer),
    [SLOW_DPI] = ACTION_TAP_DANCE_FN(slow_down_dpi),
};

*/
//right hand - one hand basic mouse
const uint16_t PROGMEM right_hand_left_click[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM right_hand_right_click[] = {KC_COMM,KC_DOT, COMBO_END};
const uint16_t PROGMEM fast_scroll_combo_one_hand[] = {KC_M, KC_DOT, COMBO_END};

//two hand mouse mods
const uint16_t PROGMEM fast_scroll_combo_left[] = {MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F), COMBO_END};
const uint16_t PROGMEM window_switch_combo[] = {MT(MOD_LGUI, KC_A),MT(MOD_LALT,KC_S), COMBO_END};
const uint16_t PROGMEM arrow_mode_combo[] = {MT(MOD_LALT,KC_S), MT(MOD_LSFT,KC_F), COMBO_END};
const uint16_t PROGMEM mouselayer_combo[] = {KC_G, MT(MOD_LGUI, KC_SCLN), COMBO_END};
const uint16_t PROGMEM volume_combo[] = {MT(MOD_LALT,KC_S), MT(MOD_LCTL, KC_D), COMBO_END};




combo_t key_combos[7] = {
    COMBO(right_hand_left_click, KC_BTN1),
    COMBO(right_hand_right_click, KC_BTN2), // keycodes with modifiers are possible too!
    COMBO(fast_scroll_combo_left, FAST_SCROLL_MODE),
    COMBO(fast_scroll_combo_one_hand, FAST_SCROLL_MODE),
    COMBO(window_switch_combo, WINDOW_SWITCH_MODE),
    COMBO(arrow_mode_combo, ARROWMODE),
    COMBO(mouselayer_combo, LT(6,KC_NO)),
    COMBO(volume_combo,VOL_MODE),
};




 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
    BASIC STRUCTURE:

    |Q|W|E|R|T|     |Y|U|I|O|P|
    |A|S|D|F|G|     |H|J|K|L|;|
    |Z|X|C|V|B|     |N|M|,|.|/|
        |_|_|_|     |_|_|_|


*/
 [_LAYER0] = LAYOUT_split_3x5_3(                      KC_Q, KC_W, KC_E, KC_R, KC_T,							 KC_Y, KC_U, KC_I, KC_O, KC_P,
MT(MOD_LGUI, KC_A), MT(MOD_LALT,KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F), KC_G, 	                     KC_H, MT(MOD_LSFT,KC_J), MT(MOD_LCTL,KC_K), MT(MOD_LALT,KC_L), MT(MOD_LGUI, KC_SCLN),
								                      KC_Z, KC_X, KC_C, KC_V, KC_B, 					     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
								              OSM(MOD_LCTL), KC_LSFT, LT(1,KC_ENT), 						 LT(2,KC_BSPC), KC_SPC),

[_LAYER1] = LAYOUT_split_3x5_3(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
                               KC_1, KC_2, LT(5,KC_3), LT(3,KC_4), KC_5,                                KC_6, KC_7, KC_8, KC_9, KC_0,
                        KC_NO, KC_NO, KC_BTN2, KC_BTN1,KC_NO,                                   KC_NO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
                                                KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS),

[_LAYER2] = LAYOUT_split_3x5_3(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, LCTL(LSFT(KC_I)), KC_NO, KC_NO,
                        KC_PIPE, KC_BSLS, KC_GRV, KC_DQUO, KC_QUOT,                                     KC_NO, LT(4,KC_NO), ALT_TAB, KC_DQUO, KC_QUOT,
            CURLYBRACK, SQUAREBRACK, PARENTHESIS, TRIBRACK, KC_NO,                                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                           KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_TRNS),

[_LAYER3] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,                                     KC_NO, KC_NO, KC_UP, KC_NO, KC_NO,
                               KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO,                                 KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO,
                                                KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS),

[_LAYER4] = LAYOUT_split_3x5_3(KC_LPRN, KC_RPRN, KC_LT, KC_GT, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_NO,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS),

[_LAYER5] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_7, KC_8, KC_9, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_4, KC_5, KC_6, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_1, KC_2, KC_3, KC_NO,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                                        KC_PENT, KC_0),

[_MOUSELAYER] = LAYOUT_split_3x5_3(WINDOW_SWITCH_MODE,ARROWMODE,VOL_MODE,KC_NO , KC_NO,                  KC_NO, CPI_MACOS, CPI_WIN, MAGIC_SWAP_LCTL_LGUI, MAGIC_UNSWAP_LCTL_LGUI,
                               SLOW_SCROLL_MODE, FAST_SCROLL_MODE, KC_BTN2, KC_BTN1, KC_NO,                KC_NO, KC_BTN1, KC_BTN2, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                           KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                                           KC_TRNS, KC_TRNS, KC_TRNS,                                            KC_TRNS, KC_TRNS),



};
