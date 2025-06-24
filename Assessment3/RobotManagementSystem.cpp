#include "RobotManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>

#include "RobotWorker.h"
#include "RobotDatabaseLoader.h"
#include "RobotFileLoaderAdapter.h"
#include "CompositeRobotLoader.h"
#include "Vitals.h"

#include "ChargerNotificationSystemFacade.h"
#include "FactoryAlertSystemFacade.h"
#include "RobotObserver.h"

using namespace std;

RobotManagementSystem::RobotManagementSystem() :
	_factoryAlertSystemFacade(std::make_unique<FactoryAlertSystemFacade>()),
	_chargerNotificationSystemFacade(std::make_unique<ChargerNotificationSystemFacade>())
{
	// Create composite loader with both database and file loaders
	auto compositeLoader = std::make_unique<CompositeRobotLoader>();

	// Add database loader
	compositeLoader->addLoader(std::make_unique<RobotDatabaseLoader>());

	// Add file loader adapter
	compositeLoader->addLoader(std::make_unique<RobotFileLoaderAdapter>("robots.txt"));

	_robotDatabaseLoader = std::move(compositeLoader);

	// Initialize connection
	_robotDatabaseLoader->initialiseConnection();

	// Setup observers
	setupObservers();
}


RobotManagementSystem::~RobotManagementSystem()
{
	_robotDatabaseLoader->closeConnection();

	// clear robot memory
	for (RobotWorker* p : _robots) {
		delete p;
	}
}

void RobotManagementSystem::setupObservers()
{
	// Create and store observers
	_observers.push_back(std::make_unique<FactoryAlertObserver>());
	_observers.push_back(std::make_unique<ChargerNotificationObserver>());
}

void RobotManagementSystem::attachObserversToRobots()
{
	// Attach observers to all robots
	for (RobotWorker* robot : _robots) {
		for (auto& observer : _observers) {
			robot->addObserver(observer.get());
		}
	}
}

void RobotManagementSystem::init()
{
	_robotDatabaseLoader->loadRobots(_robots);
	for (RobotWorker* p : _robots) {
		_robotLookup[p->uid()] = p;
	}

	// Attach observers to all loaded robots
	attachObserversToRobots();

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

