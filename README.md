# ArduinoSecuritySystem
This is a simple security system that I made using an Arduino mega, LCD1602 module, HC-SR501 PIR motion sensor module, 4x4 membrane keypad, potentiometer, a LED, and two resistors.

This security system works by using the Arduino to keep track of the states. The first state, state 0, is when the alarm is not armed. State 1 is when the alarm is active but hasn't seen any motion. To go back and forth between states 0 and 1, type in the password on the keypad then hit * to submit the password. If motion is detected by the PIR module, then the system goes into state 2, where after a countdown it will go into state 3. State 3 represents the alarm going off, which is signified by the LED turning on. To go from state 2 or 3 to state 0, type in the password and then hit *.

The LCD module will display the current stage. The PIR sensor should be placed so that it faces the direction that you want to detect movement in. In my personal testing of this security system, I found that the PIR sensor would sometime give false positives. This could be changed by requiring a certain amount of movement before it triggers a change of stage. However, this change was not implemented in this code. The password can be changed by changing the password variable. This system should also work with a 3x4 membrane keypad, though the wiring and some of the input may differ. States 2 and 3 go back to state 0 instead of state 1 because in my testing I found that the PIR sensor would immediately trigger as a result of me typing in the keypad. This could be changed by placing the keypad not in range of the sensor. 

The output for this system goes to a LED in my schematic, but it can easily be replaced with a different component. The current output pin is in the variable ledPin, which is set on pin 13. This can be changed and new pins can be added to fit new output mechanisms.

This code is run on an Arduino Mega board, but the basis for this project should work on other Arduino boards. Some of the code may vary between boards, but most should remain the same.

The following is a schematic of how to wire up the Arduino security system using the pins as listed in the code.

<img width="3000" height="2380" alt="circuit_image (1)" src="https://github.com/user-attachments/assets/9560837e-0643-4045-9bc6-679aa677dbb2" />
