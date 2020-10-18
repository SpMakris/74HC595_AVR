#include <avr/io.h>
#include <output_register.h>

//Create an instance of the class and pass the adresses for the required port-pin combination (Latch, Clock, Data)
//Here: Latch=PC1, Clock=PC2, Data=PE2
output_register test(&PORTC, 1, &PORTC, 2, &PORTE, 2);

int main(void)
{
	configure_IO();
	
	/* Replace with your application code */
	while (1)
	{
	
	//call the shift_out method to send a byte at the register and load it on the output lines
		test.shift_out(0b11110000);
	}
}

