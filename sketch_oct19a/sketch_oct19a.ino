const int dirPin = 2;
const int stepPin = 3;

int delays_micros = 5;
int last_step_micros = 0;

bool last_low = true;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  delay(2000);    

  digitalWrite(dirPin, LOW);
  last_step_micros = millis();
  // put your setup code here, to run once:

}

void loop() {
  // digitalWrite(stepPin, HIGH);
  // delay(1000);

  // digitalWrite(stepPin, LOW);
  // delay(1000);

  unsigned long now = millis();
  if (now - last_step_micros >= delays_micros) {
    last_step_micros = now;

    if (last_low) {
      digitalWrite(stepPin, HIGH);
      last_low = false;
    } else {
      digitalWrite(stepPin, LOW);
      last_low = true;
    }
  }
  // put your main code here, to run repeatedly:

}
