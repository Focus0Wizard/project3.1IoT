#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

class UltrasonicSensor
{
private:
  int trigPin;
  int echoPin;
  long duration;
  float distance;

public:
  UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo), duration(0), distance(0) {}

  void initialize()
  {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  float readDistance()
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 25000);

    if (duration == 0)
    {
      Serial.println("Timeout out of range");
      return -1;
    }

    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;
  }
};

#endif
