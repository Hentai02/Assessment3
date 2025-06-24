#pragma once

#include <string>
#include <memory>
#include "PriorityLevel.h"

// Forward declarations
class Vitals;
class RobotWorker;

// Abstract strategy interface
class PriorityCalculationStrategy {
public:
    virtual ~PriorityCalculationStrategy() = default;
    virtual PriorityLevel calculatePriority(const Vitals* vitals) const = 0;
    virtual std::string getTaskName() const = 0;
};

// Concrete strategy for Supply Materials task
class SupplyMaterialsStrategy : public PriorityCalculationStrategy {
public:
    virtual PriorityLevel calculatePriority(const Vitals* vitals) const override;
    virtual std::string getTaskName() const override { return "Supply materials for assembly"; }
};

// Concrete strategy for Move to Storage task
class MoveToStorageStrategy : public PriorityCalculationStrategy {
public:
    virtual PriorityLevel calculatePriority(const Vitals* vitals) const override;
    virtual std::string getTaskName() const override { return "Move new item to storage"; }
};

// Concrete strategy for Move to Delivery task
class MoveToDeliveryStrategy : public PriorityCalculationStrategy {
public:
    virtual PriorityLevel calculatePriority(const Vitals* vitals) const override;
    virtual std::string getTaskName() const override { return "Move item from storage to delivery system"; }
};

// Factory class to create appropriate strategy
class PriorityStrategyFactory {
public:
    static std::unique_ptr<PriorityCalculationStrategy> createStrategy(const std::string& taskName);
};