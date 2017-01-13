/*
 * MotionProfiling.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: neoadmin
 */

#include <Subsystems/MotionProfiling.h>
#include <iostream>
#include <Timer.h>
#include <Joystick.h>

MotionProfiling::MotionProfiling (double AMax, double VMax){

	Amax = AMax;
	Vmax = VMax;
	t1 = 0;
	t2 = 0;
	t3 = 0;
	V0 = 0;
	a = 0;
	b = 0;
	c = 0;

	t1 = Vmax/Amax;
}

double MotionProfiling::Xa(double t){
		return t;
}
/*
 * 		GetX(t);
 * 		if (t<= t1){
 * 				Xa(t);
 * 		}
 * 		if (t1<t<=t2){
 * 				Xb(t-t1)+Xa(t1);
 * 		}
 * 		if (t2<t<=t3){
 * 				Xc(t-t1-t2)+Xa(t1)+Xb(t2);
 * 		}
 * 		if (t>t3){
 * 				distance;
 * 		}
 */



