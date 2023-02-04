#include QMK_KEYBOARD_H
#include <stdio.h>

char wpm_str[10];
uint16_t wpm_graph_timer = 0;

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
};

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define _LAYER6 6
#define _LAYER7 7
#define _LAYER8 8




 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_LAYER0] = LAYOUT_split_3x5_3(KC_Q, KC_W, KC_E, KC_R, KC_T,							                                KC_Y, KC_U, KC_I, KC_O, KC_P,
 								MT(MOD_LGUI, KC_A), MT(MOD_LALT,KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT,KC_F), KC_G, 	KC_H, MT(MOD_LSFT,KC_J), MT(MOD_LCTL,KC_K), MT(MOD_LALT,KC_L), MT(MOD_LGUI, KC_SCLN),
								KC_Z, KC_X, KC_C, KC_V, KC_B, 							                                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
								KC_LCTL, KC_LSFT, LT(1,KC_ENT), 						                                LT(2,KC_BSPC), KC_SPC, KC_LALT),

[_LAYER1] = LAYOUT_split_3x5_3(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
                               KC_1, KC_2, LT(5,KC_3), LT(3,KC_4), KC_5,                          KC_6, KC_7, KC_8, KC_9, KC_0,
                               KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2,                                   KC_NO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
                                                KC_NO, KC_NO, KC_NO,                                    KC_NO, KC_NO, KC_NO),

[_LAYER2] = LAYOUT_split_3x5_3(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, LCTL(LSFT(KC_I)), KC_NO, KC_NO,
                        KC_PIPE, KC_BSLS, KC_GRV, KC_DQUO, KC_QUOT,                                     KC_NO, LT(4,KC_NO), KC_NO, KC_DQUO, KC_QUOT,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_LALT, KC_TAB, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO, KC_NO,                                        KC_NO, KC_NO, KC_NO),

[_LAYER3] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,                                     KC_NO, KC_NO, KC_UP, KC_NO, KC_NO,
                               KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO,                               KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO,
                                                    KC_NO, KC_TRNS, KC_NO,                              KC_NO, KC_NO, KC_NO),

[_LAYER4] = LAYOUT_split_3x5_3(KC_LPRN, KC_RPRN, KC_LT, KC_GT, KC_NO,                                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_NO,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                                    KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO),
/*
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
[_LAYER5] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_7, KC_8, KC_9, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_4, KC_5, KC_6, KC_NO,
                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                       KC_NO, KC_1, KC_2, KC_3, KC_NO,
                                            KC_NO, KC_NO, KC_NO,                                        KC_PENT, KC_0, KC_NO)

};


/*

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}


static void render_status(void) {
    // QMK Logo and version information

#ifdef WPM_ENABLE
    // Write WPM
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write_P(PSTR("\n"), false);
    oled_write(wpm_str, false);
#endif
}

static uint8_t zero_bar_count = 0;
static uint8_t bar_count = 0;

static void render_wpm_graph(void) {
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;

    if (wpm_graph_timer == 0) {

	wpm_graph_timer = timer_read();
	return;
    }
    if(timer_elapsed(wpm_graph_timer) > 500) {
	wpm_graph_timer = timer_read();

	if(OLED_DISPLAY_HEIGHT == 64)
		bar_height = get_current_wpm() / 2;
	if(OLED_DISPLAY_HEIGHT == 32)
		bar_height = get_current_wpm() / 4;
	if(bar_height > OLED_DISPLAY_HEIGHT)
		bar_height = OLED_DISPLAY_HEIGHT;

	if(bar_height == 0) {
	    // keep track of how many zero bars we have drawn.  If
	    // there is a whole screen worth, turn the display off and
	    // wait until there is something to do
	    if (zero_bar_count > OLED_DISPLAY_WIDTH) {
		oled_off();
		return;
	    }
	    zero_bar_count++;
	} else
	    zero_bar_count=0;

	oled_pan(false);
	bar_count++;
	for (uint8_t i = (OLED_DISPLAY_HEIGHT / 8); i > 0; i--) {
	    if (bar_height > 7) {
		if (i % 2 == 1 && bar_count % 3 == 0)
		    bar_segment = 254;
		else
		    bar_segment = 255;
		bar_height -= 8;
	    } else {
		switch (bar_height) {
		    case 0:
			bar_segment = 0;
			break;

		    case 1:
			bar_segment = 128;
			break;

		    case 2:
			bar_segment = 192;
			break;

		    case 3:
			bar_segment = 224;
			break;

		    case 4:
			bar_segment = 240;
			break;

		    case 5:
			bar_segment = 248;
			break;

		    case 6:
			bar_segment = 252;
			break;

		    case 7:
			bar_segment = 254;
			break;
		}
		bar_height = 0;

		if (i % 2 == 1 && bar_count % 3 == 0)
		    bar_segment++;
	    }
	    oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_WIDTH);
	}
    }
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_wpm_graph();
        render_status();
    }
    else {
        render_qmk_logo(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)

    }
}
#endif
*/
