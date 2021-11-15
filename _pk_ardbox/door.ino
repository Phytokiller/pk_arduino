#define DOOR_PIN A2

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 10000;


void setup_door() {
  pinMode(DOOR_PIN, INPUT);
}

void loop_door() {
  /*
  door_state = digitalRead(DOOR_PIN);
  if (door_state != last_door_state) {
    last_door_state = door_state;
    send_RS485_door();
  }
  */
  
  int reading = digitalRead(DOOR_PIN);
  if (reading != door_state) {
    if (millis() > (debounceDelay + lastDebounceTime)) {
      door_state = reading;
      lastDebounceTime = millis();
      send_RS485_door();
    }
  }
}
