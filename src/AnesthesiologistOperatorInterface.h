#ifndef ANESTHESIOLOGIST_OPERATOR_INTERFACE_H
#define ANESTHESIOLOGIST_OPERATOR_INTERFACE_H


#include "WPILib.h"
#include "AnesthesiologistMacros.h"

#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/NamedSendable.h"
#include "SmartDashboard/Sendable.h"
#include "SmartDashboard/SendableChooser.h"

class AnesthesiologistOperatorInterface
{
	
public:
	AnesthesiologistOperatorInterface();	
	~AnesthesiologistOperatorInterface();
	
	Joystick *getDriveJoystick();
	bool getDriveJoystickButton(uint8_t button);
	bool getDriveJoystickButtonReleased(uint8_t button);

	Joystick *getManipJoystick();		
	bool getManipJoystickButton(uint8_t button);
	bool getManipJoystickButtonReleased(uint8_t button);
	
	float getBatteryVoltage();
	
	DriverStation *getDriverStation();
	//DriverStationLCD *dsLCD; this does not exist? - WPlib removed this functionality at 2015?
	SmartDashboard *dashboard;
	
private:
	Joystick *joyDrive;
	Joystick *joyManip;
	//DriverStationEnhancedIO *ds;  also got removed? - WPlib removed this functionality at 2015?
	DriverStation *dsSimple;
};
#endif
