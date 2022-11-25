// scetch for Arduino controlling the CoPhyLab L-Chmaber venting valves and turbo pump
// code written for Arduino Uno
// G. Kargl, IWF, 11-2022

// --------------------------- Librarys --------------------------
#include <avr/wdt.h>				// watchdog timeout reset
#include <EEPROM.h>					// store data on EEPROM on Arduino

// --------------------------- Definitions --------------------------
	String Version = "ValveSerial 2.0";
// Serial Port ##########################
// set to maximum possible baud rate of Arduino serial port
	long baudrate = 115200;	// Serial port baud rate 19200, 38400, 57600, 115200
// ######################################

// Assign port pins to code name
// Valves
#define Valve1 8; //Assign valve 1 pin to name
#define valve1Read A4; // analog input pin

#define Valve2 9; // Assign valve 2 pin to name


// Turbo pump control with relais contacting TC1200 remote port
// See turbo pump manual page 19
#define TurboPump_Vent 4;		// pin for turbo pump venting relais
#define TurboPump_Motor 5;		// pin for turbo pump motor relais
#define TurboPump_Station 6;	// pin for turbo pump station relais

#define P1_Pin A1;				// whatever conection we are reading here!
#define P2_Pin A5;

// EEPROM memory addresses
	int addr_VA1 = 1;	// status of valve 1 on/off
	int addr_VA2 = 2;	// status of valve 1 on/off
	int addr_TBM = 3;	// status of motor on/off
	int addr_TBS = 4;	// status of turbo stand on/off
	int addr_TBV = 5;	// status of tubo venting on/off


//Variables
	String command = String("Syntax");	// command user input via serial port
	int value = 1;	// command parameter value
	
	int Valve1Status = 0;	// initialise valve status
	int Valve2Status = LOW;	// initialise valve status
	int TurboPump_Vent_Status = 0;
	int TurboPump_Motor_Status = 0;
	int TurboPump_Station_Status = 0;
//	int Needle_valveOpen = 0;
	int val_P1 = 0;  
	int val_P2 = 0;
	int Turbo_Pump_Speed = 0;


// ------------------------------------------------------------------
// initialisation
void setup()
	{


//	checkValveState(); // get status from EEPROM
	
// initialise pins for in or output	
	pinMode(Valve1,OUTPUT);	// initialise and set to current value
	digitalWrite(Valve1,Valve1Status);
/*//	pinMode(valve1Read,INPUT);

	pinMode(Valve2,OUTPUT,Valve2Status);

	pinMode(TurboPump_Vent,OUTPUT,TurboPump_Vent_Status);
	pinMode(TurboPump_Motor,OUTPUT,TurboPump_Motor_Status);
	pinMode(TurboPump_Station,OUTPUT,TurboPump_Station_Status);

//	pinMode(NeedleValve,OUTPUT);
  
	pinMode(P1_Pin,INPUT);
	pinMode(P2_Pin,INPUT);
	pinMode(Turbo_Pump_Speed,INPUT);

// initialize serial communication:
	Serial.begin(baudrate);
	while (!Serial)
	{
	; // wait for serial port to connect. Needed for native USB port only
	}
	Serial.flush();
	String welcome_msg = "MSG: Valve and pump control.";
	Serial.println(welcome_msg);
	Serial.println("SV: " + Version);
	
*/
// write current status to serial here ++++++++++++++++++++++++++++++!	
	}

// main loop
void loop()
	{
/* get a command from serial input
//	if (Serial.available() > 0)
//		{
//		command = Serial.readStringUntil(':');	// read command input until delimiter
//		command.toUpperCase();					// convert command input to upper case
//		value = Serial.parseInt();				// get parameter value for command
//		}
// State machine to control the device
// Selecting for commands
	switch (command) // Main selector
//	{
//		case 'STA':	// get status information of all devices
//		{
//		
//		}
//		break;
		case 'VA1':	// control valve 1
		{
			Serial.print("VA1");
			Serial.println(value);
			if (value != Valve1Status);
			{
//				digitalWrite(Valve1,Valve1Status);
				// update EEPROM value
			}
		}
		break;
		case 'VA2':	// control valve 1
		{
			Serial.print("VA2");
			Serial.println(value);
//			if (value != Valve2Status);
//			{
//				// update EEPROM value
//			}
		}
		break;
*/
/*
		case 'TBM': // control turbo pump motor on/off
		{
		}
		break;
		case 'TBS': // control turbo pump stand on/off
		{
		}
		break;
		case 'TBV': // control turbo pump venting on/off
		{
		}
		break;
		case 'NVL': // control needle valve
		{
		}
		break;

		default: // command not recognised or no command
			// do nothing
		break;
		
//	}
*/

	
	}
// #################### End of code ######################
// subroutines below here
/*void checkValveState() // read status values stored in EEPROM
//	{
//
//	int addr_VA1 = 1;	// status of valve 1 on/off
//	int addr_VA2 = 2;	// status of valve 1 on/off
//	int addr_TBM = 3;	// status of motor on/off
//	int addr_TBS = 4;	// status of turbo stand on/off
//	int addr_TBV = 5;	// status of tubo venting on/off
//

//	Serial.println("Valve status after restart: ");
//	Valve1Status = EEPROM.read(addr_VA1);
//	Valve2Status = EEPROM.read(addr_VA2);
//	TurboPump_Vent_Status = EEPROM.read(addr_TBV);
//	TurboPump_Station_Status = EEPROM.read(addr_TBS);
//	TurboPump_Motor_Status = EEPROM.read(addr_TBM);

//	}
*/