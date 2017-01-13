/*
 * FourWheelDrive.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: neoadmin
 */

#include "FourWheelDrive.h"
//#include "../RobotMap.h"


FourWheelDrive::FourWheelDrive(Constant *LucielleBall) :
		Subsystem("FourWheeelDrive")
{
	constants = LucielleBall;
	leftBack = new VictorSP(constants->Get("backLeftDrive"));
	rightBack  = new VictorSP(constants->Get("backRightDrive"));
	leftFront  = new VictorSP(constants->Get("frontLeftDrive"));
	rightFront  = new VictorSP(constants->Get("frontRightDrive"));
	leftBack->SetInverted(constants->Get("leftBackInvert")== 1);
	leftFront->SetInverted(constants->Get("leftFrontInvert")== 1);
	rightBack->SetInverted(constants->Get("rightBackInvert")== 1);
	rightFront->SetInverted(constants->Get("rightFrontInvert")== 1);
	Drive = new RobotDrive (leftFront, leftBack, rightFront, rightBack);
	shifter = new Solenoid(constants->Get("ShifterSolenoid"));
	shifter2 = new Solenoid(constants->Get("ShifterSolenoid2")); // CAT REMOVE COMMENT IF DOUBLE SOLENOID
	ShifterTest = false;
	RightWheelEncoder = new Encoder(constants->Get("RightEncoderA"), constants->Get("RightEncoderB"));
	LeftWheelEncoder = new Encoder(constants->Get("LeftEncoderA"), constants->Get("LeftEncoderB"));
	Drive->SetSafetyEnabled(false);

	//Navx freaks out the upload so the whole thing is commented out to make it easier for competition

	/*try {
		/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
		/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
		/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
		/*ahrs = new AHRS(SPI::Port::kMXP);
	} catch (std::exception ex ) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::GetInstance().ReportError(err_string.c_str());
	if (ahrs){
		LiveWindow::GetInstance()->AddSensor("IMU", "Angle", ahrs);
	}
	}*/

}

void FourWheelDrive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//precision speed
}

long FourWheelDrive::LeftEncoder(){



	return LeftWheelEncoder->Get();
}
long FourWheelDrive::RightEncoder(){


	return RightWheelEncoder->Get();
}
void FourWheelDrive::arcadeDrive(float Y, float X, bool isHighGear, bool isLowGear){

	if (isHighGear)//high gear
		ShifterTest = true;

	if (isLowGear)//low gear
		ShifterTest = false;

	if (ShifterTest){
		X=X*constants->Get("HighGearXGain");
		Y=Y*constants->Get("HighGearYGain");
	}
	else{
		X=X*constants->Get("LowGearXGain");
		Y=Y*constants->Get("LowGearYGain");
	}
	if (X<.05 && X>-.05){
		X=0;
	}
	if (Y<.05 && Y>-.05){
			Y=0;
	}


	arcadeDrive(Y,X,ShifterTest);
}
void FourWheelDrive::arcadeDrive(float Y, float X, bool isHighGear){
	// Ian's Cheezy drive algorithm
	// algorithm sets a constant difference between left and right drive
	// for all y settings difference is set by x axis.

	// Left and right speed are set for driving with the
	// + and - X and Y sets. This works in all cases until you get
	// a number input from joystick such as (.5,1) this would set the
	// leftSpeed = 1.5 rightSpeed = .5, We want constant different which should
	// be left = 1 right = 0 so we use the if's to catch this issue and
	// subtract the extra .5 from the left speed from the right speed
	double leftSpeed = Y + X;
	double rightSpeed = Y - X;

	if (leftSpeed > 1)	{
		rightSpeed = rightSpeed - (leftSpeed - 1);
		leftSpeed = 1;
	} else if (leftSpeed < -1)	{
		rightSpeed = rightSpeed - (leftSpeed + 1);
		leftSpeed = -1;
	} else if (rightSpeed > 1) {
		leftSpeed = leftSpeed - (rightSpeed - 1);
	} else if (rightSpeed < -1) {
		leftSpeed = leftSpeed - (rightSpeed + 1);
	}

	Drive->TankDrive(leftSpeed, rightSpeed, false);
	// End Ian's Cheezy algorithm

	ShifterTest=isHighGear;

	shifter->Set(ShifterTest);
	 shifter2->Set(!ShifterTest); // CAT REMOVE COMMENT IF NEEDS DOUBLE SOLENOID
}


