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
	cp -r ../../libs/input/remote_control/* lib/input/remote_control/
	cp ../../libs/input/command_handler.h lib/input/command_handler.h
	cp ../../libs/system/directions.h lib/system/directions.h