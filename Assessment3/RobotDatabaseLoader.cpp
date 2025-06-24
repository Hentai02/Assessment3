#include "RobotDatabaseLoader.h"

#include <iomanip>
#include <sstream>

#include "RobotWorker.h"
#include "Vitals.h"


void RobotDatabaseLoader::initialiseConnection()
{
    // pretend this initialises a database connection
}

void RobotDatabaseLoader::loadRobots(std::vector<RobotWorker*>& robotIn) {

    // we simulate loading robots from a database here.

    // initialise a manufacturing date from a string. This code can be reused to when loading a manufacturing date from a file
    std::tm t{ };
    std::istringstream ss("18-02-2024");
    ss >> std::get_time(&t, "%d-%m-%Y");

    // push back a new robot
    RobotWorker* p = new RobotWorker("Roy", "2A", t);
    p->addTask(Tasks::MOVE_TO_STORAGE);

    Vitals* v = new Vitals(76.5f, 80, 60);
    p->addVitals(v);

    robotIn.push_back(p);

}

void RobotDatabaseLoader::closeConnection()
{
    // pretend this closes the database connection
}

