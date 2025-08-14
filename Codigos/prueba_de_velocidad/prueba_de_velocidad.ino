# include<Wire.h>

char CODE[16];
String vel;
String a;

float revoluciones = 0;
float velocidad=0;

int ledNORTE = 13; //pin del led
int digitalNORTE =3 ; //Pin para sensor norte
int analogNORTE = A0; //Pin para sensor

int ledESTE = 12;
int digitalESTE = 4; //Pin para sensor este
int analogESTE = A1;

int ledSUR = 11;
int digitalSUR = 5; //Pin para sensor este
int analogSUR = A2;

int ledOESTE = 10;
int digitalOESTE = 6; //Pin para sensor oeste
int analogOESTE = A3;

int digitalValNORTE;
int analogValNORTE;

int digitalValESTE;
int analogValESTE;

int digitalValSUR;
int analogValSUR;

int digitalValOESTE;
int analogValOESTE;

void setup() {
Wire.begin(1);
Wire.onRequest(peticion);
Serial.begin(9600);
  pinMode(2,INPUT);
 
  pinMode(ledNORTE, OUTPUT); 
  pinMode(digitalNORTE, INPUT); 
  
  pinMode(ledESTE, OUTPUT); 
  pinMode(digitalESTE, INPUT);

  pinMode(ledSUR, OUTPUT); 
  pinMode(digitalSUR, INPUT);

  pinMode(ledOESTE, OUTPUT); 
  pinMode(digitalOESTE, INPUT);
}

void loop() {

attachInterrupt(digitalPinToInterrupt(2), fucion, RISING);
delay(3000);
detachInterrupt(2);  
  velocidad= revoluciones*0.18; //rpm y el viento a km/h
  Serial.println("");
  Serial.print("La Velocidad es: ");
  Serial.println(velocidad);
  revoluciones=0;




  //
  bool norteActivo = digitalRead(digitalNORTE) == HIGH;
  bool esteActivo = digitalRead(digitalESTE) == HIGH;
  bool surActivo = digitalRead(digitalSUR) == HIGH;
  bool oesteActivo = digitalRead(digitalOESTE) == HIGH;

  if (norteActivo && !esteActivo && !surActivo && !oesteActivo) {
    digitalWrite(ledNORTE, HIGH);
    digitalWrite(ledESTE, LOW);
    digitalWrite(ledSUR, LOW);
    digitalWrite(ledOESTE, LOW);
    Serial.println("NORTE");
    a="1";
  } else if (!norteActivo && esteActivo && !surActivo && !oesteActivo) {
    digitalWrite(ledNORTE, LOW);
    digitalWrite(ledESTE, HIGH);
    digitalWrite(ledSUR, LOW);
    digitalWrite(ledOESTE, LOW);
    Serial.println("ESTE");
     a="2";
  } else if (!norteActivo && !esteActivo && surActivo && !oesteActivo) {
    digitalWrite(ledNORTE, LOW);
    digitalWrite(ledESTE, LOW);
    digitalWrite(ledSUR, HIGH);
    digitalWrite(ledOESTE, LOW);
    Serial.println("SUR");
     a="3";
  } else if (!norteActivo && !esteActivo && !surActivo && oesteActivo) {
    digitalWrite(ledNORTE, LOW);
    digitalWrite(ledESTE, LOW);
    digitalWrite(ledSUR, LOW);
    digitalWrite(ledOESTE, HIGH);
    Serial.println("OESTE");
     a="4";
  } else if (norteActivo && oesteActivo) {
    digitalWrite(ledNORTE, HIGH);
    digitalWrite(ledESTE, LOW);
    digitalWrite(ledSUR, LOW);
    digitalWrite(ledOESTE, HIGH);
    Serial.println("NOROESTE");
     a="5";
  } else if (norteActivo && esteActivo) {
    digitalWrite(ledNORTE, HIGH);
    digitalWrite(ledESTE, HIGH);
    digitalWrite(ledSUR, LOW);
    digitalWrite(ledOESTE, LOW);
    Serial.println("NORESTE");
     a="6";
  } else if (surActivo && oesteActivo) {
    digitalWrite(ledNORTE, LOW);
    digitalWrite(ledESTE, LOW);
    digitalWrite(ledSUR, HIGH);
    digitalWrite(ledOESTE, HIGH);
    Serial.println("SUROESTE");
     a="7";
  } else if (surActivo && esteActivo) {
    digitalWrite(ledNORTE, LOW);
    digitalWrite(ledESTE, HIGH);
    digitalWrite(ledSUR, HIGH);
    digitalWrite(ledOESTE, LOW);
    Serial.println("SURESTE");
     a="8";
  } else {
    digitalWrite(ledNORTE, LOW);
    digitalWrite(ledESTE, LOW);
    digitalWrite(ledSUR, LOW);
    digitalWrite(ledOESTE, LOW);
     a="9";
  }
  Serial.println();
  delay(1000);

  
}
void fucion(){
  revoluciones++;
  Serial.println(revoluciones);
}
 void peticion(){
  vel="#"+String(velocidad)+";"+a+"fin";
  vel.toCharArray(CODE,16);
  Wire.write(CODE);} 
