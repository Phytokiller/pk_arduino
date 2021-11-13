#include <EEPROM.h>

float offset_max_range = 20.0;


void setOffset (float offset, int address) {
  int offset_sign = 0;
  if (offset < 0.) {
    offset_sign = 1; 
  }
  offset = abs(offset);
  int offset_int = int(offset);
  int offset_dec = (int(offset*100)) % 100;
  if (DEBUG) {
    Serial.print("offset_sign :");Serial.println(offset_sign);
    Serial.print("offset_int :");Serial.println(offset_int);
    Serial.print("offset_dec :");Serial.println(offset_dec);
  }
  EEPROM.update(address, offset_sign);
  EEPROM.update(address+1, offset_int);
  EEPROM.update(address+2, offset_dec);
}

void setOffsetT1(float offset) {
  setOffset(offset, 1);
}

void setOffsetT2(float offset) {
  setOffset(offset, 4);
}

float readOffset(int address) {
  float offset = EEPROM.read(address+1)+EEPROM.read(address + 2)/100.;
  if(EEPROM.read(address) == 1) {
    offset = -offset;
  }
  if (offset > offset_max_range || offset < -offset_max_range) {
    Serial.println("offset out of range !!");
    offset = 0;
  }
  return offset;
}

float readOffsetT1() {
  return readOffset(1);
}

float readOffsetT2() {
  return readOffset(4);
}

void setup_offset() { // Read Offset from EEPROM
  T1_offset = readOffsetT1();
  T2_offset = readOffsetT2();
  if (DEBUG) {
    Serial.println("T1_offset = " + String(T1_offset) +", T2_offset = " + String(T2_offset));
  }
}
