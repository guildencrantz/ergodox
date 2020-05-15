#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

enum custom_keycodes {
  RGB_SLD = SAFE_RANGE, // can always be here
  EPRM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(KC_MINUS,KC_1,KC_2,KC_3,KC_4,KC_5,KC_TRANSPARENT,KC_BSLASH,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_TRANSPARENT,KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_LSHIFT,LCTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,KC_TRANSPARENT,KC_LGUI,KC_GRAVE,KC_LEFT,KC_RIGHT,LALT_T(KC_NO),KC_PGUP,KC_PGDOWN,KC_INSERT,KC_ENTER,KC_ESCAPE,LCTL_T(KC_NO),KC_TRANSPARENT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_EQUAL,KC_LBRACKET,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,KC_BSLASH,KC_N,KC_M,KC_COMMA,KC_DOT,KC_KP_SLASH,KC_RSHIFT,RALT_T(KC_NO),KC_UP,KC_DOWN,KC_TRANSPARENT,KC_RGUI,KC_HOME,KC_END,KC_DELETE,RCTL_T(KC_NO),KC_BSPACE,KC_SPACE),

};

bool suspended = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
