/*
 * FourWheelDrive.h
 *
 *  Created on: Jan 10, 2017
 *      Author: neoadmin
 */

#ifndef FourWheelDrive_H
#define FourWheelDrive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotDrive.h>
#include <Joystick.h>
#include <Solenoid.h>
#include <Encoder.h>
#include "Constant.h"
#include <VictorSP.h>
const double EncoderReset = 0;
//#include <Talon.h>

class FourWheelDrive: public Subsystem
{
private:
	RobotDrive *Drive;
	VictorSP *leftBack; //VictorSP
	VictorSP *rightBack;//VictorSP
	VictorSP *rightFront;//VictorSP
	VictorSP *leftFront;//VictorSP
	Solenoid *shifter;
	Solenoid *shifter2; // CAT REMOVE COMMENT IF DOUBLE SOLENOID
	Encoder *RightWheelEncoder;
	Encoder *LeftWheelEncoder;
	bool ShifterTest;
	Constant *constants;


public:
	FourWheelDrive(Constant *LucielleBall);

	void arcadeDrive(float x, float y, bool isHighGear, bool isLowGear);
	void arcadeDrive(float x, float y, bool isHighGear);
	long LeftEncoder();
	long RightEncoder();

	void InitDefaultCommand();

};

#endif /* SRC_SUBSYSTEMS_FOURWHEELDRIVE_H_ */
