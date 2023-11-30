#pragma once
#ifndef APPOINTMENT
#define APPOINTMENT
using namespace std;

#include"patient.h"
#include"doctor.h"

class appointment {
private:
	int id;
	int hour;
	doctor D;
	patient P;
public:
	appointment();
	~appointment();
	void fillMap();
	void saveMap();
	void printDetails();
	void book();
	void fillDetails();
	void getDetails();
};
#endif // !APPOINTMENT
