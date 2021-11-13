unsigned long old_sendTemp, interval_sendTemp = 5000; // interval between temp send to Pi
unsigned long old_updateTemp, interval_updateTemp = 1000; // interval between update temp

const int t_array_size = 5;
double T1_array[t_array_size];
double T2_array[t_array_size];
#define T1_PIN A4 //IO8
#define T2_PIN A5 //IO9

double readTemp(uint8_t pin) {
  double t = analogRead(pin);
  t = t/10.24; // 0-10V <-> 0-1024 <-> 0-100°C
  if (t > 0. && t < 100.)
    return t;
  else  {
    Serial.println("Error Reading t for "+ String(pin) + " value is " + String(t));
    return -1;
  }
}


void updateTemp(int t_pin, double t_array[], double t_offset, double &t_result) {
  double t = readTemp(t_pin);
  if (t != -1) {
    
     // Update Temp array
    for (int i = 0; i < t_array_size-1; i ++) {
      t_array[i] = t_array[i+1];
    }
    t_array[t_array_size-1] = t + t_offset;
    // Update Temp
    double t_t1 = 0;
    for (int i = 0; i < t_array_size; i++) {
      t_t1 = t_t1 + t_array[i];
    }
    t_result = t_t1/t_array_size;
    if (DEBUG == -1) {
      Serial.print(String(t_pin) + " : [");
      for (int i = 0; i < t_array_size; i++) {
        Serial.print(t_array[i]);
        Serial.print(",");
      }
      Serial.println("] / " + String(t_result) + "°C");
    }
  }
}


void loop_temp() {
  // Update T array and T value
  if (millis() > (old_updateTemp + interval_updateTemp)) {
    updateTemp(T1_PIN, T1_array, T1_offset, T1);
    updateTemp(T2_PIN, T2_array, T2_offset, T2);
    Tmean = (T1 + T2)/2;
    old_updateTemp = millis();
  }
  
  // Send To Pi
  if (millis() > (old_sendTemp + interval_sendTemp)) {
    send_RS485_temp();
    old_sendTemp = millis();
  }
}
