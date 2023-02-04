#include QMK_KEYBOARD_H
#include <stdio.h>


static bool scrolling_mode = false;

uint16_t macos_dpi = 7800;
uint16_t win_dpi= 7000;
uint16_t slow_dpi = 3200;
uint16_t extra_fast_dpi = 7000;
uint16_t default_dpi = 7000;

static int8_t scroll_h;
static int8_t scroll_v;



enum custom_keycodes {
    BASE = SAFE_RANGE,
    MEDIA,
    NAV,
    MOUSE,
    SYM,
    NUM,
    FUN,
    BUTTON,
    FAST_SCROLL_MODE,
    //SLOW_SCROLL_MODE,
    CPI_FAST,
    CPI_SLOW,
    CPI_MACOS,
    CPI_DEFAULT
};

#define _BASE 0
#define _MEDIA 1
#define _NAV 2
#define _MOUSE 3
#define _SYM 4
#define _NUM 5
#define _FUN 6
#define _BUTTON 7
//#define _LAYER8 8
//#define _SHORTCUTLAYER 6



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {




    case CPI_FAST:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed

            pointing_device_set_cpi(extra_fast_dpi);
        }
        else{
            pointing_device_set_cpi(default_dpi);
        }
        break;

    case CPI_SLOW:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            pointing_device_set_cpi(slow_dpi);
        }
        else{
            pointing_device_set_cpi(default_dpi);
        }
        break;
    case CPI_DEFAULT:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            default_dpi = win_dpi;
            pointing_device_set_cpi(default_dpi);
        }
        break;
    case CPI_MACOS:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            default_dpi = macos_dpi;
            pointing_device_set_cpi(default_dpi);
        }
        break;






    case FAST_SCROLL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed

                scrolling_mode = true;
                //window_switch_mode_bool = false;
                pointing_device_set_cpi(4400);


        }
        else {
            pointing_device_set_cpi(default_dpi);
            scrolling_mode = false;
        }
        break;
        /*
    case SLOW_SCROLL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed

                scrolling_mode = true;
                //window_switch_mode_bool = false;
                pointing_device_set_cpi(2000);


        }
        else {
            pointing_device_set_cpi(default_dpi);
            scrolling_mode = false;
        }
        break;

*/







    }


    return true;

};

void pointing_device_init_kb(){
    pointing_device_set_cpi(default_dpi);

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



    else {
        mouse_report.x = clamped_x;
        mouse_report.y = clamped_y;
    }
    return mouse_report;
}



//TODO
//add one hand (right hand) mouse combos
//right click, left click and scroll


//THESE ONLY WORK FOR THE trackball_miryoku KEYMAP
//right hand - one hand basic mouse
const uint16_t PROGMEM miryoku_right_hand_left_click[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM miryoku_fast_scroll_combo_one_hand[] = {KC_H, KC_DOT, COMBO_END};


//THIS IS THE SAME ON BOTH
const uint16_t PROGMEM right_hand_right_click[] = {KC_COMM,KC_DOT, COMBO_END};


combo_t key_combos[7] = {

    //THESE ONLY WORK FOR THE trackball_linux KEYMAP
    COMBO(right_hand_right_click, KC_BTN2),
    COMBO(miryoku_right_hand_left_click,KC_BTN1),
    COMBO(miryoku_fast_scroll_combo_one_hand,FAST_SCROLL_MODE)

};



 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
    BASIC STRUCTURE:

    |Q|W|E|R|T|     |Y|U|I|O|P|
    |A|S|D|F|G|     |H|J|K|L|;|
    |Z|X|C|V|B|     |N|M|,|.|
        |_|_|_|     |_|_|TRACKBALL|


*/
 [_BASE] = LAYOUT_split_3x5_3(                      KC_Q, KC_W, KC_F, KC_P, KC_B,							 KC_J, KC_L, KC_U, KC_Y, KC_QUOTE,
MT(MOD_LGUI, KC_A), MT(MOD_LALT,KC_R), MT(MOD_LCTL, KC_S), MT(MOD_LSFT,KC_T), KC_G, 	                     KC_M, MT(MOD_LSFT,KC_N), MT(MOD_LCTL,KC_E), MT(MOD_LALT,KC_I), MT(MOD_LGUI, KC_O),
								    KC_Z, LT(_FUN,KC_X), KC_C, KC_D, KC_V, 					     KC_K, KC_H, KC_COMM, KC_DOT,KC_SLSH,
								    LT(_MEDIA,KC_ESC), LT(_NAV,KC_TAB), LT(_MOUSE,KC_ENT), 		            LT(_NUM,KC_BSPC), LT(_SYM,KC_SPC)),

[_MEDIA] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                             KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
                               OSL(_BUTTON), KC_NO, KC_NO, KC_NO, KC_NO,                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_NO, KC_NO, KC_NO,                                KC_MPLY, KC_MUTE),

