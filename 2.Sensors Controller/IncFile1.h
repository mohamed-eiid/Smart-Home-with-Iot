/*
 * IncFile1.h
 *
 * Created: 02/12/2017 18:16:34
 *  Author: nermeen-pc
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#ifndef F_CPU
   #define F_CPU 1000000UL     // CPU Frequency
#endif
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
/*...- . . .-. --- -... --- -
 * Define Ports and Pins as required
 * Modify Maximum response time and delay as required
 * MAX_RESP_TIME : default: 300
 * DELAY_BETWEEN_TESTS : default: 50
 */

/*ultra sonic defines */

#define TRIG1_DDR    DDRD            // Trigger Port
#define TRIG2_DDR    DDRA            // Trigger Port

#define TRIG1_PORT   PORTD
#define TRIG2_PORT   PORTA

#define TRIG1_PIN    PIND
#define TRIG2_PIN    PINA

#define TRIG1_BIT    PD0             // Trigger Pin
#define TRIG2_BIT    PA3 
   
   #define U1_on     distance_in_cm1<20
   #define U2_on     distance_in_cm2<20
   #define U1_off    distance_in_cm1>20
   #define U2_off    distance_in_cm2>20
   
   
 #define op_distance1 PD2          
 
 #define op_distance2 PA2
 #define op_error1D PD3
 #define op_error1A PA4
 
 #define op_error2D PD4
 #define op_error2A PA5
 
#define ECHO1_DDR    DDRD            // Echo Port
#define ECHO2_DDR    DDRA

#define ECHO1_PORT   PORTD
#define ECHO2_PORT   PORTA

#define ECHO1_PIN    PIND
#define ECHO2_PIN    PINA

#define ECHO1_BIT    PD1             // Echo Pin
#define ECHO2_BIT    PA1
 
// Speed of sound
// Default: 343 meters per second in dry air at room temperature (~20C)
#define SPEED_OF_SOUND  343
#define MAX_SONAR_RANGE 10          // This is trigger + echo range (in meters) for SR04
#define DELAY_BETWEEN_TESTS 500     // Echo canceling time between sampling. Default: 500us
#define TIMER_MAX 65535             // 65535 for 16 bit timer and 255 for 8 bit timer
 
/* ...- . . .-. --- -... --- -
 * Do not change anything further unless you know what you're doing
 * */
#define TRIG1_ERROR -1
#define TRIG2_ERROR -1
#define ECHO1_ERROR -2
#define ECHO2_ERROR -2
 
#define CYCLES_PER_US (F_CPU/1000000)// instructions per microsecond
#define CYCLES_PER_MS (F_CPU/1000)      // instructions per millisecond
// Timeout. Decreasing this decreases measuring distance
// but gives faster sampling
#define SONAR_TIMEOUT ((F_CPU*MAX_SONAR_RANGE)/SPEED_OF_SOUND)
 
#define TRIG1_INPUT_MODE() TRIG1_DDR &= ~(1<<TRIG1_BIT)
#define TRIG2_INPUT_MODE() TRIG2_DDR &= ~(1<<TRIG2_BIT)
#define TRIG1_OUTPUT_MODE() TRIG1_DDR |= (1<<TRIG1_BIT)
#define TRIG2_OUTPUT_MODE() TRIG2_DDR |= (1<<TRIG2_BIT)
#define TRIG1_LOW() TRIG1_PORT &= ~(1<<TRIG1_BIT)
#define TRIG2_LOW() TRIG2_PORT &= ~(1<<TRIG2_BIT)
#define TRIG1_HIGH() TRIG1_PORT |=(1<<TRIG1_BIT)
#define TRIG2_HIGH() TRIG2_PORT |=(1<<TRIG2_BIT)
 
#define ECHO1_INPUT_MODE() ECHO1_DDR &= ~(1<<ECHO1_BIT)
#define ECHO2_INPUT_MODE() ECHO2_DDR &= ~(1<<ECHO2_BIT)
#define ECHO1_OUTPUT_MODE() ECHO1_DDR |= (1<<ECHO1_BIT)
#define ECHO2_OUTPUT_MODE() ECHO2_DDR |= (1<<ECHO2_BIT)
#define ECHO1_LOW() ECHO1_PORT &= ~(1<<ECHO1_BIT)
#define ECHO2_LOW() ECHO2_PORT &= ~(1<<ECHO2_BIT)
#define ECHO1_HIGH() ECHO1_PORT |=(1<<ECHO1_BIT)
#define ECHO2_HIGH() ECHO2_PORT |=(1<<ECHO2_BIT)
 
#define CONVERT_TO_CM ((10000*2)/SPEED_OF_SOUND)    // or simply 58

	



///--------------------------------------------------------------ultrasonic function defines----------------------------------------------------------

 
/** ...- . . .-. --- -... --- -
 * @brief   Initiate Ports for Trigger and Echo pins
 * @param   void
 * @return  none
*/
void init_sonar();
 
/**  ...- . . .-. --- -... --- -
 * @brief   Send 10us pulse on Ultrasonic Trigger pin
 * @param   void
 * @return  none
*/
int trigger_sonar1();
int trigger_sonar2();
 
/**  ...- . . .-. --- -... --- -
 * @brief   Calculate and store echo time and return distance
 * @param   void
 * @return  unsigned int
 * Usage    int foo = read_sonar();
*/
unsigned int read_sonar(int);


#endif /* INCFILE1_H_ */