/*
 * Main_Avr.c
 *
 * 
 *  Author: Smart Home Project
 */ 

#define F_CPU 1000000U
#include <avr/io.h>
#include <util/delay.h>
#include "RFID.h"
#include "lcd.h"
#include "keypad.h"
#include "std_types.h"
#include "UART.h"
#include <avr/interrupt.h>
#define NUMBER_OF_OVERFLOWS_PER_HALF_SECOND 120

unsigned char g_tick = 0;
uint8 ok=0;
uint8 zft=0;
extern uint8  door_is_open; //i will but here =1 as i assumed the id is correct to move to next stage of the code
char * p;

ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_HALF_SECOND)
	{

		//toggle led every 0.5 second
		//g_tick = 0;
		zft=1;ok=1;
		//clear the tick counter again to count a new 0.5 second
	}
}


void timer0_init_normal_mode(void)
{
	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}

int main(void)
{
	//------------------ RFID Initialization ------------------//
	
		RFID_INIT();
	
	//------------------ Keypad Initialization ------------------//
	
	SREG  |= (1<<7);

	uint8 key;
	uint8 m;
	uint8 no_of_trials=0;
	uint32 n;

	uint8 count;
	uint8 i;
	uint16 password[5]={1,2,3,4,5};
	uint16 check[5];
	//------------------ LCD Initialization ------------------//
	
	LCD_init();
	LCD_displayStringRowColumn(2,0,"ENTER PASSWORD");
	LCD_goToRowColumn(3,0);
	
	DDRD = DDRD | (1<<PD6);    
	DDRD = DDRD | (1<<PD7);    
	
	PORTD = PORTD & (~(1<<PD6)); 
	PORTD = PORTD & (~(1<<PD7));
	
	//------------------ WIFI Initialization ------------------//
	//-- we used LCD in code to watch the transfer and make sure of the code --//
	
	Uart_init(9600); // Baud rate for communication with the ESP8266
	//LCD_Init();
	//LCD_GoTO_Row_Colunmn(0, 0);

	DDRD |= (1 << PD7);
	PORTD |= (1 << PD7);
	
    while(1)
    {
		//------------------- check RFID key ---------------------//
		//--------------------------------------------------------//
		
		RFID_CHECK();
		
       //------------------- Security System -------------------//
	   //-------------- Keypad and LCD interfacing -------------//
       //-------------------------------------------------------//
	    if(door_is_open)
	    timer0_init_normal_mode();
	    n=g_tick;

	    if(n<=120)
	    {    n=g_tick;
		    if(zft!=1)
		    {  if((zft!=1))

			    {n=g_tick; if (((no_of_trials<3)&&(ok!=1)&&(zft!=1)))
				    {if((key <= 9) && (key >= 0))
					    {for(count=0;count<5;count++)
						    { key = KeyPad_getPressedKey();
							    check[count]=key;
							    LCD_displayStringRowColumn(3,count,"*");
						    _delay_ms(300);}
						    LCD_clearScreen();
						    m=0;
						    for(i=0;i<5;i++)
						    { if(!(check[i]==password[i])){m=0;}
						    if(check[i]==password[i]){m=m+1;} }
						    if(m==5)
						    {LCD_displayStringRowColumn(3,0,"CORRECT PASSWORD");
							    PORTD |= (1<<PD6);
							    _delay_ms(3500);
							    
							    CLEAR_BIT(PORTD,PD6);
							    ok=1;
							    break;
							    LCD_clearScreen();
						    }
						    else
						    {
							    LCD_displayStringRowColumn(3,0,"INVALID");
							    no_of_trials=no_of_trials+1;
							    PORTD |= (1<<PD7);
							    _delay_ms(500);
							    CLEAR_BIT(PORTD,PD7);
							    
							    LCD_clearScreen();
							    if (no_of_trials<3)
							    { LCD_displayStringRowColumn(2,0,"TRY AGAIN");
								    _delay_ms(500);
							    }
							    ok=0;
							    LCD_clearScreen();
						    }

					    }
					    }else {LCD_clearScreen();LCD_displayStringRowColumn(2,0,"starting");
				    LCD_displayStringRowColumn(3,0,"security system");break;}
				    }else {LCD_clearScreen();LCD_displayStringRowColumn(2,0,"starting");
			    LCD_displayStringRowColumn(3,0,"security system");}
			    }else {LCD_clearScreen();LCD_displayStringRowColumn(2,0,"runtime error");break;}



		    }

		    else {LCD_clearScreen();LCD_displayStringRowColumn(2,0,"runtime error");break;}
	  
	   //------------------- WIFI Module ---------------------//
	   //--------------------------------------------------------//
	   
	   //LCD_GoTO_Row_Colunmn(0, 0);
	   UART_recieve_string(p);
	   _delay_ms(100);

	   if ((p[0] == 'O') && (p[1] == 'N')) // ON
	   {
		   _delay_ms(100);
		   PORTD &= ~(1 << PD7);
		  // LCD_Send_String("ON ");
	   } else if ((p[0] == 'O') && (p[1] == 'F') && (p[2] == 'F')) // OFF
	   {
		   _delay_ms(100);
		   PORTD |= (1 << PD7);
		   //LCD_Send_String("OFF");
    }
	
}
			}