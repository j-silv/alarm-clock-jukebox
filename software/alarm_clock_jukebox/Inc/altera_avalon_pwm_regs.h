/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

#ifndef __ALTERA_AVALON_PWM_REGS_H__
#define __ALTERA_AVALON_PWM_REGS_H__

#include <io.h>

#define IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(base)       IORD(base, 0) 
#define IOWR_ALTERA_AVALON_PWM_CLOCK_DIVIDER(base, data) IOWR(base, 0, data)
#define ALTERA_AVALON_PWM_CLOCK_DIVIDER_MSK              (0xFFFFFFFF)
#define ALTERA_AVALON_PWM_CLOCK_DIVIDER_OFST             (0)

#define IORD_ALTERA_AVALON_PWM_DUTY_CYCLE(base)         IORD(base, 1) 
#define IOWR_ALTERA_AVALON_PWM_DUTY_CYCLE(base, data)   IOWR(base, 1, data)
#define ALTERA_AVALON_PWM_DUTY_CYCLE_MSK                (0xFFFFFFFF)
#define ALTERA_AVALON_PWM_DUTY_CYCLE_OFST               (0)

#define IORD_ALTERA_AVALON_PWM_ENABLE(base)             IORD(base, 2) 
#define IOWR_ALTERA_AVALON_PWM_ENABLE(base, data)       IOWR(base, 2, data)
#define ALTERA_AVALON_PWM_ENABLE_MSK                    (0x1)
#define ALTERA_AVALON_PWM_ENABLE_OFST                   (0)

#endif /* __ALTERA_AVALON_PWM_REGS_H__ */
