#ifndef BELT_DRIVER_H
#define BELT_DRIVER_H

#include "belt_limiter.h"
#include "belt_driver_timer.h"
#include "../../system/timer/timer_handler.h"
#include "../../system/timer/timer_control.h"
#include "../../motors/stepper_motor/stepper_motor_driver.h"

class BeltDriver : public TimerHandler, StepperMotorDriver {
public:
	BeltDriver(int leftPin, int rightPin, TimerControl& timerControl, StepperMotorDriver& stepperMotor);
	~BeltDriver();

	void setDirection(uint8_t direction) override {
		stepperMotor.setDirection(direction);
	}

    uint8_t getDirection() override {
		return stepperMotor.getDirection();
	}

	bool isMovementBlocked();

	void high() override {
		stepperMotor.high();
	}

	void low() override {
		stepperMotor.low();
	}

	bool isRunning() override {
		return stepperMotor.isRunning();
	}

	void pulse() override;
	
	void setIsRunning(bool running) override {
		stepperMotor.setIsRunning(running);
	}

	void setSpeed(int speed) override {
		stepperMotor.setSpeed(speed);
	}

	int getSpeed() override {
		return stepperMotor.getSpeed();
	}
	
	int getDelay() override {
		return stepperMotor.getDelay();
	}

	void handleTimerEvent() override;
	StepperMotorDriver& getStepperMotor();

private:
  TimerControl& timerControl;
  StepperMotorDriver& stepperMotor;
  BeltLimiter beltLimiter;
  BeltDriverTimer beltDriverTimer;
};

#endif // BELT_DRIVER_H
