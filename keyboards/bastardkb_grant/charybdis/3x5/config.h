/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#pragma once

/* Key matrix configuration. */
#define MATRIX_ROWS 8 // Rows are doubled-up.
#define MATRIX_COLS 5

#define DIODE_DIRECTION ROW2COL

<<<<<<< HEAD:keyboards/bastardkb_grant/charybdis/3x5/config.h
/* Handedness. */
#define MASTER_RIGHT

/* Bootmagic Lite configuration. */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

/* serial.c configuration (for split keyboard) */
#define SOFT_SERIAL_PIN D0

=======
>>>>>>> 3dae56b634e610ce72fdcb9bd3bff2dda330b83e:keyboards/bastardkb/charybdis/3x5/config.h
/* Set 0 if debouncing isn't needed. */
#define DEBOUNCE 5

/* Trackball angle adjustment. */
#define ROTATIONAL_TRANSFORM_ANGLE -25

/* RGB settings. */
<<<<<<< HEAD:keyboards/bastardkb_grant/charybdis/3x5/config.h

//#define RGB_DI_PIN D3
//#define RGBLED_NUM 35
//#define RGBLED_SPLIT \
    { 18, 17 }

/* RGB matrix support. */
=======
>>>>>>> 3dae56b634e610ce72fdcb9bd3bff2dda330b83e:keyboards/bastardkb/charybdis/3x5/config.h
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 36
#    define RGB_MATRIX_SPLIT \
        { 18, 18 }
#endif
