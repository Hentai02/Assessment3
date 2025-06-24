#pragma once
#include <vector>

// forward declare the RobotWorker class
class RobotWorker;

class AbstractRobotDatabaseLoader {
public:
	// initialise the database connection
	virtual void initialiseConnection() = 0;

	// load robots from that database.
	// This method should allocated dynamic (i.e. new-ed) robot workers into
	// the vector reference. The function caller must take responsibilty for
	// cleaning up the memory.
	virtual void loadRobots(std::vector<RobotWorker*>& robotIn) = 0;

	virtual void closeConnection() = 0;
};