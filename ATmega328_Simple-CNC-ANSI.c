/*
 * Simple CNC V.1.0 - 2 Axis control
 *  
 *   Licennce: CC-BY-SA
 */ 

#define F_CPU 16000000UL				// Define Clock Source 
#define __DELAY_BACKWARD_COMPATIBLE__	// Added to Fix delay.h bug 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Global Mode to set the mode Start = 0xff ,  Stop = 0x00
volatile uint8_t operationMode = 0x0;

// Global Variable to set the motor speed 
volatile uint8_t motorSpeedDelay;


//Functions Declaration 
void init_ADC();
void init_Interrupt0();
void init_Hbridge();
void y_axis_backward(uint8_t steps_yb);
void y_axis_forward(uint8_t steps_yf);
void x_axis_backward(uint8_t steps_xb);
void x_axis_forward(uint8_t steps_xf);
void shutDownHbridge();

// Main App
int main(void)
{
	init_Hbridge();		// Setup the X-Y motors
	init_Interrupt0();	// Setup INT0
	init_ADC();			// Setup ADC on channel 5
	sei();				// Enable All Interrupts
	
	while(1)
	{	
		while(operationMode == 0xff)
		{
			for(uint8_t i=1;i<=40;i=i+2)
			{
				x_axis_forward(i);
				y_axis_forward(i);
				x_axis_backward(i);
				y_axis_backward(i);
			}
	
		}
	
		
	}
}

ISR(INT0_vect)
{
	operationMode = ~ operationMode;
	
	// Invert the Operation Mode
}

ISR(ADC_vect)
{
	motorSpeedDelay = ADCH * 2;		// Set the delay value from 0 to 512 ms
	ADCSRA |= (1<<ADSC);			// Restart the ADC conversion
}

void init_Hbridge()
{
	DDRC |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);	// First  Motor control pins
	DDRB |= (1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);	// Second Motor control pins
}

void init_Interrupt0()
{	
	// Set the interrupt on the LOW level
	DDRD &= ~(1<<PD2);
	PORTD |= (1<< PD2);		//Enable Pull up for INT0 (PD2)
	EIMSK |= (1<<INT0);		//Enable INT0 interrupt
}

void init_ADC()
{
	// The ADC will capture the the potentiometer voltage to calculate the motor Speed
	// ADC will work in 8 bit Mode (left Adjusted)
	ADCSRA |= (1<<ADEN);							// Enable ADC
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); // Set ADC Clk to the slowest conversion rate
	ADMUX  |= (1<<MUX0) | (1<<MUX2);				// Choose channel 5 
	ADMUX  |= (1<<REFS0);							// Use AVCC as AREF
	ADMUX  |= (1<<ADLAR);							// 8 bit mode (left adjusted)
	ADCSRA |= (1<<ADIE);							// Enable ADC interrupter
	ADCSRA |= (1<<ADSC);							// Start the First conversion  
}


void x_axis_forward (uint8_t steps_xf)
{

	uint8_t  i ;

	for ( i=0 ; i <= steps_xf; i++ )
	{
		if(operationMode == 0) break;	  // This line used to stop the stepper immediately
		PORTC = 0b00000110 ;              // stepper motor rotation degree = 90
		_delay_ms(motorSpeedDelay);      //stop the motor for the value captured from the potentiometer (waiting time until the next step)
	
		if(operationMode == 0) break;
		PORTC = 0b00000101 ;              // stepper motor rotation degree =180
		_delay_ms(motorSpeedDelay);      //stop the motor for the value captured from the potentiometer (waiting time until the next step)

		if(operationMode == 0) break;
		PORTC = 0b00001001 ;              // stepper motor rotation degree =270
		_delay_ms(motorSpeedDelay);      //stop the motor for the value captured from the potentiometer (waiting time until the next step)

		if(operationMode == 0) break;
		PORTC = 0b00001010 ;              // stepper motor rotation degree =360
		_delay_ms(motorSpeedDelay);      //stop the motor for the value captured from the potentiometer (waiting time until the next step)
	}
}


void x_axis_backward (uint8_t steps_xb)
{
	
	uint8_t i ;
	for (i=0 ; i<= steps_xb ; i++)
	{
		if(operationMode == 0) break;
		PORTC = 0b00001010 ;              // stepper motor rotation degree =90
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)

		if(operationMode == 0) break;
		PORTC = 0b00001001 ;              // stepper motor rotation degree =180
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTC = 0b00000101 ;              // stepper motor rotation degree =270
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)

		if(operationMode == 0) break;
		PORTC = 0b00000110 ;               // stepper motor rotation degree =360
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
	}
}



void y_axis_forward (uint8_t steps_yf)
{
	
	uint8_t i ;
	for  (i=0 ; i<= steps_yf ; i++)
	{
		if(operationMode == 0) break;
		PORTB = 0b00011000;              // stepper motor rotation degree =90
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTB = 0b00010100;              // stepper motor rotation degree =180
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTB = 0b00100100;              // stepper motor rotation degree =270
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTB = 0b00101000;              // stepper motor rotation degree =360
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
	}
}

void y_axis_backward (uint8_t steps_yb)
{
	
	uint8_t i;
	
	for (i=0 ; i<=steps_yb ; i++)
	{	
		if(operationMode == 0) break;
		PORTB = 0b00101000;              // stepper motor rotation degree =90
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTB = 0b00100100;                // stepper motor rotation degree =180
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTB = 0b00010100;              // stepper motor rotation degree =270
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
		
		if(operationMode == 0) break;
		PORTB = 0b00011000;              // stepper motor rotation degree =360
		_delay_ms(motorSpeedDelay) ;     //stop the motor for the value captured from the potentiometer (waiting time until the next step)
	
	}
}


void shutDownHbridge()
{
	PORTC &= ~((1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3));	// Shutdown stepper Motor 1 control pins
	PORTB &= ~((1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5));	// Shutdown stepper Motor 2 control pins
}
