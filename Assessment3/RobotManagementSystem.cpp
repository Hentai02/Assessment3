#include "RobotManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>

#include "RobotWorker.h"
#include "RobotDatabaseLoader.h"
#include "Vitals.h"

#include "ChargerNotificationSystemFacade.h"
#include "FactoryAlertSystemFacade.h"

using namespace std;

RobotManagementSystem::RobotManagementSystem() :
	_robotDatabaseLoader(std::make_unique<RobotDatabaseLoader>()),
	_factoryAlertSystemFacade(std::make_unique<FactoryAlertSystemFacade>()),
	_chargerNotificationSystemFacade(std::make_unique<ChargerNotificationSystemFacade>())
{
	_robotDatabaseLoader->initialiseConnection();
}

RobotManagementSystem::~RobotManagementSystem()
{
	_robotDatabaseLoader->closeConnection();

	// clear robot memory
	for (RobotWorker* p : _robots) {
		delete p;
	}
}

void RobotManagementSystem::init()
{
	_robotDatabaseLoader->loadRobots(_robots);
	for (RobotWorker* p : _robots) {
		_robotLookup[p->uid()] = p;
	}

	for (RobotWorker* p : _robots) {
		// TODO: do any processing you need here
	}
}

void RobotManagementSystem::run()
{
	printWelcomeMessage();

	bool running = true;
	while (running) {
		printMainMenu();
		int option = 0;
		cin >> option;

		// handle basic errors
		if (cin.bad()) {
			cin.clear();
			cin.ignore();
			continue;
		}

		// switch based on the selected option
		switch (option) {
		case 1:
			printRobots();
			break;
		case 2:
			addVitalsRecord();
			break;
		case 3:
			running = false;
			break;
		}
	}
}

void RobotManagementSystem::addVitalsRecord()
{
	cout << "Robots" << endl;
	printRobots();
	cout << endl;
	cout << "Enter the robot ID to enter vitals for > ";

	string pid{ "" };
	cin >> pid;
	if (_robotLookup.count(pid)) {
		float power;
		int pressure;
		int connection;

		cout << "enter battery power: ";
		cin >> power;
		cout << "enter blood pressure: ";
		cin >> pressure;
		cout << "enter connection strength: ";
		cin >> connection;

		Vitals* v = new Vitals(power, pressure, connection);
		_robotLookup[pid]->addVitals(v);
	}
	else {
		cout << "Robot not found" << endl;
	}
}

void RobotManagementSystem::printWelcomeMessage() const
{
	cout << "WELCOME TO ROBOTCO 3000" << endl;
	cout << "------------------------" << endl;
}

void RobotManagementSystem::printMainMenu() const
{
	cout << endl << "Select an option:" << endl;
	cout << "1. List robots" << endl;
	cout << "2. Add current vitals" << endl;
	cout << "3. Quit" << endl;
	cout << "> ";
}

void RobotManagementSystem::printRobots() const
{
	for (RobotWorker* p : _robots) {
		std::cout << *p << std::endl;
	}
}

