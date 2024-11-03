#include <AFMotor.h>
#include <Servo.h>

// Define motors
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);

// Define servo
Servo myServo;
int currentAngle = 90;  // Initial angle for the servo

// Define brake lights on PWM-compatible digital pins
const int brakeLight1 = 3;  // Update to a PWM-capable pin
const int brakeLight2 = 5;  // Update to a PWM-capable pin

// Brightness levels for the brake lights
const int brightLevel = 255;  // Full brightness
const int dimLevel = 50;      // Dim brightness

void setup() 
{
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Enter 'D' to rotate servo to 0, 'A' to 180.");
  Serial.println("Use '2F' for Motor 2 forward, '2B' backward, '2S' stop, and similarly for Motor 3.");

  // Attach servo to pin 10 (adjust as needed)
  myServo.attach(10);
  myServo.write(currentAngle);  // Start servo at 90 degrees

  // Set initial speed for motors
  motor2.setSpeed(255);
  motor3.setSpeed(255);

  // Set initial state for brake lights (dim)
  analogWrite(brakeLight1, dimLevel);
  analogWrite(brakeLight2, dimLevel);
}

void loop() 
{
  // Check for commands from the Serial Monitor
  if (Serial.available() > 0) 
  {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any leading or trailing whitespace

    if (command.equalsIgnoreCase("D")) 
    {
      moveToServoAngle(0);
      moveToServoAngle(90);  // Return to 90 degrees
    } 
    else if (command.equalsIgnoreCase("A")) 
    {
      moveToServoAngle(180);
      moveToServoAngle(90);  // Return to 90 degrees
    }
    else if (command.equalsIgnoreCase("2F")) 
    {
      Serial.println("Motor 2 forward");
      motor2.run(FORWARD);
      setBrakeLights(dimLevel);  // Set lights to dim when moving forward
    }
    else if (command.equalsIgnoreCase("2B")) 
    {
      Serial.println("Motor 2 backward");
      motor2.run(BACKWARD);
      setBrakeLights(brightLevel);  // Bright when moving backward
    }
    else if (command.equalsIgnoreCase("2S")) 
    {
      Serial.println("Motor 2 stopped");
      motor2.run(RELEASE);
      setBrakeLights(brightLevel);  // Bright when stopped
    }
    else if (command.equalsIgnoreCase("3F")) 
    {
      Serial.println("Motor 3 forward");
      motor3.run(FORWARD);
      setBrakeLights(dimLevel);  // Dim when moving forward
    }
    else if (command.equalsIgnoreCase("3B")) 
    {
      Serial.println("Motor 3 backward");
      motor3.run(BACKWARD);
      setBrakeLights(brightLevel);  // Bright when moving backward
    }
    else if (command.equalsIgnoreCase("3S")) 
    {
      Serial.println("Motor 3 stopped");
      motor3.run(RELEASE);
      setBrakeLights(brightLevel);  // Bright when stopped
    }
    else 
    {
      Serial.println("Invalid command. Try again.");
    }
  }
}

// Function to move servo slowly to a specified angle
void moveToServoAngle(int targetAngle) 
{
  if (currentAngle < targetAngle) 
  {
    for (int angle = currentAngle; angle <= targetAngle; angle++) 
    {
      myServo.write(angle);
      delay(15);
    }
  } 
  else 
  {
    for (int angle = currentAngle; angle >= targetAngle; angle--) 
    {
      myServo.write(angle);
      delay(15);
    }
  }

  currentAngle = targetAngle;  // Update the current angle
  Serial.print("Servo at ");
  Serial.print(targetAngle);
  Serial.println(" degrees");
}

// Function to control brake light brightness
void setBrakeLights(int brightness) 
{
  analogWrite(brakeLight1, brightness);
  analogWrite(brakeLight2, brightness);
}
