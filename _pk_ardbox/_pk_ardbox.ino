/*
 * PHYTOKILLER ARDUINO 
 * Industrial shield Ardbox RelayHF+
 * 
 * Temperature : 0/10V on I8 & I9
 * Boiler : RLY on R3
 * Alarm : RLY on R6
 * Door : Input on IO6
 * 
 */

#define DEBUG -2 // 0 : no print, 1 : basic, -1 : realtime temp, -2 : pid value

double T1;
double T2;
double Tmean;

bool door_state;
bool boiler_state;

float T1_offset;
float T2_offset;


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Start pk_ardbox setup");
  setup_offset();
  setup_coms();
  setup_boiler();
  setup_door();
  Serial.println("pk_ardbox start !");
}


void loop() {
  loop_temp();
  loop_boiler();
  loop_door();
}
