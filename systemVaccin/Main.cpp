#include <iostream>
#include <fstream>

#include "QueueList.h"
#include "List.h"
#include "User.h"
#include "AdminControl.h"
using namespace std;

void createNewRecord();
void SignIn();
void userMenu();
void adminMenu();

QueueList<long>* firstDoseQueue = new QueueList<long>();
QueueList<long>* secondDoseQueue = new QueueList<long>();
List<User>* usersList = new List<User>();

User* currentUser;
User* tempUser;

int main()
{	
	int choice = -1;
	do
	{
		cout << "\n\t----------------------" << endl;
		cout << "\n\t MAIN MENU" << endl;
		cout << "\n\t1. Register." << endl;
		cout << "\n\t2. Log In." << endl;
		cout << "\n\tEnter 0 to exit." << endl;
		cout << "\n\t----------------------" << endl;
		cout << "\n\t Enter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			createNewRecord();
			break;
		case 2:
			SignIn();
			break;
		case 0:
			cout << "\n\t\tThank you for using App." << endl;
			break;
		default:
			cout << "\n\t\tThe choice you entered was not valid," << endl;
			cout << "\n\t\tplease enter a valid option." << endl;
			break;
		}
	} while (choice);

	
	return 0;
}



void createNewRecord()
{
	string name, gov;
	int age;
	long id;
	char gender;
	cout << "\n\t Enter your name: ";
	cin >> name;

	do
	{
		cout << "\n\t Enter your national ID: ";
		cin >> id;

		try
		{
			usersList->getUserByID(id);
			cout << "\n\t Error: ID already registered!\n";
		}
		catch (runtime_error e)
		{
			break;
		}

	} while (true);

	cout << "\n\t Enter your governorate: ";
	cin >> gov;
	
	do 
	{
		cout << "\n\t Enter gender: (m/f)";
		cin >> gender;
		if (gender != 'm' && gender != 'f')
			cout << "\n\t\tInvalid Input!";
		else
			break;
	} while (true);


	cout << "\n\t Enter your age: ";
	cin >> age;
	string pass, pass2;
	do
	{ 
		cout << "\n\t Set your password: ";
		cin >> pass;
		cout << "\n\t Retype password: ";
		cin >> pass2;
		if (pass != pass2)
			cout << "\n\t Password does not match! Set up your password again!";
	} while (pass != pass2);

	int numDoses = 3;
	do
	{
		cout << "\n\t How many doses have you taken? (0 or 1 or 2): ";
		cin >> numDoses;
	} while (numDoses > 2 || numDoses < 0);
	bool vaxed = !(numDoses == 0 || numDoses == 1);
	
	tempUser = new User(name, id, pass, gender, age, "Egypt", gov, vaxed, 2 - numDoses);
	usersList->add(tempUser);

	cout << "\n\t\tUser registered successfully" << endl;
}

void SignIn()
{
	long userId;
	string pass;
	cout << "\n\t Enter your National id :";
	cin >> userId;

	
	cout << "\n\t Enter your password :";
	cin >> pass;

	if (userId == 123 && pass == "admin")
	{
		system("CLS");
		adminMenu();
	}
	else
	{
		try
		{
			tempUser = usersList->getUserByID(userId);
		}
		catch (runtime_error e)
		{
			cout << "\t" << e.what() << endl;
			return;
		}
		if (pass != tempUser->password)
		{
			cout << "\n\t\tIncorrect password." << endl;
		}
		else 
		{
			currentUser = tempUser;
			cout << "\n\tLogged in successfully." << endl;
			userMenu();
		}
	}
}

void userMenu()
{
	cout << "\n\t Hello User\n";
	cout << "\n\t Choose what you would like to do\n";
	cout << "\n\t 1.View data\n\t 2.Delete user\n\t 3.Edit user\n\t 4.Register for vaccine \n\t 5.Log out\n ";
	int choice = -1;
	do
	{
		
		cin >> choice;
		switch (choice)
		{
		case 1:
			currentUser->printUser();
			break;
		case 2:
			AdminControl::deleteUser(firstDoseQueue, secondDoseQueue, usersList, currentUser->userId);
			break;
		case 3:
			currentUser->editUser();
			break;
		case 4:
			currentUser->bookVaccine(firstDoseQueue, secondDoseQueue);
			break;
		case 5:
			system("CLS");
			main();
			break;
		default:
			cout << "\n\t\tThe choice you entered was not valid," << endl;
			cout << "\n\t\tplease enter a valid option." << endl;
			break;
		}
	} while (choice);
}

void adminMenu()
{
	system("CLS");
	cout << "\n\tHello admin";
	cout << "\n\t choose what you would like to do\n";
	cout << "\n\t 1.view data\n\t 2.delete record\n\t 3.statistics \n\t 4.Administer Vaccine\n\t 5.View Vaccine Queues\n\t 6.View All Records \n\t 7.Exit\n";
	int choice = -1;
	do
	{

		cin >> choice;
		switch (choice)
		{
		case 1:
			AdminControl::viewSingleRecord(usersList);
			break;
		case 2:
			AdminControl::deleteUser(firstDoseQueue, secondDoseQueue, usersList);
			break;
		case 3:
			AdminControl::percentageOfFemaleToMale(usersList);
			cout << "----------------------------------\n";
			AdminControl::percentageOfDose(usersList);
			break;
		case 4:
			AdminControl::administerVaccine(firstDoseQueue, secondDoseQueue, usersList);
			break;
		case 5:
			AdminControl::viewDoseQueue(firstDoseQueue, secondDoseQueue, usersList);
			break;
		case 7:
			system("CLS");
			main();
			break;
		case 6:
			AdminControl::viewAllRecords(usersList);
			break;
		default:
			cout << "\n\t\tThe choice you entered was not valid," << endl;
			cout << "\n\t\tplease enter a valid option." << endl;
			break;
		}
	} while (choice);
}

