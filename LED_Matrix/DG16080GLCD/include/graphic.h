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
Version: 18.12.2010
*/

#ifndef GRAPHIC_H_
#define GRAPHIC_H_ GRAPHIC_H_ 	//!< protects this file from beeing double included

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <avr/pgmspace.h>


namespace ui {
	//DEFINES
	#define CHECKED 1 //Checkbox
	#define UNCHECKED 0 //Checkbox

    class Button {
	private:
		char x;
		char y;
		char width;
		char height;
	public:
		explicit Button(uint8_t bx, uint8_t by, uint8_t bwidth, uint8_t bheight, char *text);
                void Draw(char *text);
		char pressed();
		void remove();
    };

    class PictureButton {
    private:
            char x;
            char y;
            char width;
            char height;
    public:
            explicit PictureButton(uint8_t bx, uint8_t by, uint8_t bwidth, uint8_t bheight, const char *bitmap); //WARNUNG_ GRAFIK WIRD IN RAM KOPIERT
            char pressed();
            void Draw(const char *bitmap);
            void remove();
    };

    class CheckBox {
	private:
		char x;
		char y;
		char width;
	public:
		char checked;
                void Draw(char *text);
                explicit CheckBox(uint8_t bx, uint8_t by, char *text, uint8_t check);
		void set(char state);
		void refresh(); //MUST BE CALLED IN MAINLOOP!
		void remove();
    };

    class Label {
        private:
            char x;
            char y;
            char width;
        public:
            explicit Label(uint8_t bx, uint8_t by, char *text);
            void setText(char *text);
            void setNum(int num);
            void remove();
    };

    class VerticalSlider {
        private:
            char x;
            char y;
            char Max;
            char Value;
            void setVal(uint8_t value);

        public:
            explicit VerticalSlider(uint8_t bx, uint8_t by, uint8_t height);
            void set(uint8_t value);
            void Draw();
            void refresh();
            char getValue();
    };

    class HorizontalSlider {
        private:
            char x;
            char y;
            char Max;
            char Value;
            void setVal(uint8_t value);

        public:
            explicit HorizontalSlider(uint8_t bx, uint8_t by, uint8_t width);
            void set(uint8_t value);
            void Draw();
            void refresh();
            char getValue();
    };

    class Progressbar {
        private:
            char x;
            char y;
            char width;
            char height;
            char Value;
            char OldValue;
            void setRaw(uint8_t value);
        public:
            void Draw();
            explicit Progressbar(uint8_t bx, uint8_t by, uint8_t width, uint8_t height);
            void setValue(uint8_t value);
            char getValue();
    };

    class Textbox {
        private:
            char x;
            char y;
            char width;
            char max;
        public:
            char text[20];
            void Draw();
            explicit Textbox(uint8_t bx, uint8_t by, uint8_t maxchar, char *text, char selected);
            void setText(char *ntext);
            void setText(char *ntext, char underscore);
            char getValue();
            char isFull();
            char pressed();
            void refresh();
            void refresh(char underscore);
            void appendText(char *ntext);
            void backspace();
    };

    //NUMFIELD NOT FINISHED
    class Numfield {
        private:
            char x;
            char y;
            char size;
        public:
            void Draw();
            explicit Numfield(uint8_t bx, uint8_t by, uint8_t size);
            char getPressed();
    };

    class Keyboard {
        private:
            char offset;
            char getRow(uint8_t ty);
            char getCol(uint8_t tx);
        public:
            char status; //0=nor; 1=shift;
            explicit Keyboard();
            explicit Keyboard(uint8_t offset_x);
            char getKey(); //Returns the key as an ASCII-character
            void Draw(); //Redraws the Keyboard
    };
}

namespace DrawFunctions {
    void DrawFilledSquare(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t PixelState);
    void DrawSquare(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t PixelState);
    void DrawHorizontalLine(uint8_t x1, uint8_t x2, uint8_t y, uint8_t PixelState);
    void DrawVerticalLine(uint8_t y1, uint8_t y2, uint8_t x, uint8_t PixelState);
    void DrawCircle(int x0, int y0, int radius, uint8_t PixelState);
    void line(int xstart,int ystart,int xend,int yend, uint8_t PixelState);
}
#endif

