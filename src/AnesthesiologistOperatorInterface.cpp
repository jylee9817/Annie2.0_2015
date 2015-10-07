#include "AnesthesiologistOperatorInterface.h"

AnesthesiologistOperatorInterface::AnesthesiologistOperatorInterface()
{
	joyDrive = new Joystick(1);
	joyManip = new Joystick(2);
	dsSimple = DriverStation::GetInstance();
	//ds = &dsSimple->GetEnhancedIO();
	//dsLCD = DriverStationLCD::GetInstance();
	dashboard->init();
}


AnesthesiologistOperatorInterface::~AnesthesiologistOperatorInterface()
{
	//delete dsLCD;
	delete joyDrive;
	delete joyManip;
	
	//dsLCD = NULL;
	joyDrive = NULL;
	joyManip = NULL;	
}

Joystick *AnesthesiologistOperatorInterface::getDriveJoystick()
{
    return joyDrive;
}

Joystick *AnesthesiologistOperatorInterface::getManipJoystick()
{
    return joyManip;
}

bool AnesthesiologistOperatorInterface::getDriveJoystickButton(uint8_t button)
{
	 if(joyDrive->GetRawButton(button))
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
}

bool AnesthesiologistOperatorInterface::getManipJoystickButton(uint8_t button)
{
	if( joyManip->GetRawButton(button) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float AnesthesiologistOperatorInterface::getBatteryVoltage()
{
	return DriverStation::GetInstance()->GetBatteryVoltage();
}
