# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MUSIC_ENABLE = no
BLUETOOTH_ENABLE = no
#SECURE_ENABLE = yes
#AUTO_SHIFT_ENABLE=yes
AVR_USE_MINIMAL_PRINTF = yes
CAPS_WORD_ENABLE=yes

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
#BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
#RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
#RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
#RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes
EXTRAFLAGS += -flto
LTO_ENABLE=yes
QMK_SETTINGS=no

#TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes


AUDIO_SUPPORTED = no
#RGB_MATRIX_SUPPORTED = yes
#RGBLIGHT_SUPPORTED = yes

LAYOUTS = split_3x5_3

POINTING_DEVICE_ENABLE = yes # Enable trackball
POINTING_DEVICE_DRIVER = adns9800
