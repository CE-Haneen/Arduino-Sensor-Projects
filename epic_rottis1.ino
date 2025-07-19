// C++ code
const int tempPin = A0;
const int ledPin = 4;
const int buttonPin = 2;

bool circuitEnabled = false;
unsigned long circuitStartTime = 0;
unsigned long ledStartTime = 0;
bool ledOn = false;
const int tempThreshold = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(200);
    circuitEnabled = true;
    circuitStartTime = millis();
  }

  if (circuitEnabled) {
    unsigned long currentTime = millis();

    int sensorValue = analogRead(tempPin);
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperatureC = (voltage - 0.5) * 100.0;

    Serial.print("Temp: ");
    Serial.println(temperatureC);

    if (temperatureC > tempThreshold) {
      digitalWrite(ledPin, HIGH);
      ledStartTime = currentTime;
      ledOn = true;
    }

    if (temperatureC <= tempThreshold && ledOn) {
      digitalWrite(ledPin, LOW);
      ledOn = false;
    }

    if ((currentTime - circuitStartTime >= 10000) && !ledOn) {
      circuitEnabled = false;
      digitalWrite(ledPin, LOW);
    }
  } else {
    digitalWrite(ledPin, LOW);
  }
}