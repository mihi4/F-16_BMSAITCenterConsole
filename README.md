# Center Console Nano

This Arduino Nano will drive the Centerconsole instruments, except the ADI and HSI.  
Altimeter, the 2 ASI needles, 4 additional servos of VVI and AOA and the MarkerBeacon

- pin A5: input for rotary push to reset motor
- pin A6: switch for pneu/elec
- pin A7: input to zeroize the stepper 
- pins 2, 3: rotary encoder (2 interrupt pins)
- pins 4, 5, 6, 7: Altimeter continous x27 motor
- pins 8, 9, 10: max7210 for 4+3 7-segment displays
- pins 11, 12, 13, A1, A2, A3, A4: servos for PNEU flag, KIAS, MACH, VVI, AOA, VVIFlag, AOAFlag
- pin A0: marker beacon LED