[_NAV] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                             KC_AGAIN, KC_PASTE, KC_UP, KC_COPY, KC_CUT,
                               KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                     KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_UNDO,
                               OSL(_BUTTON), KC_NO, KC_NO, KC_NO, KC_NO,                              KC_INSERT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                                KC_NO, KC_NO, KC_NO,                                KC_BSPC, KC_SPC),

[_MOUSE] = LAYOUT_split_3x5_3(KC_UNDO,KC_CUT, KC_COPY, KC_PASTE, KC_AGAIN,                               KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
                               CPI_MACOS,CPI_DEFAULT,KC_NO, FAST_SCROLL_MODE, KC_NO,           KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                               CG_SWAP, CG_NORM, KC_BTN2, KC_BTN1, KC_NO,                              KC_NO, KC_NO, KC_NO, KC_NO, OSL(_BUTTON),
                                                KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO),

[_SYM] = LAYOUT_split_3x5_3(S(KC_LBRC), S(KC_7), S(KC_8), S(KC_9), S(KC_RBRC),                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            S(KC_SCLN), S(KC_4), S(KC_5), S(KC_6), S(KC_EQL),               KC_NO,KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                            S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_BSLS),                KC_NO, KC_NO, KC_NO, KC_NO, OSL(_BUTTON),
                                                S(KC_DOT), S(KC_0), S(KC_MINS),                KC_NO, KC_NO),

[_NUM] = LAYOUT_split_3x5_3(KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_SCLN, KC_4, KC_5, KC_6, KC_EQL,                             KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                               KC_GRV, KC_1, KC_2, KC_3, KC_BSLS,                              KC_NO, KC_NO, KC_NO, KC_NO, OSL(_BUTTON),
                                                KC_DOT, KC_0, KC_MINS,                                KC_NO, KC_NO),

[_FUN] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            KC_PSCR, KC_F9, KC_F8, KC_F7, KC_F12,
                            KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                    KC_SCRL, KC_F6, KC_F5, KC_F4, KC_F11,
                            OSL(_BUTTON), KC_NO, KC_NO, KC_NO, KC_NO,                     KC_PAUS, KC_F3, KC_F2, KC_F1, KC_F10,
                                          KC_NO, KC_NO, KC_NO,                            KC_APP, KC_TRNS),

[_BUTTON] = LAYOUT_split_3x5_3(KC_UNDO,KC_CUT, KC_COPY, KC_PASTE, KC_AGAIN,                      KC_AGAIN, KC_PASTE, KC_COPY, KC_CUT,KC_UNDO,
                               KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                       KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                               KC_UNDO,KC_CUT, KC_COPY, KC_PASTE, KC_AGAIN,                    KC_AGAIN, KC_PASTE, KC_COPY, KC_CUT,KC_UNDO,
                                            KC_NO,KC_BTN2, KC_BTN1,                             KC_BTN1, KC_BTN2),

};





