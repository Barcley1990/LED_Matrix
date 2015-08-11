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

#ifndef TOUCH_H_
#define TOUCH_H_ TOUCH_H_ 	//!< protects this file from beeing double included

namespace touchscreen {
#include "adc.h"


#define TOUCH_PORT 	PORTA
#define TOUCH_PIN	PINA
#define TOUCH_DDR  	DDRA

#define TOUCH_X1 PA3
#define TOUCH_X2 PA2
#define TOUCH_Y1 PA1
#define TOUCH_Y2 PA0

#define TOUCH_PRESSED_LEVEL 1000

char touch_is_pressed(void);

int touch_readX(void);
int touch_readY(void);

}

#endif

