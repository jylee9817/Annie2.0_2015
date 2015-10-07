#include "AnesthesiologistDrive.h"

AnesthesiologistDrive::AnesthesiologistDrive(AnesthesiologistOperatorInterface *opInt)
{
	if(opInt) oi = opInt;
	
	linearVelocity = 0;
	turnSpeed = 0;
	
	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B);   
	shifter->Set(DoubleSolenoid::kReverse);
	
	frontLeftMotor = new CANTalon(DRIVE_FRONT_LEFT_MOTOR_CHANNEL);
	middleLeftMotor = new CANTalon(DRIVE_MIDDLE_LEFT_MOTOR_CHANNEL);
	rearLeftMotor = new CANTalon(DRIVE_REAR_LEFT_MOTOR_CHANNEL);

	frontRightMotor = new CANTalon(DRIVE_FRONT_RIGHT_MOTOR_CHANNEL);
	middleRightMotor = new CANTalon(DRIVE_MIDDLE_RIGHT_MOTOR_CHANNEL);
	rearRightMotor = new CANTalon(DRIVE_REAR_RIGHT_MOTOR_CHANNEL);

	leftCmd = 0;
	rightCmd = 0;

	timer = new Timer();
	timer->Start();
}

AnesthesiologistDrive::~AnesthesiologistDrive()
{
	delete shifter;
	delete frontLeftMotor;
	delete middleLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete middleRightMotor;
	delete rearRightMotor;
	delete timer;
	
	shifter = NULL;
	frontLeftMotor = NULL;
	middleLeftMotor = NULL;
	rearLeftMotor = NULL;
	frontRightMotor = NULL;
	middleLeftMotor = NULL;
	rearRightMotor = NULL;
	timer = NULL;
}

void AnesthesiologistDrive::shift(uint8_t highButton, uint8_t lowButton)
{	
	if(lowButton)
	{
		shifter->Set(DoubleSolenoid::kForward);
	}
	else if(highButton)
	{
		shifter->Set(DoubleSolenoid::kReverse);
	}
}

bool AnesthesiologistDrive::getShiftState()
{
	//if in low gear
	if(shifter->Get() == DoubleSolenoid::kForward)
	{
		return true;
	}
	return false;
}

void AnesthesiologistDrive::setLinVelocity(double linVal)
{
	if(linVal > DEADZONE)
	{
		linearVelocity = linVal;
	}
	else if(linVal < -DEADZONE)
	{
		linearVelocity = linVal;
	}
	else 
	{
		linearVelocity = 0; //NEUTRAL
	}	
}

double AnesthesiologistDrive::getLinVelocity()
{
	return linearVelocity;
}

void AnesthesiologistDrive::setTurnSpeed(double turn, bool turboButton)
{
	if((turn > DEADZONE && !turboButton) || (turn < -DEADZONE && !turboButton)) 
	{
		turnSpeed = turn * REDUCTION;
	}
	if(turn < DEADZONE && turn > -DEADZONE) 
	{
		turnSpeed = 0; //NEUTRAL
	}
	if((turn > DEADZONE && turboButton) || (turn < -DEADZONE && turboButton)) 
	{
		turnSpeed = turn;
	}
}

double AnesthesiologistDrive::getTurnSpeed()
{
	return turnSpeed;
}

double AnesthesiologistDrive::reduceTurn(double reduceBy)
{
	return turnSpeed * reduceBy;
}

void AnesthesiologistDrive::setLeftMotors(double velocity)
{
	frontLeftMotor->Set(-velocity); // sync state off is removed. All talons needed SYNC_STATE_OFF as second parameter, but due to update it is no longer needed
	middleLeftMotor->Set(-velocity);
	rearLeftMotor->Set(-velocity);
}

void AnesthesiologistDrive::setRightMotors(double velocity)
{
	frontRightMotor->Set(velocity);
	middleRightMotor->Set(velocity);
	rearRightMotor->Set(velocity);
}


void AnesthesiologistDrive::drive()
{
	leftCmd = linearVelocity + turnSpeed;
	rightCmd = linearVelocity - turnSpeed;
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}
