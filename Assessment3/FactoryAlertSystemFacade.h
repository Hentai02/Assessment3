#pragma once
#include "RobotWorker.h"

class FactoryAlertSystemFacade
{
public:
	FactoryAlertSystemFacade();
	virtual ~FactoryAlertSystemFacade();

	void sendAlertForRobot(RobotWorker* r);
};

