// Reconstructed 2026-10-23. New pin map; not the lost original firmware.
#include <Arduino.h>
#if defined(ESP32)
const int SENSOR=34, INPUT_A=27, INPUT_B=14, OUT=26, AUX=25;
const int ADC_MAXIMUM=4095;
#else
const int SENSOR=A0, INPUT_A=2, INPUT_B=3, OUT=8, AUX=9;
const int ADC_MAXIMUM=1023;
#endif
// OUT/AUX drive a transistor/module input, never an inductive load directly.
// Default OFF = LOW. Use a compatible active-HIGH driver for this reconstruction.

bool pump=false,fault=false;unsigned long started=0,last=0;
const int DRY_RAW=ADC_MAXIMUM*8/10,WET_RAW=ADC_MAXIMUM*3/10;
void setup(){Serial.begin(115200);pinMode(OUT,OUTPUT);digitalWrite(OUT,LOW);pinMode(INPUT_A,INPUT_PULLUP);pinMode(INPUT_B,INPUT_PULLUP);}
void loop(){
 unsigned long now=millis();
 if(digitalRead(INPUT_B)==LOW){fault=false;pump=false;digitalWrite(OUT,LOW);return;}
 if(now-last<100)return;last=now;
 int raw=analogRead(SENSOR);bool water=digitalRead(INPUT_A)==LOW;
 if(!water||raw<10||raw>ADC_MAXIMUM-10){fault=true;pump=false;}
 int moisture=constrain(map(raw,DRY_RAW,WET_RAW,0,100),0,100);
 if(fault)pump=false;
 else if(pump&&now-started>=20000){pump=false;fault=true;}
 else if(pump&&moisture>=55)pump=false;
 else if(!pump&&moisture<=30){pump=true;started=now;}
 digitalWrite(OUT,pump?HIGH:LOW);
 Serial.print(moisture);Serial.print(',');Serial.print(pump);Serial.print(',');Serial.println(fault);
}
