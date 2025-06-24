// PriorityCalculationStrategy.cpp - Implementation
#include "PriorityCalculationStrategy.h"
#include "Vitals.h"
#include "RobotWorker.h"
#include <memory>

// SupplyMaterialsStrategy implementation
PriorityLevel SupplyMaterialsStrategy::calculatePriority(const Vitals* vitals) const {
    // Any Power<10 RED, Pressure<20 RED, Connection<5 RED (universal rules)
    if (vitals->POWER() < 10 || vitals->PRESSURE() < 20 || vitals->CONNECTION() < 5) {
        return PriorityLevel::Red;
    }

    // Task-specific rules for Supply Materials
    if (vitals->POWER() < 30 || vitals->PRESSURE() < 30) {
        return PriorityLevel::Orange;
    }

    if (vitals->CONNECTION() < 20) {
        return PriorityLevel::Yellow;
    }

    return PriorityLevel::Green;
}

// MoveToStorageStrategy implementation
PriorityLevel MoveToStorageStrategy::calculatePriority(const Vitals* vitals) const {
    // Any Power<10 RED, Pressure<20 RED, Connection<5 RED (universal rules)
    if (vitals->POWER() < 10 || vitals->PRESSURE() < 20 || vitals->CONNECTION() < 5) {
        return PriorityLevel::Red;
    }

    // Task-specific rules for Move to Storage
    if (vitals->POWER() < 40 || vitals->PRESSURE() < 20) {
        return PriorityLevel::Orange;
    }

    return PriorityLevel::Green;
}

// MoveToDeliveryStrategy implementation
PriorityLevel MoveToDeliveryStrategy::calculatePriority(const Vitals* vitals) const {
    // Any Power<10 RED, Pressure<20 RED, Connection<5 RED (universal rules)
    if (vitals->POWER() < 10 || vitals->PRESSURE() < 20 || vitals->CONNECTION() < 5) {
        return PriorityLevel::Red;
    }

    // Task-specific rules for Move to Delivery
    if (vitals->POWER() < 10) {  // This is already covered by universal rules, but kept for clarity
        return PriorityLevel::Orange;
    }

    return PriorityLevel::Green;
}

// Factory implementation
std::unique_ptr<PriorityCalculationStrategy> PriorityStrategyFactory::createStrategy(const std::string& taskName) {
    if (taskName == "Supply materials for assembly") {
        return std::make_unique<SupplyMaterialsStrategy>();
    }
    else if (taskName == "Move new item to storage") {
        return std::make_unique<MoveToStorageStrategy>();
    }
    else if (taskName == "Move item from storage to delivery system") {
        return std::make_unique<MoveToDeliveryStrategy>();
    }

    // Default to supply materials strategy if task not recognized
    return std::make_unique<SupplyMaterialsStrategy>();
}