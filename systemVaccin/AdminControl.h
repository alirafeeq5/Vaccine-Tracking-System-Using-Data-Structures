#pragma once

#include <iostream>
#include "List.h"
#include "QueueList.h"
#include "User.h"
using namespace std;

class AdminControl
{
private:
	AdminControl() {}

public:
	static void viewSingleRecord(List<User>*);
	static void viewAllRecords(List<User>*);
	static void deleteUser(QueueList<long>*, QueueList<long>*, List<User>*);
	static void deleteUser(QueueList<long>*, QueueList<long>*, List<User>*, long);
	static void viewDoseQueue(QueueList<long>*, QueueList<long>*, List<User>*);
	static void administerVaccine(QueueList<long>*, QueueList<long>*, List<User>*);
	static void percentageOfFemaleToMale(List<User>*);
	static void percentageOfDose(List<User>*);

};