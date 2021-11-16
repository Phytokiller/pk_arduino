#include <PID_v2.h>

#define BOILER_PIN 6 //R3

bool boiler_relay_state = false;
bool old_boiler_relay_state;


unsigned long boiler_last_change_time;
unsigned long boiler_change_time = 1000;




//Specify the links and initial tuning parameters
double boiler_pid; // 0-255
double pid_low_action = 10; //low than this, stop the boiler
double pid_high_action = 10; //high than this, start the boiler

double Kp=2, Ki=5, Kd=1;
PID myPID(&Tmean, &boiler_pid, &Tboiler-1, Kp, Ki, Kd, DIRECT);


void setup_boiler() {
  pinMode(BOILER_PIN, OUTPUT);
  
  Tboiler = readBoilerTarget(); //Read from EEprom
  if (DEBUG) {
    Serial.println("Ttarget = " + String(Tboiler));
  }
  // tell the PID to range between 0 and the full window size
  myPID.SetMode(AUTOMATIC);
}

void loop_boiler() {
  myPID.Compute(); // update boiler_pid : 0 too high, 255 too low.
  if (DEBUG == -2)
    Serial.println(String(Tmean) + " / " + String(boiler_pid));
  if (boiler_pid > pid_high_action) {
    boiler_relay_state = true;
  }
  else if (boiler_pid < pid_low_action) {
    boiler_relay_state = false;
  }
  if(millis() > (boiler_last_change_time + boiler_change_time)) {
    if (old_boiler_relay_state != boiler_relay_state) {
      send_RS485_boiler();
      old_boiler_relay_state = boiler_relay_state;
    }
    digitalWrite(BOILER_PIN, boiler_relay_state);
    boiler_last_change_time = millis();
  }
}
