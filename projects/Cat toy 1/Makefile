.PHONY: copy-libs

copy-libs:
	rm -rf lib/motors/stepper_motor
	mkdir -p lib/motors/stepper_motor
	cp -r ../../libs/motors/stepper_motor/* lib/motors/stepper_motor/

	rm -rf lib/system/timer
	mkdir -p lib/system/timer
	cp -r ../../libs/system/timer/* lib/system/timer/

	rm -rf lib/input
	
	mkdir -p lib/input/remote_control
	cp ../../libs/input/remote_control/remote_control_timer_listener.h lib/input/remote_control/remote_control_timer_listener.h
	cp ../../libs/input/remote_control/remote_control_timer_listener.cpp lib/input/remote_control/remote_control_timer_listener.cpp
	cp ../../libs/input/remote_control/remote_control.cpp lib/input/remote_control/remote_control.cpp
	cp ../../libs/input/remote_control/remote_control.h lib/input/remote_control/remote_control.h
	cp ../../libs/input/command_handler.h lib/input/command_handler.h
	cp ../../libs/system/directions.h lib/system/directions.h

	mkdir -p lib/input/joystick
	cp ../../libs/input/joystick/joystick.cpp lib/input/joystick/joystick.cpp
	cp ../../libs/input/joystick/joystick.h lib/input/joystick/joystick.h
	cp ../../libs/input/joystick/joystick_command_handler.h lib/input/joystick/joystick_command_handler.h
	cp ../../libs/input/joystick/staged_joystick_manager.cpp lib/input/joystick/staged_joystick_manager.cpp
	cp ../../libs/input/joystick/staged_joystick_manager.h lib/input/joystick/staged_joystick_manager.h

	rm -rf lib/motion/belt
	mkdir -p lib/motion/belt
	cp ../../libs/motion/belt/belt_driver.cpp lib/motion/belt/
	cp ../../libs/motion/belt/belt_driver.h lib/motion/belt/
	cp ../../libs/motion/belt/belt_limiter.cpp lib/motion/belt/
	cp ../../libs/motion/belt/belt_limiter.h lib/motion/belt/
	cp ../../libs/motion/belt/belt_limiter_timer_adapter.cpp lib/motion/belt/
	cp ../../libs/motion/belt/belt_limiter_timer_adapter.h lib/motion/belt/
	cp ../../libs/motion/belt/belt_joystick_controller.cpp lib/motion/belt/
	cp ../../libs/motion/belt/belt_joystick_controller.h lib/motion/belt/
	
	rm -rf lib/logic/limit_switch
	mkdir -p lib/logic/limit_switch
	cp ../../libs/logic/limit_switch/limit_switch.cpp lib/logic/limit_switch/
	cp ../../libs/logic/limit_switch/limit_switch.h lib/logic/limit_switch/