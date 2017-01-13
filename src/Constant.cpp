/*
 * Constant.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: neoadmin
 */

#include "Constant.h"
#include <fstream>
#include <DriverStation.h>

Constant::Constant() {
	// TODO Auto-generated constructor stub
	reloadFile();
}


void Constant::reloadFile(){
	ifstream myfile("/home/lvuser/ErrorAndTrial.neo");
	if (myfile.is_open())
	{
		string line;
		double value;
		while(!myfile.eof()){
			myfile >> line >> value;
			map.insert (pair<string, double> (line, value));

		}
	}
	myfile.close();
}

double Constant::Get(string constantsName){
	if (map.count(constantsName)<=0){
		DriverStation::GetInstance().ReportError("Cannot find constantName "+constantsName + "\n");
		return -1;
	}

	return map.at (constantsName);
}



