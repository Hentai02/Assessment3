#pragma once

#include "RobotWorker.h"

class ChargerNotificationSystemFacade
{

public:
	ChargerNotificationSystemFacade();
	virtual ~ChargerNotificationSystemFacade();

	void sendChargerNotificationForRobot(RobotWorker* r);
};

