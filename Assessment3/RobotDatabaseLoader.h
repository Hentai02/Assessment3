#pragma once

#include "AbstractRobotDatabaseLoader.h"

// This is a simulated class. It does not really connect to the database, but
// for the sake of the assignment, pretend it does.
class RobotDatabaseLoader : public AbstractRobotDatabaseLoader {
public:

	// Inherited via AbstractRobotDatabaseLoader
	virtual void initialiseConnection() override;

	virtual void loadRobots(std::vector<RobotWorker*>& robotIn) override;

	virtual void closeConnection() override;

};


