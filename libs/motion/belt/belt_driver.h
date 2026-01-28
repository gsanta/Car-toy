#ifndef BELT_DRIVER_H
#define BELT_DRIVER_H

#include "belt_limiter.h"
#include "belt_limiter_timer_adapter.h"
#include "../../system/timer/timer_handler.h"
#include "../../system/timer/timer_control.h"
#include "../../motors/stepper_motor/stepper_motor_driver.h"
#include "../../motors/stepper_motor/stepper_motor_timer_adapter.h"

class BeltDriver {
private:
    BeltLimiter beltLimiter;
    BeltLimiterTimerAdapter limiterAdapter;
    TimerControl& timerControl;
    StepperMotorDriver& stepperMotor;
    StepperMotorTimerAdapter stepperAdapter;
    bool isRunning;

public:
    BeltDriver(int leftPin, int rightPin, TimerControl& timerControl, StepperMotorDriver& stepperMotor);
    ~BeltDriver();

    void startMotor();
    void stopMotor();
    void moveLeft();
    void moveRight();
    bool getIsRunning() const;
    StepperMotorDriver& getStepperMotor();
};

#endif // BELT_DRIVER_H
