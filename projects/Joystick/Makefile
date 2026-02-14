.PHONY: copy-libs

copy-libs:
	rm -rf lib

	mkdir -p lib/system/timer
	cp -r ../../libs/system/timer/* lib/system/timer

	mkdir -p lib/input/joystick
	cp -r ../../libs/input/joystick/* lib/input/joystick

	mkdir -p lib/communication/radio_transmitter
	cp -r ../../libs/communication/radio_transmitter/* lib/communication/radio_transmitter/

	rm -rf lib/motors/stepper_motor
	mkdir -p lib/motors/stepper_motor
	cp -r ../../libs/motors/stepper_motor/* lib/motors/stepper_motor/

	cp ../../libs/input/command_handler.h lib/input/command_handler.h
	cp ../../libs/system/directions.h lib/system/directions.h
