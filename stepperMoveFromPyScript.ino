#include <Stepper.h>

// Change these values based on your stepper's specific requirements
const int stepsPerRevolution = 2048; // Change this to fit your stepper motor

// Initialize the stepper library on pins 8 through 11 for one motor and pins 4 through 7 for the other:
Stepper myStepperX(stepsPerRevolution, 5, 6, 7, 8);
Stepper myStepperY(stepsPerRevolution, 9, 10, 11, 12);

void setup() {
  // Set the speed (RPMs):
  myStepperX.setSpeed(12); // Adjust this value to control the speed of the X-axis motor
  myStepperY.setSpeed(12); // Adjust this value to control the speed of the Y-axis motor
  
  // Start serial communication:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case 'X':
        // Move X-axis motor
        myStepperX.step(stepsPerRevolution / 64); // Adjust step size as needed
        break;
      case 'Y':
        // Move Y-axis motor
        myStepperY.step(stepsPerRevolution / 64); // Adjust step size as needed
        break;
      // Add more cases as needed for direction or finer control
    }
  }
}
