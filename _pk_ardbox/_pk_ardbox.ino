/*
 * PHYTOKILLER ARDUINO 
 * Industrial shield Ardbox RelayHF+
 * 
 * Temperature : 0/10V on I8 & I9
 * Boiler : RLY on R3
 * Alarm : RLY on R6
 * Door : Input on IO6
 * 
 * 
 * TODO :
 *  Light : si alarm OU timeout 
 *  Sound : pour timeout ou alarm
 *  Enregistrer les courbes dans la carte SD de l'ardbox
 * 
 */

#define DEBUG 1 // 0 : no print, 1 : basic, -1 : realtime temp, -2 : pid value

double T1;
double T2;
double Tmean;

double Tboiler = 25.0;

bool door_state;
bool boiler_state;

float T1_offset;
float T2_offset;
float offset_max_range = 20.0;

bool temp_alarm_state = false;
bool timeout_alarm_state = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Start pk_ardbox setup");
  setup_offset();
  setup_coms();
  setup_boiler();
  setup_door();
  Serial.println("pk_ardbox loop start !");
}


void loop() {
  loop_temp();
  loop_boiler();
  loop_door();
  loop_alarm();
}
