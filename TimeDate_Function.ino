#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeLib.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <WiFiEspClient.h>
#include <SoftwareSerial.h>
#define DEBUG_ON
#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(10,11);
#endif
#ifndef HAVE_HWSERIAL2
SoftwareSerial Serial2(12,13);
#endif
/*
 * Library used 
 * WiFiEsp: https://github.com/bportaluri/WiFiEsp
 * Time: https://github.com/PaulStoffregen/Time
 * 
 */
String date1,date2,time1,hData,tData,ipAdd,macAdd,latData,longData;  
char ssid[] = "Dulay55";            
char pass[] = "confidential";        
int status = WL_IDLE_STATUS;
const int timeZone = -8;    
unsigned int localPort = 2390;        // local port to listen for UDP packets
char timeServer[] = "0.asia.pool.ntp.org";
char mhiServer[] = "mhi.x10host.com"; 
const int NTP_PACKET_SIZE = 48;  
const int UDP_TIMEOUT = 2000;    
byte packetBuffer[NTP_PACKET_SIZE]; 
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;

WiFiEspClient client;
WiFiEspUDP Udp;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup(){

  Serial.begin(9600);
  Serial1.begin(9600);
 
  lcd.begin(20,4);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("You're connected to the network");
 
  Udp.begin(localPort);
}
void loop(){
  getTime();
  Serial.println(date1);
  Serial.println(time1);
  
}
void getTime(){
 sendNTPpacket(timeServer);
  unsigned long startMs = millis();
  while (!Udp.available() && (millis() - startMs) < UDP_TIMEOUT) {}
  if (Udp.parsePacket()) {
    Serial.println("packet received");
    Udp.read(packetBuffer,NTP_PACKET_SIZE);
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    epoch=epoch+28800;
    /*
    Serial.print("Date: ");
    Serial.print(month(epoch));
    Serial.print("/");
    Serial.print(day(epoch)) ;
    Serial.print("/");
    Serial.println(year(epoch));
    Serial.print("Time: ");
    Serial.print(hourFormat12(epoch));
    Serial.print(":");
    //Serial.print(minute(epoch));
    if(minute(epoch)<=9) {
      Serial.print("0");
      Serial.print(minute(epoch));
    }
    else {
      Serial.print(minute(epoch));
    }
    if(hour(epoch)<=11) {
      Serial.println(" AM");
    }
    else {
      Serial.println(" PM");
    }
    Serial.println("");*/
    date1 = String(month(epoch)) +"/"+String(day(epoch))+"/"+String(year(epoch));
    time1 = String(hourFormat12(epoch))+":";
    if(minute(epoch)<=9){
     time1+="0"+String(minute(epoch));
    }else{
     time1+=String(minute(epoch));
    }
    if(hour(epoch)<=11){
     time1+="AM";
    }else{
     time1+="PM";
    }
  }
  delay(5000);
}
void sendNTPpacket(char *ntpSrv){
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   
  packetBuffer[1] = 0;     
  packetBuffer[2] = 6;     
  packetBuffer[3] = 0xEC;  
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  Udp.beginPacket(ntpSrv, 123); 
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}




