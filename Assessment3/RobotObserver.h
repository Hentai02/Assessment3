#pragma once

#include "PriorityLevel.h"

// Forward declaration
class RobotWorker;

// Abstract observer interface
class RobotObserver {
public:
    virtual ~RobotObserver() = default;
    virtual void onPriorityChanged(RobotWorker* robot, PriorityLevel oldLevel, PriorityLevel newLevel) = 0;
};

// Observable interface for robots
class RobotObservable {
public:
    virtual ~RobotObservable() = default;
    virtual void addObserver(RobotObserver* observer) = 0;
    virtual void removeObserver(RobotObserver* observer) = 0;
    virtual void notifyObservers(PriorityLevel oldLevel, PriorityLevel newLevel) = 0;
};

// Concrete observer for factory alerts
class FactoryAlertObserver : public RobotObserver {
public:
    FactoryAlertObserver();
    virtual ~FactoryAlertObserver();

    virtual void onPriorityChanged(RobotWorker* robot, PriorityLevel oldLevel, PriorityLevel newLevel) override;

private:
    class FactoryAlertSystemFacade* _factoryFacade;
};

// Concrete observer for charger notifications
class ChargerNotificationObserver : public RobotObserver {
public:
    ChargerNotificationObserver();
    virtual ~ChargerNotificationObserver();

    virtual void onPriorityChanged(RobotWorker* robot, PriorityLevel oldLevel, PriorityLevel newLevel) override;

private:
    class ChargerNotificationSystemFacade* _chargerFacade;
};