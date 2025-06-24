#include "CompositeRobotLoader.h"
#include <iostream>

CompositeRobotLoader::CompositeRobotLoader()
{
}

CompositeRobotLoader::~CompositeRobotLoader()
{
    closeConnection();
}

void CompositeRobotLoader::addLoader(std::unique_ptr<AbstractRobotDatabaseLoader> loader)
{
    _loaders.push_back(std::move(loader));
}

void CompositeRobotLoader::clearLoaders()
{
    // Close all connections first
    for (auto& loader : _loaders) {
        loader->closeConnection();
    }
    _loaders.clear();
}

void CompositeRobotLoader::initialiseConnection()
{
    std::cout << "Initializing composite loader with " << _loaders.size() << " loaders." << std::endl;

    for (auto& loader : _loaders) {
        loader->initialiseConnection();
    }
}

void CompositeRobotLoader::loadRobots(std::vector<RobotWorker*>& robotIn)
{
    int totalLoaded = 0;

    for (auto& loader : _loaders) {
        size_t beforeSize = robotIn.size();
        loader->loadRobots(robotIn);
        size_t afterSize = robotIn.size();
        int loadedFromThis = afterSize - beforeSize;
        totalLoaded += loadedFromThis;

        std::cout << "Loaded " << loadedFromThis << " robots from loader." << std::endl;
    }

    std::cout << "Total robots loaded: " << totalLoaded << std::endl;
}

void CompositeRobotLoader::closeConnection()
{
    for (auto& loader : _loaders) {
        loader->closeConnection();
    }
}