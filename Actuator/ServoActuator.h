#ifndef SERVO_ACTUATOR_H
#define SERVO_ACTUATOR_H

#include <ESP32Servo.h>

class ServoActuator
{
private:
  Servo servo;
  int servoPin;
  int currentAngle;
  int targetAngle;
  int delayBetweenSteps;

public:
  ServoActuator(int pin, int initialAngle, int delayTime)
  {
    servoPin = pin;
    currentAngle = initialAngle;
    targetAngle = initialAngle;
    delayBetweenSteps = delayTime;
  }

  void initialize()
  {
    servo.attach(servoPin);
    servo.write(currentAngle);
  }

  void moveToTarget()
  {
    if (currentAngle < targetAngle)
    {
      currentAngle++;
      servo.write(currentAngle);
      delay(delayBetweenSteps);
    }
    else if (currentAngle > targetAngle)
    {
      currentAngle--;
      servo.write(currentAngle);
      delay(delayBetweenSteps);
    }
  }

  void setTargetAngle(int angle)
  {
    if (angle >= 0 && angle <= 180)
      targetAngle = angle;
  }
};

#endif