/*
#include QMK_KEYBOARD_H
#include <stdio.h>





char wpm_str[10];
uint16_t wpm_graph_timer = 0;

bool is_alt_tab_active = false;
static bool scrolling_mode = false;
static bool volume_mode = false; // ADD this near the begining of keymap.c
static bool full_arrow_mode_state = false;
static bool window_switch_mode_bool = false;
static bool lr_arrow_mode = false;

uint16_t alt_tab_timer = 0;     // we will be using them soon.


uint16_t macos_dpi = 7800;
uint16_t win_dpi= 7000;
uint16_t slow_dpi = 3200;
uint16_t extra_fast_dpi = 7000;
uint16_t default_dpi = 7000;

static int8_t scroll_h;
static int8_t scroll_v;


enum custom_keycodes {
    BASE = SAFE_RANGE,
    MEDIA,
    NAV,
    MOUSE,
    SYM,
    NUM,
    FUN,
    BUTTON,
    LAYER8,
    SHORTCUTLAYER,
    FULLARROWMODE,
    LRARROWMODE,
    VOL_MODE,q
    FAST_SCROLL_MODE,
    SLOW_SCROLL_MODE,
    WINDOW_SWITCH_MODE,
    CURLYBRACK,
    SQUAREBRACK,
    PARENTHESIS,
    TRIBRACK,
    ALT_TAB,
    CPI_FAST,
    CPI_SLOW,
    CPI_MACOS,
    CPI_DEFAULT,
    UPDATE
};

enum{
    MOUSELAYER_ACTIVATE,
    SLOW_DPI
};

#define _BASE 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
//#define _LAYER6 6
//#define _LAYER7 7
//#define _LAYER8 8
#define _SHORTCUTLAYER 6






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
    case UPDATE:
        if(record->event.pressed){
            SEND_STRING("sudo nala update "SS_DELAY(500)"&& "SS_DELAY(1000)"sudo nala upgrade -y"SS_TAP(X_ENTER)SS_DELAY(2000)"granthubbell");
        }
        break;



    case CPI_FAST:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed

            pointing_device_set_cpi(extra_fast_dpi);
        }
        else{
            pointing_device_set_cpi(default_dpi);
        }
        break;

    case CPI_SLOW:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            pointing_device_set_cpi(slow_dpi);
        }
        else{
            pointing_device_set_cpi(default_dpi);
        }
        break;
    case CPI_DEFAULT:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            default_dpi = 7000;
            pointing_device_set_cpi(default_dpi);
        }
        break;
    case CPI_MACOS:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            default_dpi = macos_dpi;
            pointing_device_set_cpi(default_dpi);
        }
        break;






    case FAST_SCROLL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!full_arrow_mode_state){
                full_arrow_mode_state = false;
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
            if (!full_arrow_mode_state){
                full_arrow_mode_state = false;
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




    case FULLARROWMODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!full_arrow_mode_state){
                full_arrow_mode_state = true;
                volume_mode = false;
                scrolling_mode = false;
                window_switch_mode_bool = false;
                pointing_device_set_cpi(200);
            }

        }
        else {
            pointing_device_set_cpi(default_dpi);
            full_arrow_mode_state = false;
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



    case VOL_MODE:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            if (!volume_mode){
                full_arrow_mode_state = false;
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
                full_arrow_mode_state = false;
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
            //volume_mode=false;
            //window_switch_mode_bool = false;
            full_arrow_mode_state = false;
            pointing_device_set_cpi(5600);
            break;
        case _LAYER5:
            scrolling_mode = true;
            //volume_mode=false;
            //window_switch_mode_bool = false;
            full_arrow_mode_state = false;
            pointing_device_set_cpi(2400);
            break;

        case _MOUSELAYER:
            if(full_arrow_mode_state){
                volume_mode = false;
                scrolling_mode=false;
                window_switch_mode_bool = false;
            }
            else if (window_switch_mode_bool){
                volume_mode = false;
                scrolling_mode=false;
                full_arrow_mode_state=false;
            }
            else{
                volume_mode = true;
                scrolling_mode=false;
                window_switch_mode_bool = false;
            }

            pointing_device_set_cpi(200);
            break;
        default:
            if (scrolling_mode || volume_mode || window_switch_mode_bool || full_arrow_mode_state) {  // check if we were scrolling before and set disable if so
                //window_switch_mode_bool = false;
                scrolling_mode = false;
                //volume_mode = false;
                full_arrow_mode_state = false;

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

    else if (full_arrow_mode_state){
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

        if(default_dpi == win_dpi){
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


//right hand - one hand basic mouse
const uint16_t PROGMEM right_hand_left_click[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM right_hand_right_click[] = {KC_COMM,KC_DOT, COMBO_END};
const uint16_t PROGMEM fast_scroll_combo_one_hand[] = {KC_M, KC_DOT, COMBO_END};

//two hand mouse mods
//const uint16_t PROGMEM volume_combo[] = {MT(MOD_LALT,KC_S), MT(MOD_LCTL, KC_D), COMBO_END};
//const uint16_t PROGMEM window_switch_combo[] = {MT(MOD_LGUI, KC_A),MT(MOD_LALT,KC_S), COMBO_END};
const uint16_t PROGMEM fast_scroll_combo_left[] = {MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F), COMBO_END};
const uint16_t PROGMEM full_arrow_mode_state_combo[] = {MT(MOD_LALT,KC_S), MT(MOD_LSFT,KC_F), COMBO_END};
const uint16_t PROGMEM slow_dpi_combo[] = {MT(MOD_LALT,KC_S),  MT(MOD_LCTL, KC_D), COMBO_END};
const uint16_t PROGMEM mouselayer_combo[] = {KC_G, MT(MOD_LGUI, KC_SCLN), COMBO_END};





combo_t key_combos[7] = {
    //COMBO(window_switch_combo, WINDOW_SWITCH_MODE),
    // COMBO(volume_combo,VOL_MODE),
    COMBO(right_hand_left_click, KC_BTN1),
    COMBO(right_hand_right_click, KC_BTN2), // keycodes with modifiers are possible too!
    COMBO(fast_scroll_combo_left, FAST_SCROLL_MODE),
    COMBO(fast_scroll_combo_one_hand, FAST_SCROLL_MODE),
    COMBO(full_arrow_mode_state_combo, FULLARROWMODE),
    COMBO(slow_dpi_combo,CPI_SLOW),
    COMBO(mouselayer_combo, LT(6,KC_NO)),

};




 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    BASIC STRUCTURE:

    |Q|W|E|R|T|     |Y|U|I|O|P|
    |A|S|D|F|G|     |H|J|K|L|;|
    |Z|X|C|V|B|     |N|M|,|.|/|
        |_|_|_|     |_|_|_|



 [_BASE] = LAYOUT_split_3x5_3(                      KC_Q, KC_W, KC_F, KC_P, KC_B,							 KC_J, KC_L, KC_U, KC_Y, KC_QUOTE,
MT(MOD_LGUI, KC_A), MT(MOD_LALT,KC_R), MT(MOD_LCTL, KC_S), MT(MOD_LSFT,KC_T), KC_G, 	                     KC_H, MT(MOD_LSFT,KC_J), MT(MOD_LCTL,KC_K), MT(MOD_LALT,KC_L), MT(MOD_LGUI, KC_SCLN),
								                      KC_Z, KC_X, KC_C, KC_V, KC_B, 					     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
								              OSM(MOD_LCTL), KC_LSFT, LT(1,KC_ENT), 						 LT(2,KC_BSPC), KC_SPC),

[_LAYER1] = LAYOUT_split_3x5_3(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KCPERC,                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
                               KC_1, KC_2, LT(5,KC_3), LT(3,KC_4), KC_5,                                KC_6, KC_7, KC_8, KC_9, KC_0,
                        KC_NO, KC_NO, KC_BTN2, KC_BTN1,KC_NO,                                   KC_NO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
                                                KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS),

[_LAYER2] = LAYOUT_split_3x5_3(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, LCTL(LSFT(KC_I)), KC_NO, KC_NO,
                        KC_PIPE, KC_BSLS, KC_GRV, KC_DQUO, KC_QUOT,                                     LT(6,KC_NO), LT(4,KC_NO), ALT_TAB, KC_DQUO, KC_QUOT,
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

[_SHORTCUTLAYER] = LAYOUT_split_3x5_3(QK_BOOTLOADER,MAGIC_UNSWAP_CTL_GUI,MAGIC_SWAP_CTL_GUI,KC_NO,KC_NO,            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               CPI_MACOS, KC_NO,KC_NO, UPDATE, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                           KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS),



};


*/


