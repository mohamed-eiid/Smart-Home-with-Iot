/*
 * RFID.c
 *
 * Created: 02/12/2017 10:58:08 ص
 *  Author: Mohamed
 */ 

#include "RFID.h"
#define Green_LED1	PB0
#define Green_LED2	PB1
#define Red_LED		PB2
#include "std_types.h"
uint8_t byte;
uint8_t door_is_open;

void RFID_INIT ()
{
		
	    spi_init();
	    _delay_ms(1000);
	    
	    //init reader
	    mfrc522_init();
	    
	    //check version of the reader
	    byte = mfrc522_read(VersionReg);
	    
	    byte = mfrc522_read(ComIEnReg);
	    mfrc522_write(ComIEnReg,byte|0x20);
		
	    byte = mfrc522_read(DivIEnReg);
	    mfrc522_write(DivIEnReg,byte|0x80);
	    
	    _delay_ms(1500);
		
	   DDRB |= (1<<PB0);    //configure as o/p
	   DDRB |= (1<<PB1);    //configure as o/p
	   DDRB |= (1<<PB2);    //configure as o/p

	//set all leds off   
	 PORTB &= (~(1<<Green_LED1));
	 PORTB &= (~(1<<Green_LED2));
	 PORTB &= (~(1<<Red_LED));
	 
	 int door_is_open = 0;
}


void RFID_CHECK()
{
	uint8_t Blue1[8]  ={0xf5,0x4c,0xd5,0x65,0x09,0xfe,0xa9,0x9f};
	uint8_t Blue2[8]  ={0x02,0x86,0xae,0xd5,0xff,0xfe,0xa9,0x9f};
	uint8_t i;
	uint8_t str[MAX_LEN];

	
	byte = mfrc522_request(PICC_REQALL,str);
	
	if(byte == CARD_FOUND)
	{
		byte = mfrc522_get_card_serial(str);
		
		if(byte == CARD_FOUND)
		{
			for( i=0;i<4;i++)
			{
				if(Blue1[i] != str[i])
				break;
				
			}
			if(i==4)
			{
				PORTB |= (1<<Green_LED1); // LED1 Green open
				door_is_open = 1;
				_delay_ms(1500);
			}
			else
			{
				for( i=0;i<4;i++)
				{
					if(Blue2[i] != str[i])
					break;
					
				}
				if(i==4)
				{
					PORTB |= (1<<Green_LED2); // LED2 Green open
					door_is_open = 1;
					_delay_ms(1500);
				}
				else
				{
					PORTB |= (1<<Red_LED); // LED RED open
					_delay_ms(1500);
				}
				
			}}
			else
			{
				PORTB = PORTB ^ (1<<Red_LED); 
			}
		}
		
		_delay_ms(1000);
	
	}

