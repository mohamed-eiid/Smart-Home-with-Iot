/*
 * RFID.h
 *
 * Created: 02/12/2017 10:57:33 ص
 *  Author: Mohamed
 */ 


#ifndef RFID_H_
#define RFID_H_


#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"
#include "spi.h"
#include "mfrc522.h"




void RFID_INIT ();
void RFID_CHECK();

#endif /* RFID_H_ */