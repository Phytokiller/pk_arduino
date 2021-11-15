#include <EEPROM.h>

/*
 * offset :
 * T1 (sign, int, dec) : 1,2,3
 * T2 (sign, int, dec) : 4,5,6
 * 
 */


 /****************************
  *      OFFSET 
  ****************************/
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

 /****************************
  *      BOILER
  ****************************/
void setBoilerTarget(float b_t) {
  int address = 7;
  int bt_int = int(b_t);
  int bt_dec = (int(b_t*100)) % 100;
  if (DEBUG) {
    Serial.print("bt_int :");Serial.println(bt_int);
    Serial.print("bt_dec :");Serial.println(bt_dec);
  }
  EEPROM.update(address, bt_int);
  EEPROM.update(address+1, bt_dec);
  
}

float readBoilerTarget() {
  int address = 7;
  float b_t = EEPROM.read(address)+EEPROM.read(address + 1)/100.;
  if (b_t > 90 || b_t < 10) {
    Serial.println("boiler target out of range !!");
    b_t = 50;
  }
  return b_t;
}
