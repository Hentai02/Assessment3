#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

// forward declare several classes
class AbstractRobotDatabaseLoader;
class FactoryAlertSystemFacade;
class ChargerNotificationSystemFacade;
class RobotWorker;

class RobotManagementSystem
{
public:

	RobotManagementSystem();
	~RobotManagementSystem();

	// initialise the robot records
	void init();
	void run();

	// ask the user for a robot and vitals and add those vitals to the robot
	void addVitalsRecord();

	void printWelcomeMessage() const;
	void printMainMenu() const;
	void printRobots() const;

protected:
	std::vector<RobotWorker*> _robots;
	std::map<std::string, RobotWorker*> _robotLookup;

	std::unique_ptr<FactoryAlertSystemFacade> _factoryAlertSystemFacade;
	std::unique_ptr<ChargerNotificationSystemFacade> _chargerNotificationSystemFacade;

	std::unique_ptr<AbstractRobotDatabaseLoader> _robotDatabaseLoader;
};



