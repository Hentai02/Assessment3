#include "RobotFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "RobotWorker.h"
#include "Vitals.h"

using namespace std;


std::vector<RobotWorker*> RobotFileLoader::loadRobotFile(const std::string& file)
{
    vector<RobotWorker*> robots{};

    std::ifstream inFile(file);
    if (inFile.is_open()) {
        std::string line;

        // Skip header line if it exists
        if (std::getline(inFile, line)) {
            // Check if this is a header line (contains non-numeric characters in expected positions)
            if (line.find("identifier") != std::string::npos ||
                line.find("classCode") != std::string::npos) {
                // This is a header, continue to next line
            }
            else {
                // This is data, process it
                processRobotLine(line, robots);
            }
        }

        // Process remaining lines
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                processRobotLine(line, robots);
            }
        }
        inFile.close();
    }
    else {
        std::cerr << "Unable to open file: " << file << std::endl;
    }

    return robots;
}

void RobotFileLoader::processRobotLine(const std::string& line, std::vector<RobotWorker*>& robots)
{
    std::istringstream ss(line);
    std::string identifier, classCode, dateStr, task;

    // Parse comma-separated values
    if (std::getline(ss, identifier, ',') &&
        std::getline(ss, classCode, ',') &&
        std::getline(ss, dateStr, ',') &&
        std::getline(ss, task, ',')) {

        // Trim whitespace
        identifier = trim(identifier);
        classCode = trim(classCode);
        dateStr = trim(dateStr);
        task = trim(task);

        // Parse the manufacturing date
        std::tm manufactureDate = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&manufactureDate, "%d-%m-%Y");

        if (!dateStream.fail()) {
            // Create new robot worker
            RobotWorker* robot = new RobotWorker(identifier, classCode, manufactureDate);

            // Add task
            robot->addTask(task);

            // Parse vitals if they exist on the same line
            std::string vitalsStr;
            if (std::getline(ss, vitalsStr)) {
                parseVitals(vitalsStr, robot);
            }

            robots.push_back(robot);
        }
        else {
            std::cerr << "Failed to parse date: " << dateStr << std::endl;
        }
    }
}

void RobotFileLoader::parseVitals(const std::string& vitalsStr, RobotWorker* robot)
{
    if (vitalsStr.empty()) return;

    std::istringstream vitalsStream(vitalsStr);
    std::string vitalRecord;

    // Parse multiple vital records separated by semicolons
    while (std::getline(vitalsStream, vitalRecord, ';')) {
        if (!vitalRecord.empty()) {
            std::istringstream recordStream(vitalRecord);
            std::string powerStr, pressureStr, connectionStr;

            if (std::getline(recordStream, powerStr, ',') &&
                std::getline(recordStream, pressureStr, ',') &&
                std::getline(recordStream, connectionStr, ',')) {

                try {
                    float power = std::stof(trim(powerStr));
                    int pressure = std::stoi(trim(pressureStr));
                    int connection = std::stoi(trim(connectionStr));

                    Vitals* vitals = new Vitals(power, pressure, connection);
                    robot->addVitals(vitals);
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing vitals: " << e.what() << std::endl;
                }
            }
        }
    }
}

std::string RobotFileLoader::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";

    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

