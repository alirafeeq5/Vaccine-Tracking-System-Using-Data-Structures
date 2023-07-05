#include <iostream>
#include "List.h"
#include "QueueList.h"
#include "User.h"
#include "AdminControl.h"
using namespace std;

void AdminControl::viewSingleRecord(List<User>* users)
{
	long id;
	cout << "\tEnter National ID to view the record: ";
	cin >> id;
	cout << endl;

	try
	{
		users->getUserByID(id)->printUser();
	}
	catch (runtime_error e)
	{
		cout << "\t" << e.what() << endl;
	}
}

void AdminControl::viewAllRecords(List<User>* users)
{
	for (int i = 0; i < users->length(); i++)
	{
		cout << "\t----------------------------\t";
		users->getByIndex(i)->printUser();
	}
}


void AdminControl::deleteUser(QueueList<long>* firstDose, QueueList<long>* secondDose, List<User>* users)
{
	long id;
	cout << "\tEnter National ID: ";
	cin >> id;
	cout << endl;

	try
	{
		users->getUserByID(id)->printUser();
		cout << "Are you sure you want to delete this user? [y/n]: ";
		string x;
		cin >> x;
		if (x._Equal("Y") || x._Equal("y"))
		{
			User* u = users->removeUserByID(id);
			if (u->remainingDoses == 1)
				firstDose->removeID(id);
			else if (u->remainingDoses == 0 && !u->isvaxed)
				secondDose->removeID(id);
			cout << "\t\tUser successfully removed!\n\n";
		}
		else
		{
			cout << "\t\tAborted\n";
		}
	}
	catch (runtime_error e)
	{
		cout << "\t" << e.what() << endl;
	}
}

void AdminControl::deleteUser(QueueList<long>* firstDose, QueueList<long>* secondDose, List<User>* users, long id)
{
	try
	{
		users->getUserByID(id)->printUser();
		cout << "Are you sure you want to delete? [y/n]: ";
		string x;
		cin >> x;
		if (x._Equal("Y") || x._Equal("y"))
		{
			User* u = users->removeUserByID(id);
			if (u->remainingDoses == 1)
				firstDose->removeID(id);
			else if (u->remainingDoses == 0 && !u->isvaxed)
				secondDose->removeID(id);
			cout << "\t\tUser successfully removed!\n\n";
		}
		else
		{
			cout << "\t\tAborted\n";
		}
	}
	catch (runtime_error e)
	{
		cout << "\t" << e.what() << endl;
	}
}

void AdminControl::viewDoseQueue(QueueList<long>* firstDose, QueueList<long>* secondDose, List<User>* users)
{
	int doseNum;
	cout << "\tSelect which dose to administer [1/2]: ";
	cin >> doseNum;

	if (doseNum == 1)
	{
		cout << "\t Name \t\t ID\n";
		User* u;
		for (int i = 0; i < firstDose->length(); i++)
		{
			u = users->getUserByID(*firstDose->getByIndex(i));
			cout << "\t " << u->name << "\t " << u->userId << endl;
		}
		cout << "\n\n";
	}
	else if (doseNum == 2)
	{
		cout << "\t Name \t\t ID\n";
		User* u;
		for (int i = 0; i < secondDose->length(); i++)
		{
			u = users->getUserByID(*secondDose->getByIndex(i));
			cout << "\t " << u->name << "\t " << u->userId << endl;
		}
		cout << "\n\n";
	}
	else
	{
		cout << "\tError: Wrong dose number!\n";
		return;
	}
}

void AdminControl::percentageOfDose(List<User>* usersList)
{
	double first_dose = 0;
	double second_dose = 0;
	double Th_dose = 0;

	for (int i = 0; i < usersList->length(); i++) {

		User* p = usersList->getByIndex(i);

		if (p->remainingDoses == 1) {
			first_dose++;
		}
		else if (p->isvaxed) {
			second_dose++;

		}
		else if (p->remainingDoses == 2)
		{
			Th_dose++;
		}

	}

	double s = usersList->length();
	double sumofFirst = (first_dose / s) * 100;
	double sumofTH = (Th_dose / s) * 100;
	double sumofSecond = 100 - sumofFirst - sumofTH;

	cout << "Percentage of 1st Dose = " << sumofFirst << "%" << endl;
	cout << "Percentage of 2nd Dose = " << sumofSecond << "%" << endl;
	cout << "Percentage of unvaccinated = " << sumofTH << "%" << endl;
}

void AdminControl::percentageOfFemaleToMale(List<User>* usersList)
{
	double Fm = 0;
	double ma = 0;
	for (int i = 0; i < usersList->length(); i++)
	{
		User* x = usersList->getByIndex(i);
		if (x->gender == 'f' || x->gender == 'F')
		{
			Fm = Fm + 1;
		}
		else
		{
			ma = ma + 1;
		}
	}
	double s = usersList->length();
	double sumofMale = (ma / s) * 100;
	double sumofFmal = 100 - sumofMale;

	cout << "percentage of males :" << sumofMale << "%" << "\n";
	cout << "percentage of females :" << sumofFmal << "%" << "\n";
}

void AdminControl::administerVaccine(QueueList<long>* firstDose, QueueList<long>* secondDose, List<User>* users)
{
	int doseNum;
	cout << "\tSelect which dose to administer [1/2]: ";
	cin >> doseNum;

	if (doseNum == 1)
	{
		long id = *firstDose->dequeue();
		User* user = users->getUserByID(id);
		user->bookVaccine(firstDose, secondDose);
	}
	else if (doseNum == 2)
	{
		long id = *secondDose->dequeue();
		User* user = users->getUserByID(id);
		user->isvaxed = true;
	}
	else
	{
		cout << "\tError: Wrong dose number!\n";
		return;
	}
	cout << "\tDose administered successfully!\n";
}