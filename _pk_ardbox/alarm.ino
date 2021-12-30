#define ALARM1_PIN 10 //R1
#define ALARM2_PIN 9 //R2

unsigned long timeoutDebounceTime = 0;
unsigned long timeoutDebounceDelay = 5000;

bool alarm1_state = false;
bool alarm2_state = true;

void setup_alarm() {
  pinMode(ALARM1_PIN, OUTPUT);
  digitalWrite(ALARM1_PIN, HIGH);
  pinMode(ALARM2_PIN, OUTPUT);
  digitalWrite(ALARM2_PIN, LOW);
}


void loop_alarm() {
  
  if (millis() > (timeoutDebounceTime + timeoutDebounceDelay)) {
    set_timeout_alarm(timeout_alarm_state);
    timeout_alarm_state = false;
    timeoutDebounceTime = millis();
  }
  
}


void process_Alarm_High(int data) { // called by com

  if(data != alarm2_state) {
    if (DEBUG) {
        Serial.print("Change Alarm1 from Alarm High to");
        Serial.println(data);
      }
    alarm2_state = data;
    digitalWrite(ALARM2_PIN, alarm2_state);
  }
}

void set_timeout_alarm(bool state) {
  //digitalWrite(ALARM1_PIN, !state);
  digitalWrite(ALARM2_PIN, state);
}
