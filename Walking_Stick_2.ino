const int trigPinFront = 13;
const int echoPinFront = 12;

const int trigPinBottom = 11;
const int echoPinBottom = 10;

const int buzzerPin = 6;
const int motorPin = 5;

const int holeThreshold = 25;     // If bottom sensor detects more than this = hole
const int minDistanceStick = 10;  // Minimum distance (in cm) to detect the stick


void setup() {
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);

  pinMode(trigPinBottom, OUTPUT);
  pinMode(echoPinBottom, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(motorPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);  // Start the Serial Monitor at 9600 baud rate
}

void loop() {
  long frontDistance = getSmoothedDistance(trigPinFront, echoPinFront);
  long bottomDistance = getSmoothedDistance(trigPinBottom, echoPinBottom);

  // Print the distances to the Serial Monitor
  Serial.print("Front Distance: ");
  Serial.print(frontDistance);
  Serial.println(" cm, ");
  Serial.print("Bottom Distance: ");
  Serial.print(bottomDistance);
  Serial.println(" cm");

  bool holeDetected = (bottomDistance > holeThreshold);
  bool obstacleDetected = frontDistance < 50;

  if (holeDetected) {
    // Hole detected: Continuous buzzer sound
    tone(buzzerPin, 1000);        // Continuous tone for hole
    digitalWrite(motorPin, LOW);  // No vibration
  } else if (obstacleDetected) {
    // Obstacle detected: Beep pattern and vibration intensity
    int beeps = getBeepCount(frontDistance);
    for (int i = 0; i < beeps; i++) {
      tone(buzzerPin, 700, 100);
      delay(150);
    }
    noTone(buzzerPin);  // Stop tone after beeping

    int intensity = getVibrationIntensity(frontDistance);
    analogWrite(motorPin, intensity);
  } else {
    // No obstacle or hole
    noTone(buzzerPin);         // No sound when no hole and no obstacle
    analogWrite(motorPin, 0);  // No vibration
  }

  delay(50);  // Small delay between loops
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);  // Timeout after 30ms
  long distance = duration * 0.034 / 2;

  if (distance == 0) {
    distance = 999;  // Treat as no reading (far away)
  }

  return distance;
}

long getSmoothedDistance(int trigPin, int echoPin) {
  long sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += getDistance(trigPin, echoPin);
    delay(10);
  }
  return sum / 3;
}

int getBeepCount(long distance) {
  if (distance < 20) return 4;
  else if (distance < 30) return 3;
  else if (distance < 40) return 2;
  else if (distance < 50) return 1;
  else return 0;
}

int getVibrationIntensity(long distance) {
  if (distance > 50) distance = 50;
  if (distance < 20) distance = 20;

  return map(distance, 50, 20, 60, 255);  // Adjust range to vibration strength
}