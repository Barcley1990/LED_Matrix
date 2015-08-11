/*
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in
compliance with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS"
basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
License for the specific language governing rights and limitations
under the License.

Author: C_Classic (cclassicvideos@aol.com)
  Date: 18.12.2010
*/

#include  <avr/io.h>
#include  <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

// Treiber für Touch und LCD
#include "include/lcd.h"
#include "include/graphic.h"
#include "include/touch.h"
#include "include/fonts.h"

void Ex_KeyboardTextBox();
void Ex_CheckboxLabel();
void Ex_SliderProgress();
void Ex_Image();

const char icon[] PROGMEM = { //Image used for Imagebutton-Example
        0xFE,0xFF,0x07,
        0x03,0x00,0x0C,
        0x01,0x00,0x08,
        0x01,0x40,0x08,
        0x01,0xA0,0x08,
        0x01,0x50,0x09,
        0x01,0x88,0x08,
        0x01,0x44,0x08,
        0x81,0xE3,0x0B,
        0x41,0x11,0x0A,
        0xA1,0x08,0x09,
        0xA1,0x84,0x08,
        0x91,0x43,0x08,
        0xE9,0x40,0x08,
        0x05,0x20,0x08,
        0xFD,0x3F,0x08,
        0x01,0x00,0x08,
        0x01,0x00,0x08,
        0x03,0x00,0x0C,
        0xFE,0xFF,0x07};

int main(void) {
    // Init hardware & drivers
    LCD::lcd_init(LCD_GRAPHIC);


    while(1) {
        LCD::lcd_clear(); // Clear LCD
        ui::Button KBTB(2,2,155,10,"Keyboard & Textbox");
        ui::Button CHKLBL(2,18,155,10,"Checkbox & Label");
        ui::Button SLIDBAR(2,34,155,10,"Slider & Progress");
        ui::Button IBTN(2,50,155,10,"Imagebutton");
        LCD::lcd_plot_text(12,68,"Made by C_Classic",8,8,fonts::font_8x8);
        while (!KBTB.pressed() && !CHKLBL.pressed() && !SLIDBAR.pressed() && !IBTN.pressed());
            if (KBTB.pressed()) Ex_KeyboardTextBox(); //Keyboard-Example
            if (CHKLBL.pressed()) Ex_CheckboxLabel(); //Checkbox-Example
            if (SLIDBAR.pressed()) Ex_SliderProgress(); //Checkbox-Example
            if (IBTN.pressed()) Ex_Image(); //Checkbox-Example
    }
}

void Ex_Image() {
    LCD::lcd_clear(); //Clear menu
    ui::Button Btn_ret(107,2,50,8,"Return"); //Create button to return to the main-menu

    ui::PictureButton pic(50,30,20,20,icon); //Create the button with the image "icon"
    ui::Label lbl(0,0,"0"); //Create Label to display something

    int cntr=0;
    while (!Btn_ret.pressed()) { //mainloop (while return is not pressed)
        if (pic.pressed()) { //Check whether the button is pressed
            cntr++; //increase counter
            lbl.setNum(cntr); //Write value to label
            while (touchscreen::touch_is_pressed()); //Wait until the stylus is released.
        }
    }
}

void Ex_SliderProgress() {
    //NOTE: To invert sliders simply use: 100 - slider.getValue()

    LCD::lcd_clear(); //Clear menu
    ui::Button Btn_ret(107,2,50,8,"Return"); //Create button to return to the main-menu

    ui::HorizontalSlider hslider(0,20,159); //Create the horizontal slider
    ui::VerticalSlider vslider(149,28,50); //Create the vertical slider
    ui::Progressbar prg(10,50,130,20); // Create the progressbar

    char oldh,oldv=0;
    while (!Btn_ret.pressed()) { //mainloop (while return is not pressed)
        hslider.refresh();//Refresh Sliders
        vslider.refresh();
        if (hslider.getValue() != oldh) { //If slider moved...
            prg.setValue(hslider.getValue()); //Set the value of the slider to the progressbar (0->100)
            oldh=hslider.getValue();
        }
        else if (vslider.getValue() != oldv) { //Same thing for the other slider
            prg.setValue(vslider.getValue());
            oldv=vslider.getValue();
        }
    }
}

void Ex_CheckboxLabel() {
    LCD::lcd_clear(); //Clear menu
    ui::Button Btn_ret(107,2,50,8,"Return"); //Create button to return to the main-menu

    ui::CheckBox chk(10,60,"I am a |\\|32|]",0); //Create unchecked checkbox
    ui::Label lbl(0,20,"Aren't you a freak?"); //Create label with default text

    char oldstat=0;
    while (touchscreen::touch_is_pressed()); //Wait for Stylus to leave screen
    while (!Btn_ret.pressed()) { //mainloop (while return is not pressed)
        chk.refresh();
        if (oldstat != chk.checked) { //Check whether the value changed
            if (chk.checked) { //If it's checked ...
                lbl.setNum(1337); //Just to demostrate how to print a number
            }
            else {
                lbl.setText("Shure?"); //Set a new text.
            }
            oldstat = chk.checked; //Refresh variable
        }
    }
}

void Ex_KeyboardTextBox() {
    LCD::lcd_clear(); //Clear menu
    ui::Button Btn_ret(107,2,50,8,"Return"); //Create button to return to the main-menu

    ui::Textbox tb1(0,0,10,"",true); // Create textbox and set focus (Max 10 chars)
    ui::Textbox tb2(0,12,10,"",false); //Create second textbox with no focus (Max 10 chars)

    ui::Button clear(107,15,50,8,"Clear"); //Create button to clear the selected box
    ui::Keyboard kbd(30); //Create keyboard with a offset of 30 (will appear at the bottom)

    uint8_t focus=0; //Variable to save which textbox is selected

    while (touchscreen::touch_is_pressed()); //Wait for Stylus to leave screen
    while (!Btn_ret.pressed()) { //mainloop
        char temp = kbd.getKey(); //Get char from keyboard

        if (tb1.pressed()) { //Check whether textbox 1 is pressed
            focus=0; //Set box 1 (index 0) as selected box
            tb1.refresh(true); //Enable underscore at textbox 1
            tb2.refresh(false); //Disable at second
        }
        else if (tb2.pressed()) { //Now the same thing for the other box
            focus=1; //Set focus-index to 1
            tb1.refresh(false); // Disable underscore at the first box
            tb2.refresh(true); //Enable at second
        }
        if (temp == 8) { //If backspace (ASCII 8) was pressed
            if (focus == 0) tb1.backspace(); // If tb1 is selected delete the last character
            else if (focus == 1) tb2.backspace(); // Otherwise delete the char at the second box
            _delay_ms(100); //Wait a little while to delay keypresses
        }

        if (temp >= 32) { //alll below 32 are just codes and no chars
            char text[2]="-";  //Just write something to the variable - this will add the terminating 0 character
            text[0] = temp; //Now replace Byte 0(-) with the Char we got from the keyboard
            if (focus == 0) { //Check which textbox is selected
                strcat(tb1.text,text); //And append the text
                tb1.refresh(); //Refresh that the user can see the new text.
            }
            else if (focus == 1) { //Same thing again
                strcat(tb2.text,text);
                tb2.refresh();
            }
            _delay_ms(100); //Wait a bit
        }
        if (clear.pressed()) { //Check whether the clear-button was pressed and...
            if (focus == 0) tb1.setText(""); // ... clear the selected textbox
            else if (focus == 1) tb2.setText("");
        }
    }
}










