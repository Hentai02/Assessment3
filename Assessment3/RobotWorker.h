#pragma once
#include "Robot.h"

#include <memory>
#include <vector>

#include "PriorityLevel.h"
#include "RobotObserver.h"

// forward declare classes
class Vitals;
class PriorityCalculationStrategy;

class Tasks {
public:
	static const std::string SUPPLY_MATERIALS;
	static const std::string MOVE_TO_STORAGE;
	static const std::string MOVE_TO_DELIVERY;
};

class RobotWorker : public Robot,public RobotObservable {
public:

	RobotWorker(const std::string& identifier, const std::string& classCode, std::tm manufactureDate);
	~RobotWorker();  // Add destructor declaration

	// return a calculated age for the robot
	// this calculation is not accurate, but is suitable for assignment purposes
	int age() const;

	// return a "unique" ID generated for the robot
	// this id is generated purely from robot details, and as such may have collisions
	std::string uid() const;

	// returns a "nice" ID for humans to interpret: identifier, classCode (UID)
	std::string humanReadableID() const;

	// robots are assigned a task
	void addTask(const std::string& task);
	const std::string& primaryTask() const;

	// add a vitals measurements record to the robot
	void addVitals(const Vitals* v);
	const std::vector<const Vitals*> vitals() const;

	// robots have an priority level (green, yellow, orange, red) calculated from their task and vitals
	void setPriorityLevel(PriorityLevel level);
	const PriorityLevel priorityLevel() const { return _priorityLevel; }

	// Observer pattern methods
	virtual void addObserver(RobotObserver* observer) override;
	virtual void removeObserver(RobotObserver* observer) override;
	virtual void notifyObservers(PriorityLevel oldLevel, PriorityLevel newLevel) override;

private:
	void calculateAndUpdatePriority();
	void updatePriorityStrategy();


protected:
	std::vector<std::string> _tasks;
	std::vector<const Vitals*> _vitals;
	PriorityLevel _priorityLevel;

	// Strategy pattern
	std::unique_ptr<PriorityCalculationStrategy> _priorityStrategy;

	// Observer pattern
	std::vector<RobotObserver*> _observers;

	friend std::ostream& operator<<(std::ostream& os, const RobotWorker& p);
};

