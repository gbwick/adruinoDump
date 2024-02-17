#include <Stepper.h>

// Update this with the actual number of steps per full revolution
const int stepsPerRevolution = 2048; 

// Initialize the Stepper library on the pins it is connected to
Stepper myStepper(stepsPerRevolution, 9, 10, 11, 12);

void setup() {
  // Set the speed in RPMs (adjust this value to change the rotation speed)
  myStepper.setSpeed(12);
  
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  Serial.println("Moving 50% forward...");
  // Move the stepper 50% of a full rotation forward
  myStepper.step(stepsPerRevolution / 2);
  delay(500); // Short delay before moving back

  Serial.println("Moving 50% backward...");
  // Move the stepper 50% of a full rotation backward
  myStepper.step(-stepsPerRevolution / 2);
  delay(500); // Short delay before the next cycle

  // This loop will repeat indefinitely, moving the stepper motor back and forth
}
