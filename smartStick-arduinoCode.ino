// Define pin numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int passBuzzer = 13;

// Define variables
long duration;
int distance;
const int thresholdDistance = 10;      // distance in cm to trigger active buzzer
const int passThresholdDistance = 40; // distance for passive buzzer

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(passBuzzer, OUTPUT);
  Serial.begin(9600); // Start Serial Monitor (terminal)
}

void loop() {
  // Trigger the ultrasonic pulse (sensor)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration and calculate distance in cm
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Control buzzers based on distance
  if (distance > 0 && distance <= thresholdDistance) {
    digitalWrite(buzzer, HIGH);
    noTone(passBuzzer);
  } else if (distance > thresholdDistance && distance <= passThresholdDistance) {
    digitalWrite(buzzer, LOW);
    tone(passBuzzer, 1000); // 1kHz tone for passive buzzer
  } else {
    digitalWrite(buzzer, LOW);
    noTone(passBuzzer);
  }

  // Output distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);
}
