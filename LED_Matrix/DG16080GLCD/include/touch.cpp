/*
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in
compliance with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS"
basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
License for the specific language governing rights and limitations
under the License.

Author: Sebastian/C_Classic (cclassicvideos@aol.com)
  Date: 01.10.2010
*/

#include <avr/io.h>
#include <util/delay.h>

#include "touch.h"


int touchscreen::readADC(char channel) {
        uint16_t result;
        uint8_t i;

        //ADC aktiv, Prescaler 16
        ADCSRA = (1 << ADEN) | (1 << ADPS2);

        //ADC0 kein mutiplexing
        ADMUX = channel;

        // AVcc als Versorgungspannung
        ADMUX |= (1 << REFS0);

        //ADC starten mit Dummyreadout
        ADCSRA |= (1 << ADSC);
        while(ADCSRA & (1 << ADSC));

        result = 0;

        for(i = 0; i < ADC_READ_CYCELS; i++) {
                ADCSRA |= (1 << ADSC);
                while(ADCSRA & (1 << ADSC));
                result += ADCW / ADC_READ_CYCELS;
                _delay_us(1);
        }

        //ADC aus
        ADCSRA &= ~(1 << ADEN);


        return result;
}


/**
 * This functions set 5V to X1 and GND to Y1,
 * the voltage at X2 is measured via the ADC.
 * If the ADC-Value is less then TOUCH_PRESSED_LEVEL,
 * the function will return 1.
 * \return 1 if pressed else 0
 */
char touchscreen::touch_is_pressed() {
        TOUCH_DDR |= (1 << TOUCH_X1);
        TOUCH_DDR |= (1 << TOUCH_Y1);
        TOUCH_DDR &= ~(1 << TOUCH_X2);

        TOUCH_PORT &= ~(1 << TOUCH_Y1);
        TOUCH_PORT |= (1 << TOUCH_X1);

        if(readADC(TOUCH_X2) < TOUCH_PRESSED_LEVEL) {
                return 1;
        }
        else {
                return 0;
        }

}
/**
 *
 *
 */
int touchscreen::touch_readX() {
        int16_t pos;

        if(touch_is_pressed()) {

                TOUCH_DDR |= (1 << TOUCH_X1);
                TOUCH_DDR |= (1 << TOUCH_X2);
                TOUCH_DDR &= ~(1 << TOUCH_Y1);
                TOUCH_DDR &= ~(1 << TOUCH_Y2);

                TOUCH_PORT &= ~(1 << TOUCH_X1);
                TOUCH_PORT |= (1 << TOUCH_X2);

                _delay_us(10);

                pos = (readADC(TOUCH_Y1) - 263) * 16 / 53;


                return pos;


        }
        else  {
                return -1;
        }

}


int touchscreen::touch_readY() {
        int16_t pos;

        if(touch_is_pressed()) {

                TOUCH_DDR |= (1 << TOUCH_Y1);
                TOUCH_DDR |= (1 << TOUCH_Y2);
                TOUCH_DDR &= ~(1 << TOUCH_X1);
                TOUCH_DDR &= ~(1 << TOUCH_X2);

                TOUCH_PORT |= (1 << TOUCH_Y1);
                TOUCH_PORT &= ~(1 << TOUCH_Y2);

                _delay_us(10);

                pos = (readADC(TOUCH_X1) - 330) * 8 / 40;


                return pos;


        }
        else  {
                return -1;
        }

}
