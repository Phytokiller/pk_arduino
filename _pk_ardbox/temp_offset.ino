void setOffsetT1(float offset) {
  setOffset(offset, 1);
}

void setOffsetT2(float offset) {
  setOffset(offset, 4);
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
