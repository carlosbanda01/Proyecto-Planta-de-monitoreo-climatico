#include <Ethernet.h>
#include <SPI.h>
//#include <UbidotsEthernet.h>

#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SD.h>

#include <UnixTime.h>

UnixTime stamp(1);

#define DHTPIN 2 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

#include <RTClib.h>	
RTC_DS3231 rtc;

LiquidCrystal_I2C lcd(0x27, 16, 2);

String FECHA;
String HORA;

String data;
char buffer[40];

#define CS  4
 
byte progressBar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

float h;
float t;

#define SS     10    //W5500 CS
#define RST    7

/********************************
 * Constants and objects
 *******************************/
/* Assigns the Ubidots parameters */
char const * TOKEN = "BBFF-R0LuYwI3yzJI9X3wDgZC8dE7OgYmxQ"; // Assign your Ubidots TOKEN
char const * VARIABLE_LABEL = "TEMPERATURA"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL2 = "HUMEDAD";

/* Enter a MAC address for your controller below */
/* Newer Ethernet shields have a MAC address printed on a sticker on the shield */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

/* initialize the instance */
//Ubidots client(TOKEN);

uint32_t unix;
uint32_t timestamp;

File myFile;

boolean state=true;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(SS, OUTPUT);
  pinMode(RST, OUTPUT);
  digitalWrite(SS, LOW);
  digitalWrite(RST,HIGH);

  pinMode(CS, OUTPUT);
  //digitalWrite(CS, HIGH);


  dht.begin();
  Wire.begin();//inicio de conexion I2C
  lcd.init();
  lcd.backlight();
  lcd.clear();

  cargando();

  //digitalWrite(CS,LOW);
  delay(10);
  //if (!SD.begin(CS)) 
  //{
    //Serial.println("No SD card!");
    //return;
  //}

  if (! rtc.begin()) {				// si falla la inicializacion del modulo
    Serial.println("Modulo RTC no encontrado !");	// muestra mensaje de error
    while (1);					// bucle infinito que detiene ejecucion del programa
  }

  //client.setDebug(true);// uncomment this line to visualize the debug message
  /* start the Ethernet connection */
  /*
  Serial.print(F("Starting ethernet..."));
  if (!Ethernet.begin(mac)) {
    Serial.println(F("failed"));
  } else {
    Serial.println(Ethernet.localIP());
  }
  /* Give the Ethernet shield a second to initialize */
  delay(250);
  Serial.println(F("Ready"));
  
}


void loop() {
  //Ethernet.maintain();
  /* Sensors readings */
  /* Sending values to Ubidots */
  //client.add(VARIABLE_LABEL, t);
  //client.add(VARIABLE_LABEL2, h);
  //client.sendAll();
  HUMEDAD_TEMPERATURA();
  RTCfecha ();
  Serial.println(data);
  delay(250);
}

void HUMEDAD_TEMPERATURA(){
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  data = "#"+FECHA+","+HORA+","+String(t)+","+String(h)+"@";
  data.toCharArray(buffer,40);
  Wire.beginTransmission(1); // transmit to device #1
  Serial.println(buffer);
  Wire.write(buffer);        // sends bytes
  Wire.endTransmission();    // stop transmitting
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.setCursor(6, 0);
  lcd.print(String(t, 2) + "°C");
  lcd.setCursor(10, 1);
  lcd.print(String(h, 1) + "%");
  delay(1000);
}

void cargando(){
  lcd.createChar(0, progressBar);  // Crear el carácter personalizado
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("CARGANDO ...");

  for (int i = 0; i <= 16; i++) {  // Llena la barra de progreso
    lcd.setCursor(i, 1);
    lcd.write((byte)0); // Mostrar el carácter personalizado
    delay(250);          // Esperar un momento
  }

  lcd.clear();  
  delay(250);  

  lcd.setCursor(0, 0);
  lcd.print("BIENVENIDOS");
  lcd.setCursor(0, 1);
  lcd.print("ESTACION-GRUPO 5");
  delay(250);
  lcd.clear();  
  delay(250);
}

void RTCfecha () {
  DateTime fecha = rtc.now();
  FECHA = ((String)fecha.day()+"/"+(String)fecha.month()+"/"+(String)fecha.year());
  HORA = ((String)fecha.hour()+":"+(String)fecha.minute()+":"+(String)fecha.second());

  stamp.setDateTime(fecha.year(), fecha.month(), fecha.day(), fecha.hour(), fecha.minute(), fecha.second());   // 20 мая 2021, 7:04:15
  unix = stamp.getUnix();

  DateTime now2 = rtc.now();
  timestamp = now2.unixtime() * 1000;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(FECHA);
  lcd.setCursor(0,1);
  lcd.print(HORA);
  delay(1000);
  lcd.clear();
}

void Lectura (){
  Wire.requestFrom(2, data2); // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
  coma = m.indexOf(',');
  coma22 = coma + 1;
  coma2 = m.indexOf(',', coma22);
  coma3 = m.lastIndexOf(',');
  fin = m.indexOf('@');

  PRESION= m.substring(inicio+1,coma);
  HORA = m.substring(coma+1,coma2);
  TEMP = m.substring(coma2+1,coma3);
  HUM = m.substring(coma3+1,fin);
  
  TEMP.toCharArray(temp, 5);
  HUM.toCharArray(hum, 5);
  HORA.toCharArray(hora, 9);
  Serial.println(temp);
  Serial.println(hum);
  delay(500);
}
