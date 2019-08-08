# Smart Home with Iot
 
Smart home is embedded system project based on IoT system aims to turn our homes to smart homes.

The project is separated to five parts:
• Power saving by sensing the motion and light the house on and off automatically
• Security system by using sensors interfacing with keypad and LCD 
• Smart locks by using RFID 
• Monitoring by using live camera on RaspberryPi3 
• Connectivity by using IoT to connect all the sensors reading and control from mobile

Each part will be discussed individually.

# Power saving

The target of this part is to reduce the consumed power from lighting by switching it on and off automatically using Passive infrared sensor(PIR) in the room to sense the motion and connecting it with ultrasonic sensor in the door of the room to count ever one gets in and out so when the counter counting persons in the room and agree with the reading from PIR sensor the light switched on automatically and when both read 0 the light automatically switching off.

Special case in the code is added as when the PIR reads an information there is a person in the room and the counter counting the number of the people 0 in this case the security mode activates an alarm as it probably indicate to a thief.


# Security system

security system by Keypad and LCD we design a password protected system using a 3x3 keypad, the user will enter a 7 digit numeric password to gain access of the system once the correct password is entered the green led will light and the alarm will stop.

# Smart locks

Replacing ordinary key by tags and cards as a card or a tag passes in front of the reader in which we stored this tag/card id, usually RF Tags id consists of 8 bytes designed by the manufacturer and if the ID is right it rotates the motor and opens the door.


# Monitoring

Security camera system based on raspberry pi3 controller using its module TTL Mini camera.


# Connectivity

Internally, the connectivity established by transmitting the data between sensors and main AVR wirelessly using "Esp8266 NodeMCU" module and establishing IoT system so that will make every home can merge the system easily.
Externally, a mobile application is established to connect the system to the mobile to see what is happening inside the home when you are not there.
