#define LIGHT_PIN 7 //R6

void setup_alarm() {
  pinMode(LIGHT_PIN, OUTPUT);
}

void set_alarm(bool state) {
  digitalWrite(LIGHT_PIN, state);
}
