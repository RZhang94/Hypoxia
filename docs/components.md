For RH

## Key Components
- Arduino Uno/Nano: Contains the logic that drives the stepper motor. 
- DRV8825 Stepper Motor Driver: Connects the motor, power supply, input from arduino, outputs stepper motor commands. Set to 2.3 A, using the pot screw. 
- NEMA17 Stepper motor: Spins
- Hypoxia Device: Swaps the output airflow based on rotation of the input piece. Has a gear train that converts stepper motor rotation into input piece rotation. (NEMA_14t -> Gear1_24t/14t -> Gear2_28t/14t -> Input_59t = 14.4 ratio)
- Button: Activates the hpoxia timing
- Electroylitc Capacitor: smooths out the power for the stepper motor.

## Pinout Diagram
Refer to the diagrams:
# Arduino <=> DRV8825
Pin2 = DIR
Pin3 = STEP
GND1 = GND+M2+M1+M0+EN
3.3V = RST+SLP (parallel)

# Arduino <=> Button
PIN4 = Side1
GND2 = Side2

# DRV8825 <=> Stepper
Plug in the JST 1 way, if you don't like the initial direction you can rotate it 180.

# DRV8825 <=> 12V power supply
VMOT = +
GND = -

## Physical Connections/Tips
During assembly, put the input/retaining ring/output together first. M5 hardware
NEMA17 bolts into the square pattern, M3 hardware
Put in the gear train from the stepper motor side -> Input ring.
Should probably use grease for the whole assembly.
