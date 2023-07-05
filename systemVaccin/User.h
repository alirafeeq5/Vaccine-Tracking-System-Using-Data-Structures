#pragma once
#include <string>

#include "QueueList.h"
using namespace std;

class User
{
public:
	string name;
	long userId;
	string password;
	char gender;
	int age;
	string country;
	string governorate;
	bool isvaxed;
	int remainingDoses;

	User() :
		name(""),
		userId(0),
		password(""),
		gender('f'),
		age(0),
		country(""),
		governorate(""),
		isvaxed(false),
		remainingDoses(2) {}

	User(string n, int i, string pass, char g, int ag, string ctr, string gov, bool vaxed, int dose)
	{
		name = n;
		userId = i;
		password = pass;
		gender = g;
		age = ag;
		country = ctr;
		governorate = gov;
		isvaxed = vaxed;
		remainingDoses = dose;
	}

	void bookVaccine(QueueList<long>*, QueueList<long>*);
	void printUser();
	void editUser();
};
