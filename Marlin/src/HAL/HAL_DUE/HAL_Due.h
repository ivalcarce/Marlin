/* **************************************************************************
 
 Marlin 3D Printer Firmware
 Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

// **************************************************************************
//
// Description:          *** HAL for Arduino Due ***
//
// ARDUINO_ARCH_SAM
// **************************************************************************

#ifndef _HAL_DUE_H
#define _HAL_DUE_H

// --------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------

#include <stdint.h>

#include "Arduino.h"

#include "fastio_Due.h"
#include "watchdog_Due.h"



// --------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------

#define _BV(bit) 	(1 << (bit))

#define analogInputToDigitalPin(IO) IO

#define     CRITICAL_SECTION_START	uint32_t primask=__get_PRIMASK(); __disable_irq();
#define     CRITICAL_SECTION_END    if (primask==0) __enable_irq();

// On AVR this is in math.h?
#define square(x) ((x)*(x))

#define strncpy_P(dest, src, num) strncpy((dest), (src), (num))

// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

#define HAL_TIMER_TYPE unsigned long

// --------------------------------------------------------------------------
// Public Variables
// --------------------------------------------------------------------------

// reset reason set by bootloader
extern uint8_t MCUSR;

// --------------------------------------------------------------------------
// Public functions
// --------------------------------------------------------------------------

// Disable interrupts
void cli(void);

// Enable interrupts
void sei(void);

void _delay_ms(int delay);

int freeMemory(void);


void eeprom_write_byte(unsigned char *pos, unsigned char value);

unsigned char eeprom_read_byte(unsigned char *pos);
void eeprom_read_block (void *__dst, const void *__src, size_t __n);
void eeprom_update_block (const void *__src, void *__dst, size_t __n);



// timers
#define STEP_TIMER_NUM 3
#define TEMP_TIMER_NUM 4

#define HAL_TIMER_RATE 		     (F_CPU/32.0)
#define TICKS_PER_NANOSECOND   (HAL_TIMER_RATE)/1000

#define ENABLE_STEPPER_DRIVER_INTERRUPT()	HAL_timer_enable_interrupt (STEP_TIMER_NUM)
#define DISABLE_STEPPER_DRIVER_INTERRUPT()	HAL_timer_disable_interrupt (STEP_TIMER_NUM)

//
#define HAL_STEP_TIMER_ISR 	void TC3_Handler()
#define HAL_TEMP_TIMER_ISR 	void TC4_Handler()

void HAL_timer_start (uint8_t timer_num, uint32_t frequency);
void HAL_timer_set_count (uint8_t timer_num, uint32_t count);
HAL_TIMER_TYPE HAL_timer_get_count (uint8_t timer_num);

void HAL_timer_enable_interrupt (uint8_t timer_num);
void HAL_timer_disable_interrupt (uint8_t timer_num);

void HAL_timer_isr_prologue (uint8_t timer_num);
//

extern uint16_t HAL_adc_result;

void HAL_adc_start_conversion (uint8_t adc_pin);
uint16_t HAL_adc_get_result(void);


// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

#endif // _HAL_DUE_H
