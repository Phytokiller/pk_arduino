#define ALARM1_PIN 10 //R1
#define ALARM2_PIN 9 //R2

unsigned long alarmDebounceTime = 0;
unsigned long alarmDebounceDelay = 5000;

void setup_alarm() {
  pinMode(ALARM1_PIN, OUTPUT);
  pinMode(ALARM2_PIN, OUTPUT);
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
  digitalWrite(ALARM2_PIN, state);
}

void set_timeout_alarm(bool state) {
  digitalWrite(ALARM1_PIN, state);
}
