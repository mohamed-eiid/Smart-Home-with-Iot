/*
 * CFile1.c
 *
 * Created: 02/12/2017 18:40:35
 *  Author: nermeen-pc
 */ 

//------------------------------------------- Ultrasonic -------------------------------------------//
 
#include "IncFile1.h"
 
volatile uint32_t overFlowCounter = 0;
volatile uint32_t trig1_counter = 0;
volatile uint32_t trig2_counter = 0;
volatile uint32_t no_of_ticks1 = 0;
volatile uint32_t no_of_ticks2 = 0;
 
/********** ...- . . .-. --- -... --- - *********************************
 * Initiate Ultrasonic Module Ports and Pins
 * Input:   none
 * Returns: none
*********** ...- . . .-. --- -... --- - *********************************/
void init_sonar(){
    TRIG1_OUTPUT_MODE();     // Set Trigger pin as output
	TRIG2_OUTPUT_MODE(); 
    ECHO1_INPUT_MODE();      // Set Echo pin as input
	ECHO2_INPUT_MODE(); 
		TRIG1_DDR |= (1<<op_distance1 );
		TRIG2_DDR |= (1<<op_distance2);
		TRIG1_DDR |= (1<<op_error1D);
		TRIG2_DDR |= (1<<op_error1A);
		TRIG1_DDR |= (1<<op_error2D);
		TRIG2_DDR |= (1<<op_error2A);
	
}
 
/********** ...- . . .-. --- -... --- - *********************************
 * Send 10us pulse on Sonar Trigger pin
 * 1.   Clear trigger pin before sending a pulse
 * 2.   Send high pulse to trigger pin for 10us
 * 3.   Clear trigger pin to pull it trigger pin low
 *  Input:   none
 *  Returns: none
********** ...- . . .-. --- -... --- - *********************************/
int trigger_sonar1(){
    TRIG1_LOW();             // Clear pin before setting it high
    _delay_us(1);           // Clear to zero and give time for electronics to set
    TRIG1_HIGH();            // Set pin high
    _delay_us(12);          // Send high pulse for minimum 10us
    TRIG1_LOW();             // Clear pin
    _delay_us(1);           // Delay not required, but just in case...
	return ECHO1_PIN;
}

int trigger_sonar2(){
	TRIG2_LOW();             // Clear pin before setting it high
	_delay_us(1);           // Clear to zero and give time for electronics to set
	TRIG2_HIGH();            // Set pin high
	_delay_us(12);          // Send high pulse for minimum 10us
	TRIG2_LOW();             // Clear pin
	_delay_us(1);           // Delay not required, but just in case...
	
	return ECHO2_PIN;
}
 
/********** ...- . . .-. --- -... --- - *********************************
 * Increment timer on each overflow
 * Input:   none
 * Returns: none
********** ...- . . .-. --- -... --- - *********************************/
ISR(TIMER1_OVF_vect){   // Timer1 overflow interrupt
    overFlowCounter++;
    TCNT1=0;
}
 
/********** ...- . . .-. --- -... --- - *********************************
 * Calculate and store echo time and return distance
 * Input:   none
 * Returns: 1. -1       :   Indicates trigger error. Could not pull trigger high
 *          2. -2       :   Indicates echo error. No echo received within range
 *          3. Distance :   Sonar calculated distance in cm.
********** ...- . . .-. --- -... --- - *********************************/
unsigned int read_sonar(int x){
  
    init_sonar();                       // Setup pins and ports
    if (x==1)
	
	{       int dist_in_cm1 = 0;             // send a 10us high pulse
		int z=trigger_sonar1();  
 
    while(!(z & (1<<ECHO1_BIT))){   // while echo pin is still low
        trig1_counter++;
		z=trigger_sonar1();  
         uint32_t max_response_time = SONAR_TIMEOUT;
        if (trig1_counter > max_response_time){   // SONAR_TIMEOUT
            return TRIG1_ERROR;
        }
    }
 
    TCNT1=0;                            // reset timer
    TCCR1B |= (1<<CS10);              // start 16 bit timer with no prescaler
    TIMSK |= (1<<TOIE1);             // enable overflow interrupt on timer1
    overFlowCounter=0;                  // reset overflow counter
    sei();                              // enable global interrupts
 
    while((z & (1<<ECHO1_BIT))){ 
		z=trigger_sonar1();     // while echo pin is still high
        if (((overFlowCounter*TIMER_MAX)+TCNT1) > SONAR_TIMEOUT){
            return ECHO1_ERROR;          // No echo within sonar range
        }
    };
 
    TCCR1B = 0x00;                      // stop 16 bit timer with no prescaler
    cli();                              // disable global interrupts
    no_of_ticks1 = ((overFlowCounter*TIMER_MAX)+TCNT1);  // counter count
    dist_in_cm1 = (no_of_ticks1/(CONVERT_TO_CM*CYCLES_PER_US));   // distance in cm

    return (dist_in_cm1 );
	}
	else if (x==2)
	{        int dist_in_cm2 = 0;
		                // send a 10us high pulse
		                int h=trigger_sonar2();
		                
		                while(!(h & (1<<ECHO2_BIT))){   // while echo pin is still low
			                trig2_counter++;
							h=trigger_sonar2();  
			                uint32_t max_response_time = SONAR_TIMEOUT;
			                if (trig2_counter > max_response_time){   // SONAR_TIMEOUT
				                return TRIG2_ERROR;
			                }
		                }
		                
		                TCNT1=0;                            // reset timer
		                TCCR1B |= (1<<CS10);              // start 16 bit timer with no prescaler
		                TIMSK |= (1<<TOIE1);             // enable overflow interrupt on timer1
		                overFlowCounter=0;                  // reset overflow counter
		                sei();                              // enable global interrupts
		                
		                while((h & (1<<ECHO2_BIT))){ 
							h=trigger_sonar2();   // while echo pin is still high
			                if (((overFlowCounter*TIMER_MAX)+TCNT1) > SONAR_TIMEOUT){
				                return ECHO2_ERROR;          // No echo within sonar range
			                }
		                };
		                
		                TCCR1B = 0x00;                      // stop 16 bit timer with no prescaler
		                cli();                              // disable global interrupts
		                no_of_ticks2 = ((overFlowCounter*TIMER_MAX)+TCNT1);  // counter count
		                dist_in_cm2 = (no_of_ticks2/(CONVERT_TO_CM*CYCLES_PER_US));   // distance in cm

		                return (dist_in_cm2 );
		
		
	}
}

