
### A4988 Driver

#### how to set current limit

- check current limit of motor
- power the driver with arduino (vdd, ground)
- connect the other ground of the arduino board to the multimeter negativ terminal
- touch the potmeter on the driver with the
multimeters positive terminal
- use the calculation: I = V / (8 * R)

V: the limit the multimeter shows
R: driver dependent (e.g R100 on the board means 0.1 ohms)