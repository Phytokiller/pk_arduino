#define LIGHT_PIN 7 //R6

unsigned long alarmDebounceTime = 0;
unsigned long alarmDebounceDelay = 5000;

void setup_alarm() {
  pinMode(LIGHT_PIN, OUTPUT);
}


void loop_alarm() {
  if (millis() > (alarmDebounceTime + alarmDebounceDelay)) {
    set_temp_alarm(temp_alarm_state);
    temp_alarm_state = false;
//    set_timeout_alarm(timeout_alarm_state);
//    timeout_alarm_state = false;
    alarmDebounceTime = millis();
  }
}

void set_temp_alarm(bool state) {
  digitalWrite(LIGHT_PIN, state);
}

void set_timeout_alarm(bool state) {
  digitalWrite(LIGHT_PIN, state);
}
