// settings and functions to drive servo motors (directly connected to the arduino)
// V1.3.7 26.09.2021

//target= reference link to the line of the servodata table of this module
//ref2= not used
//ref3= not used
//ref4= not used
//ref5= not used

#include <Servo.h>

#define SERVODELAY 80
#define SERVOSLEEPTIME 20000

typedef struct
{
byte pIN;           //PIN the motor is connected to
byte p_ug;          //min arc for the motor (must not be less than 0!)
byte p_og;          //max arc for the motor (must not be more than 180!)
long a_ug;           //min absolut value that might be displayed (i.e.   0 for a speed indicator)
long a_og;           //max absolut value that might be displayed (i.e. 800 for a speed indicator)
long last;           //previous value
unsigned long lu;   //last update
} Servodata;


Servodata servodata[] =
{// pIN  p_ug  p_og  a_ug  a_og  last  lu
    //{A1,   0,   180,   0,   800,    0,   0},  // example speed indicator: {Servo on PIN=9, min arc =0, max arc=180, lowest possible value=0, highest value=800, past value=0, lastUpdate=0}
	{11,   0,   90,   0,   1,    0,   0},  // PNEU Flag
	{12,   0,   180,   0,   65535,    0,   0},  // KIAS	
	{13,   0,   180,   0,   20,    0,   0},  // mach
	{A1,   40,   140,   -170,  170,    0,   0},  // VVI usually -100 to 100; default value uses just -170 to 170 for values of -1.0 to 1.0
    {A2,   0,   90,   0,   1,    0,   0},  // vvi data2
	{A3,   0,   180,   -350,   350,    0,   0},  // AOA  -35 to 35 deg; float value, see above
	{A4,   0,   90,   0,   1,    0,   0}  // AOA Flag 
};
const int SERVOZAHL = sizeof(servodata)/sizeof(servodata[0]);
Servo servo[SERVOZAHL];

void SetupServo()
{  
  for (byte lauf=0;lauf<SERVOZAHL;lauf++)
  {
    servo[lauf].attach(servodata[lauf].pIN);
    servo[lauf].write(servodata[lauf].p_ug);
    delay(500);
    servo[lauf].write(servodata[lauf].p_og);
    delay(500);
    servo[lauf].write(90);
    delay(500);
	servo[lauf].write(servodata[lauf].p_ug);
	delay(100);
    servo[lauf].detach();
  }
}

void Servo_FastUpdate()
{}

void Servo_Zeroize(bool mode)
{
  for (byte lauf=0;lauf<SERVOZAHL;lauf++)
  {
    if (!servo[lauf].attached())
        {servo[lauf].attach(servodata[lauf].pIN);}  //reactivate servo
    servo[lauf].write(servodata[lauf].p_ug);
    if (mode)
    {
      delay(500);
      servo[lauf].write(servodata[lauf].p_og);
      delay(5000);
      servo[lauf].write(servodata[lauf].p_og - servodata[lauf].p_ug);
      delay(5000);
    }
	servo[lauf].write(servodata[lauf].p_ug);
	delay(100);
    servo[lauf].detach();
  }
}


void UpdateServo(byte id)
{	

	/*if (debugmode){SendMessage("updatingServo",1);}
	if (debugmode){SendMessage(datenfeld[id].ID,1);}
	if (debugmode){SendMessage(datenfeld[id].wert,1);}  */

  if (servodata[datenfeld[id].target].lu + SERVOSLEEPTIME < millis())
  {
    servo[datenfeld[id].target].detach();                        //disable servo if no new signal for more than 5 seconds
  }  
  else if (servodata[datenfeld[id].target].lu + SERVODELAY < millis())
  {
    servodata[datenfeld[id].target].lu = millis();  //pause servo
    
	long newValue = 0;
	if (datenfeld[id].format == 'f') { 
		float tmpVal = atof(datenfeld[id].wert);
		newValue = tmpVal * 10;
	} else {
		newValue = atol(datenfeld[id].wert);
	}
	if (id == 6) {
		char buff[12];
		SendMessage(datenfeld[id].bezeichnung,1);
		SendMessage(ltoa(newValue, buff, 10),1);
	}
    if (servodata[datenfeld[id].target].last != newValue)
    {	  
	  uint16_t winkel;
      servodata[datenfeld[id].target].last = newValue; 
      if (!servo[datenfeld[id].target].attached())
        {servo[datenfeld[id].target].attach(servodata[datenfeld[id].target].pIN);}  //reactivate servo      
	  winkel = map(servodata[datenfeld[id].target].last, servodata[datenfeld[id].target].a_ug, servodata[datenfeld[id].target].a_og, servodata[datenfeld[id].target].p_ug, servodata[datenfeld[id].target].p_og); 
	  if (id == 6) {  // special calculations for MLU VVI gauge		
			if (newValue > 170) winkel = map(newValue, 171, 900, 140, 180);
			if (newValue < -170) winkel = map(newValue, -900, -171, 0, 40);				  
	  }
	  servo[datenfeld[id].target].write(winkel);          
    }
  }
}
