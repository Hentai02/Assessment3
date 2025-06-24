#include "RobotObserver.h"
#include "RobotWorker.h"
#include "FactoryAlertSystemFacade.h"
#include "ChargerNotificationSystemFacade.h"

// FactoryAlertObserver implementation
FactoryAlertObserver::FactoryAlertObserver() {
    _factoryFacade = new FactoryAlertSystemFacade();
}

FactoryAlertObserver::~FactoryAlertObserver() {
    delete _factoryFacade;
}

void FactoryAlertObserver::onPriorityChanged(RobotWorker* robot, PriorityLevel oldLevel, PriorityLevel newLevel) {
    // Only send alert if the new level is Red
    if (newLevel == PriorityLevel::Red) {
        _factoryFacade->sendAlertForRobot(robot);
    }
}

// ChargerNotificationObserver implementation
ChargerNotificationObserver::ChargerNotificationObserver() {
    _chargerFacade = new ChargerNotificationSystemFacade();
}

ChargerNotificationObserver::~ChargerNotificationObserver() {
    delete _chargerFacade;
}

void ChargerNotificationObserver::onPriorityChanged(RobotWorker* robot, PriorityLevel oldLevel, PriorityLevel newLevel) {
    // Send notification for Orange and Red levels (as per ChargerNotificationSystemFacade logic)
    if (newLevel > PriorityLevel::Orange) {
        _chargerFacade->sendChargerNotificationForRobot(robot);
    }
}