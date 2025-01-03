// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2023 QMK


#include QMK_KEYBOARD_H

#define HO_Z MT(MOD_LSFT,KC_Z)
#define HO_X MT(MOD_LALT,KC_X)
#define HO_C MT(MOD_LCTL,KC_C)
#define HO_D MT(MOD_LGUI,KC_D)
#define HO_Q HYPR_T(KC_Q)

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
    VIM_TABN,
    VIM_TABP,
    VIM_TABNEW,
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

combo_t key_combos[] = {
    COMBO(combo1, KC_ESC),
    COMBO(combo2, LSFT(KC_9)),     // (
    COMBO(combo3, KC_LBRC),        // [
    COMBO(combo4, LSFT(KC_LBRC)),  // {
    COMBO(combo5, LSFT(KC_RBRC)),  // }
    COMBO(combo6, KC_RBRC),        // ]
    COMBO(combo7, LSFT(KC_0)),     // )
    COMBO(combo8, LSFT(KC_SCLN)),  // :
};


bool process_record_user(uint16_t keycode, keyrecord_t* record)
{

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

        case VIM_TABN:
            tap_code(KC_ESC);
            SEND_STRING(":tabn");
            tap_code(KC_ENTER);
            return false;
        case VIM_TABP:
            tap_code(KC_ESC);
            SEND_STRING(":tabp");
            tap_code(KC_ENTER);
            return false;
        case VIM_TABNEW:
            tap_code(KC_ESC);
            SEND_STRING(":tabnew");
            tap_code(KC_ENTER);
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
            send_string_with_delay(":EslintFixAll",1);
            tap_code(KC_ENTER);
            tap_code(KC_ESC);
            send_string_with_delay(":w",1);
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
     * │SHFT│ALT │    │    │    │          │    │    │    │ALT │SHFT│
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │NAV │CMD │    ││    │    │NUMS│
     *                └────┴────┴────┘└────┴────┴────┘
     *
     */
    [0] = LAYOUT_ortho36(
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
        HO_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC,
        KC_A,    KC_S,    KC_R,    KC_T,    KC_G,       KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        HO_Z,    HO_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H,    KC_COMM, HO_DOT,  HO_SLSH,
                          MO(3), ESCMD,   KC_BSPC,    KC_SPACE,ENTCTL,  MO(2)
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
    /*
     * NAV
     *
     * ┌────┬────┬────┬────┬────┐          ┌────┬────┬────┬────┬────┐
     * │ESC │    │SC  │SC  │    │          │    │    │    │    │    │
     * │    │    │TAB │TAB │    │          │    │    │ UP │    │DEL │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │TAB │    │STAB│TAB │    │          │PGUP│ <- │DOWN│ -> │ENTR│
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │    │    │SCMD│CMD │    │          │    │    │    │    │    │
     * │CTL │    │TAB │TAB │    │          │PGDN│    │    │    │CTL │
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │BRAC│    │    ││    │    │XXXX│
     *                └────┴────┴────┘└────┴────┴────┘
     *
     */
    [2] = LAYOUT_ortho36(
    //  #######  #######  #######  #######   #######     #######   ########  #######  ########  ########
        KC_ESC, _______,  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB), _______, _______,  _______,  KC_UP,    _______,  KC_DEL,
        KC_TAB,  _______, LSFT(KC_TAB), KC_TAB,_______,    KC_PGUP,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_ENTER,
        KC_LCTL, _______, LSFT(LGUI(KC_TAB)),  LGUI(KC_TAB),  _______,    KC_PGDN,  XXXXXXX, XXXXXXX, XXXXXXX,  KC_RCTL,
                          MO(5), LSFT(KC_SCLN),  _______,       _______,  _______,_______
    //  #######  #######  #######       #######   #######     #######   #######   #######  #######  #######
    ),

    /*
     * NUMS
     *
     * ┌────┬────┬────┬────┬────┐          ┌────┬────┬────┬────┬────┐
     * │ 1  │ 2  │ 3  │ 4  │ 5  │          │ 6  │ 7  │ 8  │ 9  │ 0  │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │ !  │ @  │ #  │ $  │ %  │          │ ^  │ &  │ *  │ (  │ )  │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │ \  │ |  │ "  │ '  │ `  │          │ ~  │ -  │ +  │ =  │ _  │
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │XXXX│    │    ││    │VIM │BRAC│
     *                └────┴────┴────┘└────┴────┴────┘
     */
    [3] = LAYOUT_ortho36(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5), LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),LSFT(KC_0),
        KC_BACKSLASH, LSFT(KC_BACKSLASH), LSFT(KC_QUOTE), KC_QUOTE, KC_GRAVE,    LSFT(KC_GRAVE), KC_MINUS, LSFT(KC_EQUAL), KC_EQUAL, LSFT(KC_MINUS),
                          _______, _______, _______,    _______,MO(4), MO(5)
    ),

    //
    //  VIM SHORTCUTS
    //
    [4] = LAYOUT_ortho36(
    //  #######  #######  #######    #######  #######     #######  #######  #######  #######  #######
        VIM_QUIT,_______, VIM_FILES, _______, VIM_BUFS,    VIM_MVU, _______, VIM_WU, _______, QK_BOOT,
        _______, VIM_SAVE,VIM_TABP,  VIM_TABN,VIM_TABNEW,   VIM_MVD, VIM_WL, VIM_WD, VIM_WR, VIM_CMD,
        _______, _______, VIM_COPY,  _______, VIM_PASTE,    _______, _______, _______, _______, _______,
                          _______,   _______, _______,    _______, _______, _______
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
    ),

    /*
     * BRACKETS
     *
     * ┌────┬────┬────┬────┬────┐          ┌────┬────┬────┬────┬────┐
     * │    │    │    │    │    │          │    │PLAY│VOLU│VOLD│    │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │    │ (  │ [  │ {  │ ;  │          │ :  │ }  │ ]  │ )  │    │
     * ├────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┤
     * │    │    │    │    │    │          │    │    │    │    │    │
     * └────┴────┴────┼────┼────┼────┐┌────┼────┼────┼────┴────┴────┘
     *                │XXXX│    │    ││    │    │XXXX│
     *                └────┴────┴────┘└────┴────┴────┘
     */
    [5] = LAYOUT_ortho36(
    //  #######  #######  #######  #######        #######     #######  #######  #######  #######  #######
        _______, _______, _______, _______,      _______,    KC_MPLY, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, _______, _______,
        _______, LSFT(KC_9),KC_LBRC, LSFT(KC_LBRC),KC_SCLN,    LSFT(KC_SCLN), LSFT(KC_RBRC), KC_RBRC,LSFT(KC_0),   _______,
        _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
                          _______, _______, _______,    _______, _______, _______
    //  #######  #######  #######  #######  #######     #######  #######  #######  #######  #######
    ),
};



