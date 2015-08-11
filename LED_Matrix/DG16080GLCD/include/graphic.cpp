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

#include "graphic.h"
#include "lcd.h"
#include "fonts.h"
#include "touch.h"

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <avr/pgmspace.h>

//Zeichnet eine Horizontale Linie
void DrawFunctions::DrawHorizontalLine(uint8_t x1, uint8_t x2, uint8_t y, uint8_t PixelState) {
    uint8_t x;
    for (x=x1; x<=x2; x++) {
            LCD::lcd_plot_pixel(x,y,PixelState);
    }

        /* //NEW METHOD (NOT WORKING!)

        uint8_t outval;

        x=8;
        while (x1 > x) {
            x+=8;
        }
        outval=x- x1;

        uint8_t temp;

        temp = LCD::lcd_read_byte((y*20 + x/8 - 1)); //anfangs-speicherzelle lesen
        for (uint8_t xt=8; xt >= 9-outval;xt--) {
            temp |= (1<<(xt-1)); //outval px von rechts schwarz einfärben.
        }
        LCD::lcd_write_byte((y*20 + x/8 - 1),temp); //Speicherzelle wieder schrieben.


        x=152;
        while (x > x2) {
            x-=8;
        }
        outval=x2-x;

        temp = LCD::lcd_read_byte((y*20 + x/8 - 1)); //end-speicherzelle lesen
        for (uint8_t xt=8; xt >= 8-outval;xt--) {
            temp |= (1<<(xt-1)); //outval px von rechts schwarz einfärben.
        }
        LCD::lcd_write_byte((y*20 + x/8 - 1),temp); //Speicherzelle wieder schrieben.*/



}

//Zeichnet eine vertikale Linie
void DrawFunctions::DrawVerticalLine(uint8_t y1, uint8_t y2, uint8_t x, uint8_t PixelState) {
        uint8_t y;
        for (y=y1; y<=y2; y++) {
                LCD::lcd_plot_pixel(x,y,PixelState);
        }
}

// Zeichnet ein Ausgefülltes Rechteck.
void DrawFunctions::DrawFilledSquare(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t PixelState) {
uint8_t xtemp;
uint8_t ytemp;

        for (ytemp=y; ytemp <= y+height; ytemp++) {
                for (xtemp=x; xtemp <= x+width; xtemp++) {
                        LCD::lcd_plot_pixel(xtemp,ytemp,PixelState);
                }
        }
}

//Zeichnet ein nicht ausgefülltes Rechteck
void DrawFunctions::DrawSquare(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t PixelState) {
        DrawHorizontalLine(x,x+width,y,PIXEL_ON); //obere Linie
        DrawHorizontalLine(x,x+width,y+height,PIXEL_ON); //untere Linie
        DrawVerticalLine(y+1,y+height-1,x,PIXEL_ON); //linke Linie
        DrawVerticalLine(y+1,y+height-1,x+width,PIXEL_ON); //rechte Linie
}

/* Taken from http://de.wikipedia.org/wiki/Bresenham-Algorithmus */
  void DrawFunctions::DrawCircle(int x0, int y0, int radius, uint8_t PixelState)
  {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    LCD::lcd_plot_pixel(x0, y0 + radius,PixelState);
    LCD::lcd_plot_pixel(x0, y0 - radius,PixelState);
    LCD::lcd_plot_pixel(x0 + radius, y0,PixelState);
    LCD::lcd_plot_pixel(x0 - radius, y0,PixelState);

    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;

      LCD::lcd_plot_pixel(x0 + x, y0 + y,PixelState);
      LCD::lcd_plot_pixel(x0 - x, y0 + y,PixelState);
      LCD::lcd_plot_pixel(x0 + x, y0 - y,PixelState);
      LCD::lcd_plot_pixel(x0 - x, y0 - y,PixelState);
      LCD::lcd_plot_pixel(x0 + y, y0 + x,PixelState);
      LCD::lcd_plot_pixel(x0 - y, y0 + x,PixelState);
      LCD::lcd_plot_pixel(x0 + y, y0 - x,PixelState);
      LCD::lcd_plot_pixel(x0 - y, y0 - x,PixelState);
    }
  }



