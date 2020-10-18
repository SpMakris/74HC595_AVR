/*
* output_register.h
*
* Created: 18/10/2020 2:26:34
* Author: Spiros
*/


#ifndef __OUTPUT_REGISTER_H__
#define __OUTPUT_REGISTER_H__
#include "output_register.h"
#include <stdint.h>
#include <avr/sfr_defs.h>
class output_register
{
	//variables
	public:
	protected:
	private:
	
	// Port adresses and pin numbers corresponding to Latch, Clock and Data outputs
	volatile uint8_t *PORT_LATCH;
	volatile uint8_t *PORT_CLOCK;
	volatile uint8_t *PORT_DATA;
	volatile uint8_t pin_latch;
	volatile uint8_t pin_clock;
	volatile uint8_t pin_data;
	
	//Copy of the register's current contents
	uint8_t status;
	
	//functions
	public:
	output_register();
	output_register(volatile uint8_t *PORT_L, uint8_t pin_l, volatile uint8_t *PORT_C,uint8_t pin_c,
	volatile uint8_t *PORT_D, uint8_t pin_d)
	{
		PORT_LATCH = PORT_L;
		PORT_CLOCK = PORT_C;
		PORT_DATA = PORT_D;
		pin_latch = pin_l;
		pin_clock = pin_c;
		pin_data = pin_d;
		status=0;
		shift_out(0);
	}
	
	//returns the current contents of the register
	uint8_t get_status()
	{
		return status;
	}
	//Shift out a byte of data
	void shift_out(uint8_t message)
	{
		write_latch(0);
		write_data(0);
		write_clock(0);
		for(int i=7;i>=0;i--)
		{
			write_data((message>>i)&1);
			write_clock(1);
			write_clock(0);
		}
		write_latch(1);
		write_latch(0);
		status = message;
	}
	//Write bit value to latch pin
	void write_latch(uint8_t bit)
	{
		if(bit)
		{
			*PORT_LATCH |=_BV(pin_latch);
		}
		else
		{
			*PORT_LATCH&=_BV(pin_latch);
		}
	}
	//Write bit value to clock pin
	void write_clock(uint8_t bit)
	{
		if(bit)
		{
			*PORT_CLOCK|=_BV(pin_clock);
		}
		else
		{
			*PORT_CLOCK&=_BV(pin_clock);
		}
	}
	//Write bit value to data pin
	void write_data(uint8_t bit)
	{
		if(bit)
		{
			*PORT_DATA|=_BV(pin_data);
		}
		else
		{
			*PORT_DATA&=_BV(pin_data);
		}
	}
	~output_register();
	protected:
	private:

	
	output_register( const output_register &c );
	output_register& operator=( const output_register &c );

}; //output_register

#endif //__OUTPUT_REGISTER_H__
