

void setOffsetT1(float offset) {
  if (offset > offset_max_range || offset < -offset_max_range) {
    Serial.println("T1_offset out of range");   
  }
  else {
    setOffset(offset, 1);
  }
  T1_offset = readOffsetT1();
}

void setOffsetT2(float offset) {
  if (offset > offset_max_range || offset < -offset_max_range) {
    Serial.println("T2_offset out of range");   
  }
  else {
    setOffset(offset, 4);
  }
  T2_offset = readOffsetT2();
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
