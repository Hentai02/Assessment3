#include "FactoryAlertSystemFacade.h"

#include <iostream>


FactoryAlertSystemFacade::FactoryAlertSystemFacade()
{ }

FactoryAlertSystemFacade::~FactoryAlertSystemFacade()
{ }

void FactoryAlertSystemFacade::sendAlertForRobot(RobotWorker* r)
{
	if (r->priorityLevel() == PriorityLevel::Red) {
		// A mocked alert message. 
		std::cout << std::endl;
		std::cout << "This is an alert to the factory:" << std::endl;
		std::cout << "Robot: " << r->humanReadableID() << " has a critical priority level" << std::endl;
	}
}
