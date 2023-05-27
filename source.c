#include QMK_KEYBOARD_H

enum layer_names {
    _COLEMAK,
    _FN_MEDIA_COPY_PRINT,
    _NAVIGATION_LAYER
};

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
            // Host Keyboard Layer Status
            oled_write_P(PSTR("Layer: "), false);
            switch (get_highest_layer(layer_state)) {
                case _COLEMAK:
                    oled_write_P(PSTR("Colemak\n"), false);
                    break;
                case _FN_MEDIA_COPY_PRINT:
                    oled_write_P(PSTR("Fn Media Copy/Pase\n"), false);
                    break;
                case _NAVIGATION_LAYER:
                    oled_write_P(PSTR("Navigation\n"), false);
                    break;
                default:
                    // Or use the write_ln shortcut over adding '\n' to the end of your string
                    oled_write_ln_P(PSTR("Undefined"), false);
        }
        // Host Keyboard WPM status
        char wpm_str[10];
        sprintf(wpm_str, "WPM: %03d", get_current_wpm(void));
        oled_write(wpm_str, false);
    } else {
        render_logo();  // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    }
    return false;
}
#endif
