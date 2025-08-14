#define pinPluviometro 2
#include "Wire.h"
int pulsos;
double factor = 4;
double mm_lluvia;
String mm_lluvia_s;
char mm_lluvia_c[5];
volatile bool interrupcionDetectada = false;
unsigned long tiempoInicio = 0;
unsigned long tiempoEspera = 6000;
void setup() {
  Serial.begin(9600);
  Wire.begin(1);
  pinMode(pinPluviometro,INPUT);
  Wire.onRequest(requestEvent);
  attachInterrupt(digitalPinToInterrupt(pinPluviometro), count_up, FALLING);

}

void loop() {
  //contador();
  unsigned long tiempoActual = millis();

  if (interrupcionDetectada) {
    tiempoInicio = tiempoActual;
    interrupcionDetectada = false;
  }

  if (tiempoActual - tiempoInicio >= tiempoEspera) {
    Serial.println("No se detectó interrupción durante el tiempo especificado.");
    pulsos =0;
    tiempoInicio = tiempoActual;
  }
  //Serial.println(digitalRead(pinPluviometro));
}

void contador(){
  attachInterrupt(digitalPinToInterrupt(pinPluviometro), count_up, FALLING);
  delay(2000);
  detachInterrupt(2);
}
void count_up(){
  interrupcionDetectada = true;
  pulsos++;
  delay (500);
  mm_lluvia = pulsos*factor;
  Serial.println(pulsos);
}
void requestEvent() {
  mm_lluvia_s = String(mm_lluvia);
  mm_lluvia_s.toCharArray(mm_lluvia_c,5);
  Wire.write(mm_lluvia_c); 
}
