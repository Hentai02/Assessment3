#pragma once

#include "AbstractRobotDatabaseLoader.h"
#include <vector>
#include <memory>

class CompositeRobotLoader : public AbstractRobotDatabaseLoader {
public:
    CompositeRobotLoader();
    virtual ~CompositeRobotLoader();

    // Add a loader to the composite
    void addLoader(std::unique_ptr<AbstractRobotDatabaseLoader> loader);

    // Remove all loaders
    void clearLoaders();

    // Inherited via AbstractRobotDatabaseLoader
    virtual void initialiseConnection() override;
    virtual void loadRobots(std::vector<RobotWorker*>& robotIn) override;
    virtual void closeConnection() override;

private:
    std::vector<std::unique_ptr<AbstractRobotDatabaseLoader>> _loaders;
};