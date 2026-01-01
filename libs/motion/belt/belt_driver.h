#ifndef BELT_DRIVER_H
#define BELT_DRIVER_H

#include "belt_limiter.h"
#include "../../logic/limit_switch/limit_reached_command.h"
#include "../../system/timer/timer_handler.h"
#include "../../system/timer/timer_control.h"
#include "../../motors/stepper_motor/stepper_motor_driver.h"
#include "../../motors/stepper_motor/stepper_motor_timer_adapter.h"

class BeltDriver : public TimerHandler {
private:
    BeltLimiter& beltLimiter;
    LimitReachedCommand& command;
    TimerControl& timerControl;
    StepperMotorDriver* stepperMotor;
    StepperMotorTimerAdapter* stepperAdapter;
    bool isRunning;

public:
    BeltDriver(BeltLimiter& beltLimiter, LimitReachedCommand& command, TimerControl& timerControl, StepperMotorDriver* stepperMotor);
    ~BeltDriver();
    
    void moveLeft();
    void moveRight();
    void handleTimerEvent() override;
};

#endif // BELT_DRIVER_H
