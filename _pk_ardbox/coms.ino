/*
 * Receive : 
 *  ALARM : "!alarm:1"
 *  T1 OFFSET : "!T1offset:xx.xx" 
 *  T2 OFFSET : "!T2offset:xx.xx"
 *  T target BOILER : "!Tboiler:xx.xx"
 *  getT1offset :
 * 
 * Send :
 *  DOOR : door:X
 *  SENSORS : sensors:XX.xx:YY.yy
 *  BOILER : boiler:X
 *  
 */
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
      Serial.print("RS485Event : ");Serial.println(rcv_message);
    }
    route_RS485(rcv_message);
  }
  else {
    rcv_message = rcv_message + char(rx);
  }
}

void route_RS485(String message) {
  /*
   * 
   * 
   * 
   * 
   */
  if (message.startsWith("alarm")) {
    if (DEBUG) {
      Serial.println("receive alarm");
    }
    temp_alarm_state = true;
  }
  else if (message.startsWith("timeout")) {
    if (DEBUG) {
      Serial.println("receive timeout");
    }
    timeout_alarm_state = true;
  }
  else if(message.startsWith("getSettings")) {
    if (DEBUG) {
      Serial.println("get setting asked !");
    }
    send_RS485_getSettings();
  }
  else if (message.startsWith("T1offset")) {
    setOffsetT1(message.substring(9, message.length()).toFloat());
  }
  else if (message.startsWith("T2offset")) {
    setOffsetT2(message.substring(9, message.length()).toFloat());
  }
  else if (message.startsWith("Tboiler")) {
    setBoilerTarget(message.substring(8, message.length()).toFloat());
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
    Serial.print(Tmessage);
    Serial.println(" // Tmean :" + String(Tmean));
  }
  send_RS485(Tmessage);
}

void send_RS485_getSettings() {
  String Smessage = "settings:{\"T1offset\":"+String(T1_offset)+",\"T2offset\":"+String(T2_offset)+",\"Tboiler\":" + String(Tboiler)+"}";
  if (DEBUG == 1) {
    Serial.println(Smessage);
  }
  send_RS485(Smessage);
}

void send_RS485_boiler() {
  String Bmessage = "boiler:"+String(boiler_relay_state);
  if (DEBUG == 1) {
    Serial.println(Bmessage);
  }
  send_RS485(Bmessage);
}

    
