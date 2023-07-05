#include "User.h"

#include <iostream>
#include <string>
#include <fstream>

#include "QueueList.h"
using namespace std;

void User::bookVaccine(QueueList<long>* firstDose, QueueList<long>* secondDose)
{
	//farahat
	
	if (firstDose->elementExists(&userId))
	{
		cout << "\n\t\t\t*******\n";
		cout << "\t\t Error: You're already in queue for the first dose!" << endl;
	}
	else if (secondDose->elementExists(&userId))
	{
		cout << "\n\t\t\t*******\n";
		cout << "\t\t Error: You're already in queue for the second dose!" << endl;
	}
	else if (isvaxed)
	{
		cout << "\n\t\t\t*******\n";
		cout << "\t\t Error: You're already vaccinated!" << endl;
	}
	else if (remainingDoses == 2)
	{
		firstDose->enqueue(&userId);
		cout << "\t\t You have been added to the first dose waiting list!" << endl;
		remainingDoses--;
	}
	else if (remainingDoses == 1 && !firstDose->elementExists(&userId))
	{
		secondDose->enqueue(&userId);
		cout << "\t\t You have been added to the second dose waiting list!" << endl;
		remainingDoses--;
	}

}

void User::printUser()
{
	cout << "\n\n";
	cout << "\tID: " << userId << endl;
	cout << "\tName: " << name << endl;
	cout << "\tAge: " << age << endl;
	cout << "\tGender: " << gender << endl;
	cout << "\tGovernerate: " << governorate << endl;
	cout << "\tRemaining doses: " << remainingDoses << endl;
	cout << "\tIs vaccinated: " << isvaxed << endl;
	cout << "\n\n";
}

void User::editUser()
{
	string newName, newGov;
	int newAge;
	char newGender;
	cout << "\n\t Enter your name: ";
	cin >> newName;

	cout << "\n\t Enter your governorate: ";
	cin >> newGov;

	do
	{
		cout << "\n\t Enter gender: (m/f)";
		cin >> newGender;
		if (newGender != 'm' && newGender != 'f')
			cout << "\n\t\tInvalid Input!";
		else
			break;
	} while (true);


	cout << "\n\t Enter your age: ";
	cin >> newAge;
	string newPass, newPass2;
	do
	{
		cout << "\n\t Set your password: ";
		cin >> newPass;
		cout << "\n\t Retype password: ";
		cin >> newPass2;
		if (newPass != newPass2)
			cout << "\n\t Password does not match! Set up your password again!";
	} while (newPass != newPass2);

	name = newName;
	age = newAge;
	gender = newGender;
	governorate = newGov;
	password = newPass;

	cout << "\n\t\tUser updated successfully" << endl;
}

