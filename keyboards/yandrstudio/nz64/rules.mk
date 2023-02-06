# MCU name
MCU = STM32F401
BOARD = GENERIC_STM32_F401XC

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
<<<<<<<< HEAD:keyboards/bastardkb_old/tbkmini/rules.mk
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
LTO_ENABLE = yes

AUDIO_SUPPORTED = no
RGB_MATRIX_SUPPORTED = yes
RGBLIGHT_SUPPORTED = yes

LAYOUTS = split_3x6_3
========
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
WS2812_DRIVER = pwm         # Driver for RGB
>>>>>>>> 3dae56b634e610ce72fdcb9bd3bff2dda330b83e:keyboards/yandrstudio/nz64/rules.mk
