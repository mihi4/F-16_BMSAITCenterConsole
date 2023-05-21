/* Here are all the functions, vars and definitions for the internal things */

#define KNOBBUTTONPIN A5
#define PNEUPIN A7  
  
// Knob button 
OneButton knob(KNOBBUTTONPIN, true);  

void changeConfigMode() {
	configmode = !configmode;
	if (debugmode) SendMessage("Configmode Changed",1);
}
void resetAltimeter() {
	AltimeterX27_Zeroize(false);
	if (debugmode) SendMessage("Resetting Altimeter",1);
}

void SetupAltimeterKnob() {	
	knob.attachLongPressStart(changeConfigMode);
	knob.attachDoubleClick(resetAltimeter);
	pinMode(PNEUPIN, INPUT_PULLUP);
}

void UpdateAltimeterKnob() {
	knob.tick();
}

void increaseAltimeterOffset() {
	altimeterOffset += 1;
}

void decreaseAltimeterOffset() {
	altimeterOffset -= 1;
}

bool pneuActivated() {
	return analogRead(PNEUPIN) > 5 ? 1 : 0;
}
