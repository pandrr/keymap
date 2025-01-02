// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2023 QMK


#include QMK_KEYBOARD_H

#define HO_Z MT(MOD_LSFT,KC_Z)
#define HO_X MT(MOD_LALT,KC_X)
#define HO_C MT(MOD_LCTL,KC_C)
#define HO_D MT(MOD_LGUI,KC_D)
#define HO_V HYPR_T(KC_V)

#define HO_K    HYPR_T(KC_K)
#define HO_H    MT(MOD_RGUI,KC_H)
#define HO_COMM MT(MOD_RCTL,KC_COMM)
#define HO_DOT  MT(MOD_RALT,KC_DOT)
#define HO_SLSH MT(MOD_RSFT,KC_SLSH)


#define ESCMD MT(MOD_LGUI,KC_ESC)
#define ENTCTL MT(MOD_LCTL,KC_ENTER)

enum custom_keycodes {
    VIM_CMD = SAFE_RANGE,
    VIM_FILES,
    VIM_BUFS,
    VIM_MVU,
    VIM_COPY,
    VIM_PASTE,
    VIM_MVD,
    VIM_QUIT,
    VIM_SAVE,
    VIM_WL,
    VIM_WR,
    VIM_WU,
    VIM_WD,
    L3_HYPR,
};

/*
     *
     * DUAL:
     * ┌────┬────┬────┬────┬────┐          ┌────┬────┬────┬────┬────┐
     * │   ESC   (    [    {    │          │    }    ]    )    │    │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │    │    │    │    │    │          │    │    │    │    :    │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │    │    │    │    │    │          │    │    │    │    │    │
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │    │    │    ││    │    │    │
     *                └────┴────┴────┘└────┴────┴────┘
     */

const uint16_t PROGMEM combo1[] = {KC_Q, KC_W, COMBO_END};

const uint16_t PROGMEM combo2[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_P, KC_B, COMBO_END};

