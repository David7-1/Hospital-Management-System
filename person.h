#pragma once
#ifndef PERSON
#define PERSON
#include<string>
#include "address.h"
using namespace std;

class person {
protected:
	int id;
	string firstName, lastName;
	char gender;
	int16_t age;
	string phoneNumber;
	address add;
	string cat;
	int category;
public:
	person();
	virtual void fillMap() = 0;
	virtual void saveMap() = 0;
	virtual void addPerson(int16_t minAge = 0, int16_t maxAge = 1000);
	virtual void printDetails();
	virtual void printDetailsFromHistory();
	virtual void getDetails(int rec = 0) = 0;
	virtual void getDetailsFromHistory() = 0;
	virtual void removePerson() = 0;

};
#endif // !PERSON
