/*
 * MotionProfiling.h
 *
 *  Created on: Jan 11, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_MOTIONPROFILING_H_
#define SRC_SUBSYSTEMS_MOTIONPROFILING_H_

#include <Timer.h>
 class MotionProfiling{
public:
	 MotionProfiling (double Amax, double Vmax);

private:
	double Amax;
	double Vmax;
	double t3;
	double t2;
	double t1;
	double V0;
	double a;
	double b;
	double c;
	double Xa(double t);
 };



#endif /* SRC_SUBSYSTEMS_MOTIONPROFILING_H_ */
