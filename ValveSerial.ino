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
	long baudrate = 9600;	// Serial port baud rate 19200, 38400, 57600, 115200
// ######################################

// Assign port pins to code name
// Valves
#define Valve1 8 //Assign valve 1 control pin
#define valve1Read A4 // Valve 1 status input

#define Valve2 9 // Assign valve 2 control pin
#define valve2Read A2 // Valve 2 status input

// Turbo pump control with relais contacting TC1200 remote port
// See turbo pump manual page 19
#define TurboPump_Vent 4		// pin for turbo pump venting relais
#define TurboPump_Motor 5		// pin for turbo pump motor relais
#define TurboPump_Station 6	// pin for turbo pump station relais

#define P1_Pin A1				// whatever conection we are reading here!
#define P2_Pin A5

// EEPROM memory addresses
	int addr_VA1 = 1;	// status of valve 1 on/off
	int addr_VA2 = 2;	// status of valve 2 on/off
	int addr_TPM = 3;	// status of motor on/off
	int addr_TPS = 4;	// status of turbo stand on/off
	int addr_TPV = 5;	// status of tubo venting on/off


//Variables
	String command = "Syntax";	// command user input via serial port
	int value = 1;	// command parameter value

	String cmdlist = "NON STA VA1 VA2 TPM TPV TPS EEP RES HELLO";
	int cmdind = 0;
	
	int Valve1Status = 0;	// initialise valve status
	int Valve2Status = 0;	// initialise valve status
	int TurboPump_Vent_Status = 0;
	int TurboPump_Motor_Status = 0;
	int TurboPump_Station_Status = 0;
	int Needle_valveOpen = 0;
	int val_P1 = 0;  
	int val_P2 = 0;
	int Turbo_Pump_Speed = 0;

// ------------------------------------------------------------------
// initialisation
void setup()
	{


	checkValveState(); // get status from EEPROM
	
// initialise pins for in or output	
// Chamber venting valves
	pinMode(Valve1,OUTPUT);	// initialise and set to current value
	digitalWrite(Valve1,Valve1Status);
	pinMode(valve1Read,INPUT);
	pinMode(Valve2,OUTPUT);
	digitalWrite(Valve2,Valve2Status);
	pinMode(valve2Read,INPUT);
	
	pinMode(TurboPump_Vent,OUTPUT);
	digitalWrite(TurboPump_Vent,TurboPump_Vent_Status);
	pinMode(TurboPump_Motor,OUTPUT);
	digitalWrite(TurboPump_Motor,TurboPump_Motor_Status);
	pinMode(TurboPump_Station,OUTPUT);
	digitalWrite(TurboPump_Station,TurboPump_Station_Status);

//	pinMode(NeedleValve,OUTPUT);
/*  
	pinMode(P1_Pin,INPUT);
	pinMode(P2_Pin,INPUT);
	pinMode(Turbo_Pump_Speed,INPUT);
*/
// initialize serial communication:
	Serial.begin(baudrate);
	while (!Serial)
	{
	; // wait for serial port to connect. Needed for native USB port only
	}
	Serial.flush();
	String welcome_msg = "MSG: Valve and pump control.";
//	Serial.println(welcome_msg);
//	Serial.println("SVE: " + Version);

	wdt_enable(WDTO_8S);   // Watchdog set to 8 s [Arduino resets after 8s "hanging"]
	}

