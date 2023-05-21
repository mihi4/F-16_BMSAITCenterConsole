# BMSAIT Center Console Controller
* Microcontroller: Arduino Nano
## Hardware controlled
* all Centerconsole instruments, except the ADI (driven by the InstrumentpanelController?) and HSI (graphical version):
  * Altimeter
  * ASI (2 needles), 
  * VVI (2 servos)
  * AOA (2 servos)
  * MarkerBeacon

- pin A5: input for rotary push to reset motor
- pin A6: switch for pneu/elec
- pin A7: input to zeroize the stepper 
- pins 2, 3: rotary encoder (2 interrupt pins)
- pins 4, 5, 6, 7: Altimeter continous x27 motor
- pins 8, 9, 10: max7219 for 4+3 7-segment displays
- pins 11, 12, 13, A1, A2, A3, A4: servos for PNEU flag, KIAS, MACH, VVI, AOA, VVIFlag, AOAFlag
- pin A0: marker beacon LED