const uint16_t PROGMEM combo5[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo7[] = {KC_U, KC_Y, COMBO_END};

const uint16_t PROGMEM combo8[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo9[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo10[] = {KC_SPACE, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo1, KC_ESC),
    COMBO(combo2, LSFT(KC_9)),     // (
    COMBO(combo3, KC_LBRC),        // [
    COMBO(combo4, LSFT(KC_LBRC)),  // {
    COMBO(combo5, LSFT(KC_RBRC)),  // }
    COMBO(combo6, KC_RBRC),        // ]
    COMBO(combo7, LSFT(KC_0)),     // )
    COMBO(combo8, LSFT(KC_SCLN)),  // :
    COMBO(combo9, KC_SCLN),        //;
};

static uint16_t colon_timer;
uint8_t hyprCount=0;

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
        case L3_HYPR:
            if (record->event.pressed) {
                if (timer_elapsed(colon_timer) > 500 )hyprCount=0;
                colon_timer = timer_read();
                if (hyprCount==0) layer_on(3);
                if (hyprCount==1) set_mods(MOD_MASK_CSAG);
                hyprCount++;
            } else {
                layer_off(3);
                clear_mods();
            }
            return false;
    }

    if (record->event.pressed)
    {
    switch (keycode)
    {
        case VIM_CMD:
            tap_code(KC_ESC);
            SEND_STRING(":");
            return false;

        case VIM_WL:
            tap_code(KC_ESC);
            SEND_STRING(SS_LCTL("w"));
            SEND_STRING("h");
            return false;
        case VIM_WR:
            tap_code(KC_ESC);
            SEND_STRING(SS_LCTL("w"));
            SEND_STRING("l");
            return false;
        case VIM_WU:
            tap_code(KC_ESC);
            SEND_STRING(SS_LCTL("w"));
            SEND_STRING("k");
            return false;
        case VIM_WD:
            tap_code(KC_ESC);
            SEND_STRING(SS_LCTL("w"));
            SEND_STRING("j");
            return false;


        case VIM_QUIT:
            tap_code(KC_ESC);
            SEND_STRING(":qa!");
            tap_code(KC_ENTER);
            return false;
        case VIM_FILES:
            tap_code(KC_ESC);
            SEND_STRING(" ff");
            return false;
        case VIM_BUFS:
            tap_code(KC_ESC);
            SEND_STRING(" fb");
            return false;
        case VIM_MVU:
            tap_code(KC_ESC);
            SEND_STRING("ddkP");
            return false;
        case VIM_MVD:
            tap_code(KC_ESC);
            send_string_with_delay("ddp",10);
            return false;
        case VIM_COPY:
            tap_code(KC_ESC);
            send_string_with_delay("\"+y",30);
            return false;
        case VIM_PASTE:
            tap_code(KC_ESC);
            send_string_with_delay("\"+p",30);
            return false;
        case VIM_SAVE:
            tap_code(KC_ESC);
            send_string_with_delay(":EslintFixAll",10);
            tap_code(KC_ENTER);
            tap_code(KC_ESC);
            send_string_with_delay(":w",10);
            tap_code(KC_ENTER);
            return false;
    }
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *
     * HOLD:
     * ┌────┬────┬────┬────┬────┐          ┌────┬────┬────┬────┬────┐
     * │    │    │    │    │    │          │    │    │    │    │    │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │    │    │    │    │    │          │    │    │    │    │    │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │SHFT│ALT │CTRL│CMD │HYPR│          │HYPR│CMD │CTRL│ALT │SHFT│
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │NAV │CMD │    ││    │    │NUMS│
     *                └────┴────┴────┘└────┴────┴────┘
     *
     */
    [0] = LAYOUT_ortho36(
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
        KC_Q,  KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC,
        KC_A,    KC_S,    KC_R,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        HO_Z,    HO_X,    KC_C,    KC_D,    HO_V,       HO_K,    KC_H,    KC_COMM, HO_DOT,  HO_SLSH,
                          L3_HYPR,   ESCMD,   KC_BSPC,    KC_SPACE,  ENTCTL,  MO(2)
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
    ),
    [1] = LAYOUT_ortho36(
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        KC_A,    KC_S,    KC_R,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                          _______, _______, _______,    _______, _______, _______
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
    ),
    [2] = LAYOUT_ortho36(
    //  #######  #######  #######   #######   #######     #######   ########  #######  ########  ########
        KC_ESC, _______,  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB), _______,   _______,  _______,   _______,  KC_DEL,
        KC_TAB,  _______, _______,  LSFT(KC_TAB), KC_TAB,KC_UP,  KC_PGUP,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_ENTER,
        _______, _______, _______,  _______,  _______,    KC_PGDN,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
                          MO(4),   _______,  _______,       _______,  _______,_______
    //  #######  #######  #######       #######   #######     #######   #######   #######  #######  #######
    ),

    /*
     * NUMS
     *
     * ┌────┬────┬────┬────┬────┐          ┌────┬────┬────┬────┬────┐
     * │ !  │ @  │ #  │ $  │ %  │          │ ^  │ &  │ *  │ (  │ )  │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │ 1  │ 2  │ 3  │ 4  │ 5  │          │ 6  │ 7  │ 8  │ 9  │ 0  │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │ \  │ |  │ "  │ '  │ `  │          │ ~  │ -  │ +  │ =  │ _  │
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │    │    │    ││    │ L5 │ L4 │
     *                └────┴────┴────┘└────┴────┴────┘
     */
    [3] = LAYOUT_ortho36(
        LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5), LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0),
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_BACKSLASH, LSFT(KC_BACKSLASH), LSFT(KC_QUOTE), KC_QUOTE, KC_GRAVE,    LSFT(KC_GRAVE), KC_MINUS, LSFT(KC_EQUAL), KC_EQUAL, LSFT(KC_MINUS),
                          _______, _______, _______,    _______, MO(5), MO(4)
    ),

    //
    //  APP SHORTCUTS
    //
    [4] = LAYOUT_ortho36(
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
        VIM_QUIT, _______, VIM_FILES, _______, VIM_BUFS,    VIM_MVU, _______, VIM_WU, _______, QK_BOOT,
        _______, VIM_SAVE, _______, VIM_CMD, _______,   VIM_MVD, VIM_WL, VIM_WD, VIM_WR, _______,
        _______, _______, VIM_COPY, _______, VIM_PASTE,    _______, _______, KC_MPLY, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP,
                          _______, _______, _______,    _______, _______, _______
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
    ),

    //
    // MOUSE
    //
    [5] = LAYOUT_ortho36(
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
        _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,    _______, MS_BTN1, MS_BTN3, MS_BTN3, _______,
        _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
                          _______, _______, _______,    _______, _______, _______
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
    ),
};


