#pragma once

#include "AbstractRobotDatabaseLoader.h"
#include "RobotFileLoader.h"
#include <string>

class RobotFileLoaderAdapter : public AbstractRobotDatabaseLoader {
public:
    RobotFileLoaderAdapter(const std::string& filename);
    virtual ~RobotFileLoaderAdapter();

    // Inherited via AbstractRobotDatabaseLoader
    virtual void initialiseConnection() override;
    virtual void loadRobots(std::vector<RobotWorker*>& robotIn) override;
    virtual void closeConnection() override;

private:
    RobotFileLoader _fileLoader;
    std::string _filename;
    bool _connectionInitialized;
};