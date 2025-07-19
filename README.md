# Arduino-Sensor-Projects

# Project 1: TempSense-LED-Control  
LED control using TMP36 temperature sensor and push button. Turns on above 50°C, Auto shutoff and manual disable supported


### Components Used

- Arduino Uno  
- TMP36 Temperature Sensor  
- Push Button  
- LED  
- 220Ω Resistor  
- Breadboard & Jumper Wires

### How it works
- The LED will turn ON only if the temperature exceeds 50°C and the circuit is enabled via the push button.  
- Once turned ON, the LED will stay ON for 10 seconds then turn OFF.  
- If nothing happens for 10 seconds, the circuit will auto-disable.  
- The LED will also turn OFF if the temperature drops below 50°C.  
- Pressing the button again toggles the circuit ON/OFF.


### Circuit Diagram
![circuit-digram2](https://github.com/user-attachments/assets/fd7b5195-cf13-4c3f-9bd1-d7423f2696c2)
![circuit-digram3](https://github.com/user-attachments/assets/ba4d86d2-9a55-497e-9ef0-51578a122066)


### Code Logic
```cpp
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

```








