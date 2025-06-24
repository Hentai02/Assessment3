#include "ChargerNotificationSystemFacade.h"

#include <iostream>


ChargerNotificationSystemFacade::ChargerNotificationSystemFacade()
{ }

ChargerNotificationSystemFacade::~ChargerNotificationSystemFacade()
{ }

void ChargerNotificationSystemFacade::sendChargerNotificationForRobot(RobotWorker* r)
{
	if (r->priorityLevel() > PriorityLevel::Orange) {
		// A mocked alert message. 
		std::cout << std::endl;
		std::cout << "This is an notification to the Charger:" << std::endl;
		std::cout << "Robot: " << r->humanReadableID() << " needs to recharge" << std::endl;
	}
}
