#include "RobotWorker.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Vitals.h"
#include "PriorityCalculationStrategy.h"

using namespace std;

const std::string Tasks::SUPPLY_MATERIALS = "Supply materials for assembly";
const std::string Tasks::MOVE_TO_STORAGE = "Move new item to storage";
const std::string Tasks::MOVE_TO_DELIVERY = "Move item from storage to delivery system";


RobotWorker::RobotWorker(const std::string& identifier, const std::string& classCode, std::tm manufactureDate) :
	Robot(identifier, classCode, manufactureDate),
	_priorityLevel(PriorityLevel::Green)
{
}

RobotWorker::~RobotWorker() {
	// Clean up vitals
	for (const Vitals* vital : _vitals) {
		delete vital;
	}
}

int RobotWorker::age() const
{
	// an inaccurate age estimate but fine for assignment purposes
	return 2025 - (1900 + _manufactureDate.tm_year);
}

std::string RobotWorker::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_classCode.at(0))
		<< (char)std::tolower(_identifier.at(0))
		<< std::setfill('0') << std::setw(2) << (_manufactureDate.tm_mon + 1)
		<< _manufactureDate.tm_year;
	return ss.str();
}

std::string RobotWorker::humanReadableID() const
{
	return "" + _classCode + ", " + _identifier + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const RobotWorker& p)
{
	os << p.uid() << "|" << p._classCode << "," << p._identifier << "|" << std::put_time(&p._manufactureDate, "%d-%m-%Y") << "|" << p.primaryTask();

	os << "|";
	for (int i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

void RobotWorker::addTask(const std::string& task)
{
	_tasks.push_back(task);
	updatePriorityStrategy();
}

const std::string& RobotWorker::primaryTask() const
{
	return _tasks.front();
}

void RobotWorker::addVitals(const Vitals* v)
{
	_vitals.push_back(v);
	// Calculate priority for newly added vitals only (not historical data)
	calculateAndUpdatePriority();
}

const std::vector<const Vitals*> RobotWorker::vitals() const
{
	return _vitals;
}

void RobotWorker::setPriorityLevel(PriorityLevel level)
{
	PriorityLevel oldLevel = _priorityLevel;
	_priorityLevel = level;

	if (_priorityLevel > PriorityLevel::Green) {
		cout << "Robot Worker: " << humanReadableID() << "has a priority level: ";
		switch (_priorityLevel) {
		case PriorityLevel::Yellow:
			cout << "Yellow";
			break;
		case PriorityLevel::Orange:
			cout << "Orange";
			break;
		case PriorityLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;
	}
}

	// Notify observers of priority change
	if (oldLevel != _priorityLevel) {
		notifyObservers(oldLevel, _priorityLevel);
	}
	void RobotWorker::addObserver(RobotObserver * observer)
	{
		if (observer && std::find(_observers.begin(), _observers.end(), observer) == _observers.end()) {
			_observers.push_back(observer);
		}
	}

	void RobotWorker::removeObserver(RobotObserver * observer)
	{
		_observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
	}

	void RobotWorker::notifyObservers(PriorityLevel oldLevel, PriorityLevel newLevel)
	{
		for (RobotObserver* observer : _observers) {
			observer->onPriorityChanged(this, oldLevel, newLevel);
		}
	}

	void RobotWorker::calculateAndUpdatePriority()
	{
		if (_vitals.empty() || !_priorityStrategy) {
			return;
		}

		// Use the most recent vitals for priority calculation
		const Vitals* latestVitals = _vitals.back();
		PriorityLevel newPriority = _priorityStrategy->calculatePriority(latestVitals);

		setPriorityLevel(newPriority);
	}

	void RobotWorker::updatePriorityStrategy()
	{
		if (!_tasks.empty()) {
			_priorityStrategy = PriorityStrategyFactory::createStrategy(primaryTask());
		}
	}

