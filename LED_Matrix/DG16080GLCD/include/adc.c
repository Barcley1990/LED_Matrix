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
  Date: 01.10.2010
*/

#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

int readADC(char channel) {
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
