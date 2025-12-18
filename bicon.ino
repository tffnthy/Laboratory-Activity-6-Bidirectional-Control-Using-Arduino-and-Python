// ---------- PIN DEFINITIONS ----------
const int redPin = 7;
const int greenPin = 6;
const int bluePin = 5;

const int btn1Pin = 12;
const int btn2Pin = 11;
const int btn3Pin = 10;

// ---------- BUTTON STATE TRACKING ----------
int btn1LastState = HIGH; // Not pressed (INPUT_PULLUP)
int btn2LastState = HIGH;
int btn3LastState = HIGH;

// ---------- LED STATE TRACKING ----------
bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {
  Serial.begin(9600); // Start serial at 9600 baud
  delay(2000);        // Wait for R4 WiFi to stabilize

  // Set LEDs as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set buttons as input with internal pull-ups
  pinMode(btn1Pin, INPUT_PULLUP);
  pinMode(btn2Pin, INPUT_PULLUP);
  pinMode(btn3Pin, INPUT_PULLUP);
}

void loop() {
  // --------- READ BUTTONS ----------
  int btn1State = digitalRead(btn1Pin);
  int btn2State = digitalRead(btn2Pin);
  int btn3State = digitalRead(btn3Pin);

  // Button 1 → send 'R' on press
  if (btn1LastState == HIGH && btn1State == LOW) {
    Serial.println("R"); // Use println for Python to read full line
  }
  btn1LastState = btn1State;

  // Button 2 → send 'G' on press
  if (btn2LastState == HIGH && btn2State == LOW) {
    Serial.println("G");
  }
  btn2LastState = btn2State;

  // Button 3 → send 'B' on press
  if (btn3LastState == HIGH && btn3State == LOW) {
    Serial.println("B");
  }
  btn3LastState = btn3State;

  // --------- READ PYTHON INPUT FOR LED TOGGLE ----------
  if (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar == '1') {
      redState = !redState;
      digitalWrite(redPin, redState);
    } else if (incomingChar == '2') {
      greenState = !greenState;
      digitalWrite(greenPin, greenState);
    } else if (incomingChar == '3') {
      blueState = !blueState;
      digitalWrite(bluePin, blueState);
    }
  }
}