// main loop
void loop()
	{
// get a command from serial input
	if (Serial.available() > 0)
		{
//		command = Serial.readStringUntil(':');	// read command input until delimiter
		String Sercommand = Serial.readString();	// read command input until delimiter
		Sercommand.toUpperCase();
		Sercommand.trim();
 //Serial.print("Received ");
// Serial.println(Sercommand);
		// convert command input to upper case
		int delim = Sercommand.indexOf(':');
		command = Sercommand.substring(0,delim);
		
		String svalue = Sercommand.substring(delim+1);

		value = svalue.toInt();				// get parameter value for command
// Serial.println("Command: " + command);
// Serial.print("Value ");
// Serial.println(value);
		
		cmdind = cmdlist.indexOf(command);
//		cmdind = cmdindstr.toInt();

// Serial.println("Cmd index " + String(cmdind));

		}
	else
		{
		command = "Nothing";
		}
// State machine to control the device
// Selecting for commands
	switch (cmdind) // Main selector
	{
		case 4:	// STA get status information of all devices
		{
//		Serial.println("STA received");
		Serial.print("status:");
//		Serial.print(",");
		Serial.print(digitalRead(Valve1));
		Serial.print(",");
		Serial.print(digitalRead(Valve2));
		Serial.print(",");
		Serial.print(digitalRead(TurboPump_Motor));
		Serial.print(",");
		Serial.print(digitalRead(TurboPump_Station));       
		Serial.print(",");
		Serial.print(digitalRead(TurboPump_Vent)); 

		}
		break;	
		case 8:	//VA1 control valve 1
		{			
			if (value != Valve1Status)
			{
//				Serial.print("VA1 status changed " + String(value));
				digitalWrite(Valve1,value);
        if (value == 0) {
          digitalWrite(TurboPump_Motor,0); //TMP off if valve closed
          EEPROM.update(addr_TPM,0);
        }
        if (value == 1) {
          digitalWrite(Valve2,0); // Valve 2 closed if valve 1 opened
          EEPROM.update(addr_VA2,0);
        }
				// update EEPROM value
				EEPROM.update(addr_VA1,value);
			}
			Valve1Status = value;
			Serial.print("VA1:");
//			Serial.print(Valve1Status);
			Serial.print(value);
      Serial.print(";");
		}
		break;
		case 12:	//'VA2' control valve 1
		{
			if (value != Valve2Status && !TurboPump_Motor_Status && !Valve1Status) //Valve 2 only if valve 1 closed and TMP off
			{
//				Serial.print("VA2 status changed " + String(value));
				digitalWrite(Valve2,value);
				// update EEPROM value
				EEPROM.update(addr_VA2,value);
			}
			Valve2Status = value;
			Serial.print("VA2:");
			Serial.print(value);
      Serial.print(";");
		}
		break;
		case 16: // 'TPM'control turbo pump motor on/off
		{
			if (value != TurboPump_Motor_Status && Valve1Status)
			{
//				Serial.print("TPM status changed " + String(value));
				digitalWrite(TurboPump_Motor,value);
				EEPROM.update(addr_TPM,value);
			}
			TurboPump_Motor_Status = value;
			Serial.print("TPM:");
			Serial.print(value);
      Serial.print(";");
		}
		break;
		case 20: //'TPV' control turbo pump venting on/off
		{
			if (value != TurboPump_Vent_Status)
			{
//				Serial.print("TPV status changed " + String(value));
				digitalWrite(TurboPump_Vent,value);
				EEPROM.update(addr_TPV,value);
			}
			TurboPump_Station_Status = value;
			Serial.print("TPV:");
			Serial.print(value);
      Serial.print(";");
		}
		break;
		case 24: //'TPS' control turbo pump stand on/off
		{
			if (value != TurboPump_Station_Status)
			{
//				Serial.print("TPS status changed " + String(value));
				digitalWrite(TurboPump_Station,value);
				EEPROM.update(addr_TPS,value);
			}
			TurboPump_Vent_Status = value;
			Serial.print("TPS:");
			Serial.print(value);
      Serial.print(";");
		}
		break;
		case 28: // EEPROM values
		{
			Serial.print("EEPROM status: ");
			Serial.print(EEPROM.read(addr_VA1));
			Serial.print(",");
			Serial.print(EEPROM.read(addr_VA2));
			Serial.print(",");
			Serial.print(EEPROM.read(addr_TPM));
			Serial.print(",");
			Serial.print(EEPROM.read(addr_TPS));
			Serial.print(",");
			Serial.print(EEPROM.read(addr_TPV));

		}
		break;
		case 32: // RES force reboot
		{
			delay(10000);	// wait 10 s to trigger watchdog
					/*	delay time has to be larger than
						watchdog critical time!
						default wd time 8 s
						overun causes soft reboot
					*/
		}
		break;
		case 36: // service message
		{
			Serial.print("Hello_Pumping;");
		}
		break;
/*		case 'NVL': // control needle valve
		{
		// not implemented
		}
		break;
*/
		default: // command not recognised or no command
			// do nothing
		break;
		
	}
	cmdind = 0;

	wdt_reset();		// reset watchdog to prevent automatic reset	
	}
// #################### End of code ######################
// subroutines below here
void checkValveState() // read status values stored in EEPROM
	{
//
//	int addr_VA1 = 1;	// status of valve 1 on/off
//	int addr_VA2 = 2;	// status of valve 1 on/off
//	int addr_TPM = 3;	// status of motor on/off
//	int addr_TPS = 4;	// status of turbo stand on/off
//	int addr_TPV = 5;	// status of tubo venting on/off
//

//	Serial.println("Valve status after restart: ");
	Valve1Status = EEPROM.read(addr_VA1);
	Valve2Status = EEPROM.read(addr_VA2);
	TurboPump_Vent_Status = EEPROM.read(addr_TPV);
	TurboPump_Station_Status = EEPROM.read(addr_TPS);
	TurboPump_Motor_Status = EEPROM.read(addr_TPM);

	}
