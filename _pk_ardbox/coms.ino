// Include Industrial Shields libraries
#include <RS485.h>

String rcv_message = "";

void setup_coms() {
  // Begin RS485 port
  RS485.begin(38400);
}


// ---------- RECEIVE -------------
void RS485Event() {
  // Print received byte
  byte rx = RS485.read();
  if (rx == 33) { //  '! - start'
   rcv_message = "";  
  }
  else if (rx == 10) { //  '\n - end'
    if (DEBUG) {
      Serial.println(rcv_message);
    }
    route_RS485(rcv_message);
  }
  else {
    rcv_message = rcv_message + char(rx);
  }
}

void route_RS485(String message) {
  /*
   * ALARM : "!alarm:1"
   * T1 OFFSET : "!T1offset:xx.xx" 
   * T2 OFFSET : "!T2offset:xx.xx"
   * 
   * 
   * 
   */
  if (message.startsWith("alarm")) {
    if (message.endsWith("1")) {
      set_alarm(true);
    }
    else {
      set_alarm(false);
    }
  }
  else if (message.startsWith("T1offset")) {
    setOffsetT1(message.substring(9, message.length()).toFloat());
  }
  else if (message.startsWith("T2offset")) {
    setOffsetT2(message.substring(9, message.length()).toFloat());
  }
}

// ------------ SEND -------------
void send_RS485(String message) {
  for (int i = 0; i < message.length(); i++) {
    RS485.write(message[i]);
  }
  RS485.write('\n');
}

void send_RS485_door() {
  String Dmessage = "door:" + String(door_state);
  if (DEBUG == 1) {
    Serial.println(Dmessage);
  }
  send_RS485(Dmessage);
}

void send_RS485_temp() {
  String Tmessage = "sensors:"+String(T1)+":"+String(T2);
  if (DEBUG == 1) {
    Serial.println(Tmessage);
    Serial.println(Tmean);
  }
  send_RS485(Tmessage);
}

void send_RS485_boiler() {
  String Bmessage = "boiler:"+String(boiler_relay_state);
  if (DEBUG == 1) {
    Serial.println(Bmessage);
  }
  send_RS485(Bmessage);
}
    
