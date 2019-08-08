/*
 * Sensors.c
 *
 *
 *  Author: Smart Home Project
 */ 


#define F_CPU 1000000U
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "IncFile1.h"

#define Flame_inpit PB0
#define PIR_input   PB1
#define Green_LED PB2 
#define Red_LED PB2 
#define Buzzer PB4
#define Simulation_light PB5 

int main(){
	
	 //---- Flame sensor initialization ----//
	 
	DDRB &= (~(1<<PB0)); 


  //---- motion sensor initialization ----//

	DDRB &= (~(1<<PB1)); 


//---- LEDs and Buzzer initialization ----//

     DDRB |= (1<<PB2); 
	 DDRB |= (1<<PB3);
	 DDRB |= (1<<PB4); 
	 DDRB |= (1<<PB5); 
	 
//---- all outputs off ----//

	 PORTB &= (~(1<<Green_LED));
	 PORTB &= (~(1<<Red_LED));
     PORTB &= (~(1<<Buzzer));
	 PORTB &= (~(1<<Simulation_light));
	 
//---- ultrasonic initialization ----//
	int distance_in_cm1=0;
	int distance_in_cm2=0;

	
// initialize display, cursor off, human existence 
	int y;
	int Human_exist=0; 
	int Counter_flag=0;

	while(1)
	{   
/*-------------------------------------Ultra sonic sensor ----------------------------------*/
//------------------------------------------------------------------------------------------//

		 y=1;
		distance_in_cm1=read_sonar(y);
		_delay_ms(100);
		
		y=2;
	   distance_in_cm2=read_sonar(y);
	   _delay_ms(100);
	

if(distance_in_cm1<50)
{
		_delay_ms(200);
		
		 y=1;
		 distance_in_cm1=read_sonar(y);
		 _delay_ms(100);
		  y=2;
		 distance_in_cm2=read_sonar(y);
		 _delay_ms(100);
	if (distance_in_cm2<50)
{	
	
	TRIG1_PORT |=(1<<op_distance1);
		}
}

 distance_in_cm1=0;
 distance_in_cm2=0;

 _delay_ms(200);

	 y=1;
	 distance_in_cm1=read_sonar(y);
	 	 _delay_ms(100);
	 y=2;
	 distance_in_cm2=read_sonar(y);
	 _delay_ms(100);

	 if(distance_in_cm2<50)
{ 
	_delay_ms(200);
	
	 y=1;
	 distance_in_cm1=read_sonar(y);
	 _delay_ms(100);
	  y=2;
	 distance_in_cm2=read_sonar(y);
	 _delay_ms(100);
	if(distance_in_cm1<50)
	{
		
		TRIG2_PORT |=(1<<op_distance2);
		Counter_flag = op_distance2 ;
			
		}
	}
/*-------------------------------------motion sensor ----------------------------------*/
//------------------------------------------------------------------------------------//

if(PINB & (1<<PIR_input) )        //there is human
{
	PORTB |= (1<<Green_LED);
	Human_exist = 1 ;
	
}
else
{
	PORTB |= (1<<Red_LED);
	Human_exist = 0 ;
}

/*-------------------------------------condition to turn on light ----------------------------------*/
//--------------------------------------------------------------------------------------------------//

	if(!(Counter_flag && Human_exist) == 0 ) // both ultra sonics and motion sensor tell there is human
		{
			PORTB |= (1<<Simulation_light);
			
		}
	else if((Counter_flag == 0) && (Human_exist == 1)) //  ultra sonics says no one and motion sensor tell there is human
		{
			PORTB |= (1<<Simulation_light);
		}
	else if((Counter_flag && Human_exist) == 0) // both ultra sonics and motion sensor tell there is NO human
		{
			PORTB &= (~(1<<Simulation_light));
		}

/*-------------------------------------flame sensor ----------------------------------*/
//------------------------------------------------------------------------------------//
	
	
	if(PINB & (1<<Flame_inpit) )        //no fire
	{
		PORTB &= (~(1<<Buzzer));   //turn off buzzer
		
	}
	else
	{
		PORTB |= (1<<Buzzer);    //turn on buzzer
		
	}
	
	
	}
	
	return 0;
}
