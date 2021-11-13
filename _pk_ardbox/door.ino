#define DOOR_PIN A2

bool last_door_state;

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
  if (reading != last_door_state) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != door_state) {
      door_state = reading;
      send_RS485_door();
    }
  }
  last_door_state = reading;
  
}