/* Taken from http://de.wikipedia.org/wiki/Bresenham-Algorithmus */
/* [[Signum (Mathematik)|signum function]] */
int sgn(int x){
  return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

void DrawFunctions::line(int xstart,int ystart,int xend,int yend, uint8_t PixelState)
/*--------------------------------------------------------------
 * Bresenham-Algorithmus: Linien auf Rastergeräten zeichnen
 *
 * Eingabeparameter:
 *    int xstart, ystart        = Koordinaten des Startpunkts
 *    int xend, yend            = Koordinaten des Endpunkts
 *
 * Ausgabe:
 *    void DrawFunctions::SetPixel(int x, int y) setze ein Pixel in der Grafik
 *         (wird in dieser oder aehnlicher Form vorausgesetzt)
 *---------------------------------------------------------------
 */
{
    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

/* Entfernung in beiden Dimensionen berechnen */
   dx = xend - xstart;
   dy = yend - ystart;

/* Vorzeichen des Inkrements bestimmen */
   incx = sgn(dx);
   incy = sgn(dy);
   if(dx<0) dx = -dx;
   if(dy<0) dy = -dy;

/* feststellen, welche Entfernung größer ist */
   if (dx>dy)
   {
      /* x ist schnelle Richtung */
      pdx=incx; pdy=0;    /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dy;   el =dx;   /* Fehlerschritte schnell, langsam */
   } else
   {
      /* y ist schnelle Richtung */
      pdx=0;    pdy=incy; /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dx;   el =dy;   /* Fehlerschritte schnell, langsam */
   }

/* Initialisierungen vor Schleifenbeginn */
   x = xstart;
   y = ystart;
   err = el/2;
   LCD::lcd_plot_pixel(x,y,PixelState);

/* Pixel berechnen */
   for(t=0; t<el; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
   {
      /* Aktualisierung Fehlerterm */
      err -= es;
      if(err<0)
      {
          /* Fehlerterm wieder positiv (>=0) machen */
          err += el;
          /* Schritt in langsame Richtung, Diagonalschritt */
          x += ddx;
          y += ddy;
      } else
      {
          /* Schritt in schnelle Richtung, Parallelschritt */
          x += pdx;
          y += pdy;
      }
       LCD::lcd_plot_pixel(x,y,PixelState);
   }
} /* line() */

ui::Button::Button(uint8_t bx, uint8_t by, uint8_t bwidth, uint8_t bheight, char *text) {
    x=bx;
    y=by;
    width=bwidth;
    height=bheight;
    Draw(text);
}

void ui::Button::Draw(char *text) {
#define BUTTONS_USE_DOUBLED_LINES 1

#if (BUTTONS_USE_DOUBLED_LINES == 1)
        DrawFunctions::DrawSquare(x-2,y-2,width+4,height+4,PIXEL_ON);

        LCD::lcd_plot_pixel(x-1,y-1,PIXEL_ON);
        LCD::lcd_plot_pixel(x+1+width,y-1,PIXEL_ON);
        LCD::lcd_plot_pixel(x-1,y+1+height,PIXEL_ON);
        LCD::lcd_plot_pixel(x+1+width,y+1+height,PIXEL_ON);
#endif
        DrawFunctions::DrawSquare(x,y,width,height, PIXEL_ON);
        LCD::lcd_plot_text(x+width/2-((strlen(text)*8-1)/2),y+height/2-3,text,8,8,fonts::font_8x8); // Text Vertikal und Horizontal zentriert ausgeben
}

char ui::Button::pressed() {
    if (!touchscreen::touch_is_pressed()) {
                    return 0;
            }
    int tx = touchscreen::touch_readX();
            int ty = touchscreen::touch_readY();

            if (tx >= x && tx <= (x+width)) {
                    if (ty >= y && ty <= (y+height)) {
                            return true;
                    }
            }
            return false;
}

void ui::Button::remove() { //Maybe with errors! (Removing not enought)
    DrawFunctions::DrawFilledSquare(x,y,width,height,PIXEL_OFF);
}

//CHECKBOX
ui::CheckBox::CheckBox(uint8_t bx, uint8_t by, char *text, uint8_t check) {
    x=bx;
    y=by;
    width= strlen(text) * 9-1 + 13;
    checked = check;
    Draw(text);
    if (checked == CHECKED) {
            set(CHECKED);
    }
}

void ui::CheckBox::Draw(char *text) {
    DrawFunctions::DrawHorizontalLine(x,x+10,y,PIXEL_ON);
    DrawFunctions::DrawHorizontalLine(x,x+10,y+9,PIXEL_ON);
    DrawFunctions::DrawVerticalLine(y+1,y+8,x,PIXEL_ON);
    DrawFunctions::DrawVerticalLine(y+1,y+8,x+10,PIXEL_ON);
    LCD::lcd_plot_text(x+13,y+1,text,8,8,fonts::font_8x8);
    if (checked) set(checked);
}

void ui::CheckBox::set(char state) {
    uint8_t lx;
    for (lx = 1; lx <= 8; lx++) {
        LCD::lcd_plot_pixel(lx + x,lx + y,state);
        LCD::lcd_plot_pixel(9 + x - lx,lx + y,state);
    }
   checked = state;
}

void ui::CheckBox::refresh() {
    uint16_t tx,ty;
            if (!touchscreen::touch_is_pressed()) {
                    return;
            }
            tx = touchscreen::touch_readX();
            ty = touchscreen::touch_readY();

            if (tx >= x && tx <= (x+width)) {
                    if (ty >= y && ty <= (y+10)) {
                            if (checked == CHECKED) {
                                    set(UNCHECKED);
                            }
                            else {
                                    set(CHECKED);
                            }
                            while(touchscreen::touch_is_pressed());
                    }
            }
}

void ui::CheckBox::remove() {
    DrawFunctions::DrawFilledSquare(x,y,width,10,PIXEL_OFF);
}


ui::Label::Label(uint8_t bx, uint8_t by, char *text) {
    x=bx;
    y=by;
    width=0;
    setText(text);
}

void ui::Label::setText(char *text) {
    DrawFunctions::DrawFilledSquare(x,y,width,8,PIXEL_OFF);
    width = strlen(text) * 8-1 + 3; //3 evtl. verändern.
    LCD::lcd_plot_text(x,y,text,8,8,fonts::font_8x8);
}

void ui::Label::setNum(int num) {
    char buffer[10];
    snprintf (buffer, (size_t)255, "%d ", num);
    setText(buffer);
}

void ui::Label::remove() {
    DrawFunctions::DrawFilledSquare(x,y,width,8,PIXEL_OFF);
}

//SLIDER

ui::VerticalSlider::VerticalSlider(uint8_t bx, uint8_t by, uint8_t height) {
    x = bx;
    y = by;
    Max = height;
    Value = 1;
    Draw();
}

void ui::VerticalSlider::Draw() {
        uint8_t val;
    for (val=y;val <= Max+y; val++) {
        LCD::lcd_plot_pixel(x + 4,val,PIXEL_ON);
    }
    setVal(0);
}

void ui::VerticalSlider::setVal(uint8_t value) {
    if (value != Value) {
                    LCD::lcd_plot_pixel(x+1,y + Value-1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+2,y + Value-1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+3,y + Value-1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+5,y + Value-1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+6,y + Value-1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+7,y + Value-1,PIXEL_OFF);

                    LCD::lcd_plot_pixel(x+1,y + Value+1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+2,y + Value+1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+3,y + Value+1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+5,y + Value+1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+6,y + Value+1,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+7,y + Value+1,PIXEL_OFF);

                    LCD::lcd_plot_pixel(x,y+Value,PIXEL_OFF);
                    LCD::lcd_plot_pixel(x+8,y+Value,PIXEL_OFF);


                    LCD::lcd_plot_pixel(x+1,y + value-1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+2,y + value-1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+3,y + value-1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+5,y + value-1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+6,y + value-1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+7,y + value-1,PIXEL_ON);

                    LCD::lcd_plot_pixel(x+1,y + value+1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+2,y + value+1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+3,y + value+1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+5,y + value+1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+6,y + value+1,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+7,y + value+1,PIXEL_ON);

                    LCD::lcd_plot_pixel(x,y + value,PIXEL_ON);
                    LCD::lcd_plot_pixel(x+8,y + value,PIXEL_ON);
                                    //ClearSquare(10,10,16,35);
                                    //PWert=val/80;
                                    //PWert=PWert*100;
                                    //snprintf (buffer, (size_t)255, "%d", PWert);
                                    //LCD::lcd_plot_text(10,10,buffer,16,16,font_12x16);
                    Value=value;
            }
}

void ui::VerticalSlider::set(uint8_t value) {
    float temp;
    float percentage;
    temp = Max;
    percentage = value;
    temp = temp * percentage/100;
    setVal(temp);
}

void ui::VerticalSlider::refresh() {
    uint16_t tx,ty;
    tx = touchscreen::touch_readX();
    ty = touchscreen::touch_readY();
    if(touchscreen::touch_is_pressed()) {
            if (tx >= x && tx <= x+8 && ty <= y+Max && ty >= y) {
                    setVal(ty - y);
            }
    }
}

char ui::VerticalSlider::getValue() {
    float temp;
    float Maxi;
    temp = Value;
    Maxi = Max;
    temp = temp/Maxi;
    temp = temp * 100;
    return (temp);
}

//SLIDER

ui::HorizontalSlider::HorizontalSlider(uint8_t bx, uint8_t by, uint8_t width) {
    x = bx;
    y = by;
    Max = width;
    Value = 1;
    Draw();
}

void ui::HorizontalSlider::Draw() {
    uint8_t val;
    DrawFunctions::DrawHorizontalLine(x,x+Max+1,y,PIXEL_ON);
    setVal(0);
}

void ui::HorizontalSlider::setVal(uint8_t value) {
    if (value != Value) {
        DrawFunctions::DrawVerticalLine(y-2,y-1,x+Value-1,PIXEL_OFF);
        DrawFunctions::DrawVerticalLine(y+1,y+2,x+Value-1,PIXEL_OFF);
        DrawFunctions::DrawVerticalLine(y-2,y-1,x+Value+1,PIXEL_OFF);
        DrawFunctions::DrawVerticalLine(y+1,y+2,x+Value+1,PIXEL_OFF);
        LCD::lcd_plot_pixel(x+Value,y-3,PIXEL_OFF);
        LCD::lcd_plot_pixel(x+Value,y+3,PIXEL_OFF);
        Value=value;

        DrawFunctions::DrawVerticalLine(y-2,y-1,x+value-1,PIXEL_ON);
        DrawFunctions::DrawVerticalLine(y+1,y+2,x+value-1,PIXEL_ON);
        DrawFunctions::DrawVerticalLine(y-2,y-1,x+value+1,PIXEL_ON);
        DrawFunctions::DrawVerticalLine(y+1,y+2,x+value+1,PIXEL_ON);
        LCD::lcd_plot_pixel(x+value,y-3,PIXEL_ON);
        LCD::lcd_plot_pixel(x+value,y+3,PIXEL_ON);
    }
}

void ui::HorizontalSlider::set(uint8_t value) {
    float temp;
    float percentage;
    temp = Max;
    percentage = value;
    temp = temp * percentage/100;
    setVal(temp);
}

void ui::HorizontalSlider::refresh() {
    uint16_t tx,ty;
    tx = touchscreen::touch_readX();
    ty = touchscreen::touch_readY();
    if(touchscreen::touch_is_pressed()) {
            if (tx >= x && tx <= x+Max && ty >= y-3 && ty <= y + 3) {
                    setVal(tx - x);
            }
    }
}

char ui::HorizontalSlider::getValue() {
    float temp;
    float Maxi;
    temp = Value;
    Maxi = Max;
    temp = temp/Maxi;
    temp = temp * 100;
    return (temp);
}


ui::Progressbar::Progressbar(uint8_t bx, uint8_t by, uint8_t bwidth, uint8_t bheight) {
    x=bx;
    y=by;
    width=bwidth;
    height=bheight;
    Value=0;
    OldValue=0;

    Draw();
}

void ui::Progressbar::Draw() {
    DrawFunctions::DrawSquare(x,y, width, height, PIXEL_ON); //Draw frame (0%)
}

void ui::Progressbar::setRaw(uint8_t value) {
    if (value != Value) {
                    if (value > Value) {
                            // Mehr schwarz
                        DrawFunctions::DrawFilledSquare (x + 2 + Value, y + 2, value - Value, height - 4, PIXEL_ON);
                    }
                    else {
                            // Weniger schwarz
                        DrawFunctions::DrawFilledSquare (x + 2 + value, y + 2, Value - value, height - 4, PIXEL_OFF);
                    }
                    Value=value;
            }
}

void ui::Progressbar::setValue(uint8_t value) {
    float temp;
    float percentage;
    temp = width - 4; //-4 weil rechts und links 1px Abstand ist (und  natürlich der Strich nicht gezählt werden darf)
    percentage = value;
    temp = temp * percentage/100;
    setRaw(temp);
}

char ui::Progressbar::getValue() {
    float temp;
    float Max;
    temp = Value;
    Max = width - 4;
    temp = temp/Max;
    temp = temp * 100;
    return (temp);
}

ui::PictureButton::PictureButton(uint8_t bx, uint8_t by, uint8_t bwidth, uint8_t bheight, PGM_P bitmap) {
    x=bx;
    y=by;
    width=bwidth;
    height=bheight;
    Draw(bitmap);
}

void ui::PictureButton::Draw(PGM_P bitmap) {
     LCD::lcd_plot_bitmap(x,y,bitmap,height,width);
}

void ui::PictureButton::remove() {
    DrawFunctions::DrawFilledSquare(x,y,width,height,PIXEL_OFF);
}

char ui::PictureButton::pressed() {
    if (!touchscreen::touch_is_pressed()) {
                    return 0;
            }
    int tx = touchscreen::touch_readX();
            int ty = touchscreen::touch_readY();

            if (tx >= x && tx <= (x+width)) {
                    if (ty >= y && ty <= (y+height)) {
                            return true;
                    }
            }
            return false;
}

ui::Textbox::Textbox(uint8_t bx, uint8_t by, uint8_t maxchar, char *ntext, char selected) {

    x=bx;
    y=by;
    max = maxchar-1;
    width=0;
        DrawFunctions::DrawSquare(x,y,max * 9-1 + 3,10,PIXEL_ON);
    setText(ntext,selected);
}

void ui::Textbox::setText(char *ntext) {
    setText(ntext,true);
}

void ui::Textbox::refresh() {
    setText(text);
}
void ui::Textbox::refresh(char underscore) {
    setText(text, underscore);
}

void ui::Textbox::backspace() {
    if (strlen(text) > 0) {
        text[strlen(text) - 1] = 0;
    }
    refresh();
}

void ui::Textbox::setText(char *ntext, char underscore) {
    if (!isFull() || (strlen(ntext) * 9-1 + 3) <= width) { //Wenn der neue text kürzer ist als der alte ODER die Box nicht voll ist
        strcpy(text,ntext); // Neuen Text speichern

        if (isFull()) DrawFunctions::DrawFilledSquare(x+2,y+2,width-6,7,PIXEL_OFF); //alten Text löschen
        else DrawFunctions::DrawFilledSquare(x+2,y+2,width+1,7,PIXEL_OFF); //alten txt + _ löschen

        width = (strlen(ntext) * 8) +6; //2 evtl. verändern.
        if (!isFull() && underscore) { // wenn noch ein zeichen Platz hat und underscore an ist...
            strcat(text,"_"); //... einen _ ans Ende
        }


        LCD::lcd_plot_text(x+2,y+2,text,8,8,fonts::font_8x8); // Neuen text schreiben

        if (!isFull() && underscore && strlen(text) > 0) { //wenn überhaupt n text drinsteht
            text[(strlen(text)-1)] = 0; //den _ wieder löschen
        }
    }
    else { //wenn box voll
        //hardware::PlaySound(70,100); //DEBUG_FLAG

        if (strcmp(ntext,text) != 0) { //wenn input != output
            strcpy(ntext,text); // alten string zurückgeben --> inputVariable zurücksetzen
        }
        else { //wenn direkt in variable geschrieben wurde könnte der string zu lang sein
            while (strlen(text) * 8 > max*9+3 && strlen(text)>0) { //So lange im Kreis rennen und ...
                text[strlen(text) - 1] = 0; //... das hintere Zeichen entfernen ...
            } // ... bis die länge OK ist.
    }
}
}

void ui::Textbox::appendText(char *ntext) {
    strcat(text,ntext);
    refresh();
}

char ui::Textbox::isFull() {
    if (width < max*9+3) {
        return false;
    }
    return true;
}

char ui::Textbox::pressed() {
    if (!touchscreen::touch_is_pressed()) {
                    return 0;
            }
    int tx = touchscreen::touch_readX();
            int ty = touchscreen::touch_readY();

            if (tx >= x && tx <= (x+(max*9+3))) {
                    if (ty >= y && ty <= (y+10)) {
                            return true;
                    }
            }
            return false;
}

ui::Numfield::Numfield(uint8_t bx, uint8_t by, uint8_t size) {

}


ui::Keyboard::Keyboard() { //DOES NOT WORK??!!
    offset=30;
        status=0;
    Draw();
}

ui::Keyboard::Keyboard(uint8_t offset_x) {
    offset=offset_x;
        status=0;
    Draw();
}

void ui::Keyboard::Draw() {
#define offsetX 3
    DrawFunctions::DrawFilledSquare(0,offset,160,50,PIXEL_OFF);

    if (status == 0) { //nor
        LCD::lcd_plot_text(offsetX,offset+2,"1 2 3 4 5 6 7 8 9 0",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+12,"q w e r t z u i o p",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+22,"a s d f g h j k l #",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+32,"y x c v b n m , . -",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+41,"Shift         bksp.",8,8,fonts::font_8x8);
    }
    else if (status == 1) { //shift
        LCD::lcd_plot_text(offsetX,offset+2,"! \" $ % & / ( ) = ?",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+12,"Q W E R T Z U I O P",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+22,"A S D F G H J K L *",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+32,"Y X C V B N M ; : _",8,8,fonts::font_8x8);
        LCD::lcd_plot_text(offsetX,offset+41,"Shift         bksp.",8,8,fonts::font_8x8);
    }

    for (int x=0; x <= 50; x+=10) {
        DrawFunctions::DrawHorizontalLine(0,159,offset+x,PIXEL_ON);
    }
    DrawFunctions::DrawHorizontalLine(0,159,79,PIXEL_ON); //border b

    DrawFunctions::DrawVerticalLine(offset,offset+48,0,PIXEL_ON); //border l
    DrawFunctions::DrawVerticalLine(offset,offset+39,14,PIXEL_ON); //1

    for (int x=28; x <= 140; x+=16) {
        DrawFunctions::DrawVerticalLine(offset,offset+39,offsetX + x,PIXEL_ON);
    }
    DrawFunctions::DrawVerticalLine(offset,offset+49,159,PIXEL_ON); //border r

    DrawFunctions::DrawVerticalLine(offset+41,159,47,PIXEL_ON); //shift-->space border
    DrawFunctions::DrawVerticalLine(offset+41,159,111,PIXEL_ON); //space-->2nd border

    /*
    DrawFunctions::DrawVerticalLine(offset,offset+38,14,PIXEL_ON); //1
    DrawFunctions::DrawVerticalLine(offset,offset+38,28,PIXEL_ON); //2
    DrawFunctions::DrawVerticalLine(offset,offset+38,44,PIXEL_ON); //3
    DrawFunctions::DrawVerticalLine(offset,offset+38,60,PIXEL_ON); //4
    DrawFunctions::DrawVerticalLine(offset,offset+38,76,PIXEL_ON); //5
    DrawFunctions::DrawVerticalLine(offset,offset+38,92,PIXEL_ON); //6
    DrawFunctions::DrawVerticalLine(offset,offset+38,108,PIXEL_ON); //7
    DrawFunctions::DrawVerticalLine(offset,offset+38,124,PIXEL_ON); //8
    DrawFunctions::DrawVerticalLine(offset,offset+38,140,PIXEL_ON); //9
    DrawFunctions::DrawVerticalLine(offset,offset+38,156,PIXEL_ON); //0
*/

}

char ui::Keyboard::getKey() {
    if (!touchscreen::touch_is_pressed()) {
                    return 0;
    }

    //Touchscreen lesen
    int tx = touchscreen::touch_readX();
    int ty = touchscreen::touch_readY();

    if (ty <= offset) return 0; // kleiner als y-Offset--> keine taste

    char row = getRow(ty);
    char col = getCol(tx);

    if (row == 5 && col <=3) { //Shift
        status = !status;
        Draw();
        return 0;
    }

    char status_old = status;
    status = 0;
    if (status_old != 0) Draw();

    if (row == 5 && col >3 && col < 8) { //Space
           return 32;
       }

       if (row == 5 && col >= 8) { //bksp
           return 8; //bksp;
       }

       if (row==1 && status_old == 0) { //Zahlen
           char temp = col+48;
           if (temp >= 58) temp-=10;
           return temp;
       }
       if (row==1 && status_old == 1) { //zeichen
           if (col==1) return 33;
           if (col==2) return 34;
           if (col==3) return 36;
           if (col==4) return 37;
           if (col==5) return 38;
           if (col==6) return 47;
           if (col==7) return 40;
           if (col==8) return 41;
           if (col==9) return 61;
           if (col==10) return 63;
       }

       char outtemp;
       if (row==2) {
           if (col==1) outtemp=81; //Q
           if (col==2) outtemp=87; //W
           if (col==3) outtemp=69; //E
           if (col==4) outtemp=82; //R
           if (col==5) outtemp=84; //T
           if (col==6) outtemp=90; //Z
           if (col==7) outtemp=85; //U
           if (col==8) outtemp=73; //I
           if (col==9) outtemp=79; //O
           if (col==10) outtemp=80; //P

           if (status_old == 0) outtemp+=32; //kleine Zeichen 32 zeichen weiter hinten im ASCII-Code
           return outtemp;
       }

       if (row==3) {
           if (col==1) outtemp=65; //A
           if (col==2) outtemp=83; //S
           if (col==3) outtemp=68; //D
           if (col==4) outtemp=70; //F
           if (col==5) outtemp=71; //G
           if (col==6) outtemp=72; //H
           if (col==7) outtemp=74; //J
           if (col==8) outtemp=75; //K
           if (col==9) outtemp=76; //L

           if (status_old == 0) outtemp+=32; //kleine Zeichen 32 zeichen weiter hinten im ASCII-Code

           if (col==10 && status_old==0) outtemp=35; //#
           else if (col==10 && status_old==1) outtemp=42; //*

           return outtemp;
       }

       if (row==4) {
           if (col==1) outtemp=89; //Y
           if (col==2) outtemp=88; //X
           if (col==3) outtemp=67; //C
           if (col==4) outtemp=86; //V
           if (col==5) outtemp=66; //B
           if (col==6) outtemp=78; //N
           if (col==7) outtemp=79; //M

           if (status_old == 0) outtemp+=32; //kleine Zeichen 32 zeichen weiter hinten im ASCII-Code

           if (col==8 && status_old==0) outtemp=44; //,
           else if (col==10 && status_old==1) outtemp=59; //;

           if (col==9 && status_old==0) outtemp=46; //.
           else if (col==10 && status_old==1) outtemp=58; //:

           if (col==10 && status_old==0) outtemp=45; //-
           else if (col==10 && status_old==1) outtemp=95; //_

           return outtemp;
       }

       return 0;
   }

char ui::Keyboard::getRow(uint8_t ty) {
    for (int x=0; x <= 50; x+=10) {
        if (ty < x+offset) {
            return (x/10);
        }
    }
}

char ui::Keyboard::getCol(uint8_t tx) {
    char cc=1;
    if (tx < 14) {
        return cc;
    }
    for (int x=28; x <= 140; x+=16) {
        cc++;
        if (tx < x) {
            return cc;
        }
    }
    cc++;
    return cc;
}
