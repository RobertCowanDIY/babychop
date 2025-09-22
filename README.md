#  MiniMonster 🐣

As seen here - https://youtu.be/huZRMhoT-YE

NOTES:

Make sure your arduino has optiboot as the bootloader.  Most ESCs want to see a signal fairly quickly after turning on and a normal arduino will take too long to boot and the ESC will go into a failsafe model.  ESCs want to see a 'zero' signal before controlling the motor, so you might need to adjust your PWM signal in the code to correspond with your ESCs expected 'off' state.
