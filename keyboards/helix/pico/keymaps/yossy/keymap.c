#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "keymap_jp.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
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
  L_SPC,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CAPS |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Enter|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |  Up  |  /   |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | Ctrl | Alt  | GUI  |A_EISU|A_EISU| L_SPC| L_SPC| L_SPC| L_SPC|G_KANA|G_KANA| Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */

[_QWERTY] = LAYOUT( \
      KC_TAB,   KC_Q,    KC_W,    KC_E,             KC_R,             KC_T,                KC_Y,  KC_U,             KC_I,             KC_O,    KC_P,    KC_BSPC, \
      KC_CAPS,  KC_A,    KC_S,    KC_D,             KC_F,             KC_G,                KC_H,  KC_J,             KC_K,             KC_L,    JP_SCLN, KC_ENT,  \
      KC_LSFT,  KC_Z,    KC_X,    KC_C,             KC_V,             KC_B,                KC_N,  KC_M,             JP_COMM,          JP_DOT,  KC_UP,   JP_SLSH, \
      KC_LCTL,  KC_LALT, KC_LGUI, LGUI_T(KC_LANG2), LGUI_T(KC_LANG2), L_SPC, L_SPC, L_SPC, L_SPC, RGUI_T(KC_LANG1), RGUI_T(KC_LANG1), KC_LEFT, KC_DOWN, KC_RGHT \
			),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   1  |   2  |   3  |   4  |   5  |   6  |             |   7  |   8  |   9  |   0  |   -  |  ^   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |  ESC |  F1  |  F2  |  F3  |  F4  |             |  F6  |   |  |   \  |   :  |   @  |  _   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |  F5  |  F6  |  F7  |  Adj |             |  F12 |      |      |      | Vol+ | Bli+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |   `  |      | Vol- | Bli- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,                      JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS, JP_CIRC, \
      KC_GRV,  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,                     KC_F6,   JP_PIPE, JP_YEN,  JP_AT,   JP_COLN,   JP_UNDS, \
      _______, _______, KC_F5,   KC_F6,   KC_F7,   ADJUST,                    KC_F12,  _______, JP_LBRC, JP_RBRC, KC_VOLU, KC_BRMU, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_BRMD  \
a      ),

  /* Adjust
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Aud on|Audoff|MU TOG|MU MOD| Mac  |             | Win  |Qwerty|Colemk|Dvorak|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |CK TOG|CK RST| CK UP|CK DWN|      |             |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      _______, RESET,   RGBRST,  _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, CK_UP,   CK_TOGG, MU_TOG,  AU_ON,   _______,                   AG_SWAP, QWERTY,  _______, _______,  _______, _______, \
      _______, CK_DOWN, CK_RST,  MU_MOD,  AU_OFF,  _______,                   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};



#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
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
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case L_SPC:
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
  	case KC_RCTL:
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
    _delay_ms(50); // gets rid of tick
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

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
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
  }
  matrix_update(&display, &matrix);
}

#endif
