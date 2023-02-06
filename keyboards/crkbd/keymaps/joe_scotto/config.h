/*
Copyright 2022 Joe Scotto

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

#pragma once

#include "config_common.h"

<<<<<<< HEAD:keyboards/boardsource/microdox/config.h
#define VENDOR_ID       0xF7E0
#define PRODUCT_ID      0x0412
#define DEVICE_VER      0x0000
#define MANUFACTURER    Boardsource
#define PRODUCT         microdox


#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT


=======
>>>>>>> 3dae56b634e610ce72fdcb9bd3bff2dda330b83e:keyboards/crkbd/keymaps/joe_scotto/config.h
/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS  8
#define MATRIX_COLS  6
#define MATRIX_ROW_PINS \
    { D4, C6, D7, E6 }

// wiring of each half
#define MATRIX_COL_PINS \
    { F4, F5, F6, F7, B1, B3 }
// #define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

<<<<<<< HEAD:keyboards/boardsource/microdox/config.h
/* ws2812 RGB LED */
#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN D3
#define RGBLED_SPLIT { 6, 6 }
#define EE_HANDS
#ifdef RGBLIGHT_ENABLE
#define RGBLED_NUM 12    // Number of LEDs
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION


=======
>>>>>>> 3dae56b634e610ce72fdcb9bd3bff2dda330b83e:keyboards/crkbd/keymaps/joe_scotto/config.h
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
<<<<<<< HEAD:keyboards/boardsource/microdox/config.h
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
=======

#define TAPPING_TERM 50
>>>>>>> 3dae56b634e610ce72fdcb9bd3bff2dda330b83e:keyboards/crkbd/keymaps/joe_scotto/config.h
