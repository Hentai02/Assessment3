#pragma once

#include <string>
#include <vector>

// forward declare the RobotWorker class
class RobotWorker;

class RobotFileLoader
{
public:
	// loads a list of robots from a file and returns a vector of those robots
	std::vector<RobotWorker*> loadRobotFile(const std::string& file);


private:
	// Helper methods for parsing
	void processRobotLine(const std::string& line, std::vector<RobotWorker*>& robots);
	void parseVitals(const std::string& vitalsStr, RobotWorker* robot);
	std::string trim(const std::string& str);
};

