#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#include "keymap_jp.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOW_SPACE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CAPS |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Enter|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |  Up  |  /   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Alt  | GUI  |A_EISU|A_EISU| L_SPC| L_SPC| L_SPC| L_SPC|G_KANA|G_KANA| Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      _______,  _______, _______, _______,     _______,     _______,                                      _______,       _______,            _______,            _______, _______, _______, \
      KC_TAB,   KC_Q,    KC_W,    KC_E,        KC_R,        KC_T,                                         KC_Y,          KC_U,               KC_I,               KC_O,    KC_P,    KC_BSPC, \
      KC_CAPS,  KC_A,    KC_S,    KC_D,        KC_F,        KC_G,                                         KC_H,          KC_J,               KC_K,               KC_L,    JP_SCLN, KC_ENT,  \
      KC_LSFT,  KC_Z,    KC_X,    KC_C,        KC_V,        KC_B,           JP_LBRC,       JP_RBRC,       KC_N,          KC_M,               JP_COMM,            JP_DOT,  KC_UP,   JP_SLSH, \
      KC_LCTL,  KC_LALT, KC_LGUI, LT(2, KC_LANG2), LT(2, KC_LANG2), LOW_SPACE, LOW_SPACE, LOW_SPACE, LOW_SPACE, RGUI_T(KC_LANG1), RGUI_T(KC_LANG1), KC_LEFT, KC_DOWN, KC_RGHT \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   1  |   2  |   3  |   4  |   5  |   6  |             |   7  |   8  |   9  |   0  |   -  |  ^   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |  ESC |  F1  |  F2  |  F3  |  F4  |             |  F6  |   |  |   \  |   :  |   @  |  _   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F5  |  F6  |  F7  |  F8  |  (   |   )  |  F12 |      |      |      | Vol+ | Bli+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |   `  |      | Vol- | Bli- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, \
      JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,                     JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS, JP_CIRC, \
      KC_GRV,  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,                    KC_F6,   JP_PIPE, JP_YEN,  JP_COLN, JP_AT,   JP_UNDS, \
      _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,  JP_LCBR, JP_RCBR, KC_F12,  _______, JP_LBRC, JP_RBRC, KC_VOLU, KC_BRMU, \
      _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_BRMD  \
      ),

  /* Adjust
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |Qwerty|      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______ , _______, \
      _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL,   \
      _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, QWERTY,  _______, _______, _______, _______,  \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,  \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD   \
      )
};

#else
#error "undefined keymaps"
#endif

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool mod_key_pressed = false;
bool shift_key_pressed = false;
bool char_key_pressed = false;
bool lower_tapped = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOW_SPACE:
			if (mod_key_pressed || char_key_pressed) {
				if (record->event.pressed){
					register_code(KC_SPC);
					unregister_code(KC_SPC);
				} else {
					layer_off(_LOWER);
					lower_tapped = false;
				}
			} else {
				if (record->event.pressed){
					lower_tapped = true;
					layer_on(_LOWER);
				} else {
					layer_off(_LOWER);

					if (lower_tapped) {
						register_code(KC_SPC);
						unregister_code(KC_SPC);
					}
					lower_tapped = false;
				}
			}
      return false;
      break;
    case QWERTY:
			persistent_default_layer_set(1UL<<_QWERTY);
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
		  break;
	  case KC_RGUI:
	  case KC_LGUI:
	  case KC_LALT:
	  case KC_LCTL:
			if (record->event.pressed){
 				mod_key_pressed = true;
			} else {
        mod_key_pressed = false;
			}
			return true;
			break;
	  case KC_LSFT:
			if (record->event.pressed){
				shift_key_pressed = true;
			} else {
        shift_key_pressed = false;
			}
			return true;
			break;
    default:
			if (record->event.pressed){
				char_key_pressed = true;
				lower_tapped = false;
			} else {
        char_key_pressed = false;
			}
			return true;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_ADJUST (1<<_ADJUST)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
