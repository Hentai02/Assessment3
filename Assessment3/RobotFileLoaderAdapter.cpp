#include "RobotFileLoaderAdapter.h"
#include <iostream>

RobotFileLoaderAdapter::RobotFileLoaderAdapter(const std::string& filename)
    : _filename(filename), _connectionInitialized(false)
{
}

RobotFileLoaderAdapter::~RobotFileLoaderAdapter()
{
    if (_connectionInitialized) {
        closeConnection();
    }
}

void RobotFileLoaderAdapter::initialiseConnection()
{
    // Simulate connection initialization for file loading
    std::cout << "Initializing file connection for: " << _filename << std::endl;
    _connectionInitialized = true;
}

void RobotFileLoaderAdapter::loadRobots(std::vector<RobotWorker*>& robotIn)
{
    if (!_connectionInitialized) {
        std::cerr << "Connection not initialized!" << std::endl;
        return;
    }

    // Use the file loader to get robots
    std::vector<RobotWorker*> fileRobots = _fileLoader.loadRobotFile(_filename);

    // Add them to the provided vector
    for (RobotWorker* robot : fileRobots) {
        robotIn.push_back(robot);
    }

    std::cout << "Loaded " << fileRobots.size() << " robots from file." << std::endl;
}

void RobotFileLoaderAdapter::closeConnection()
{
    // Simulate closing file connection
    std::cout << "Closing file connection." << std::endl;
    _connectionInitialized = false;
}