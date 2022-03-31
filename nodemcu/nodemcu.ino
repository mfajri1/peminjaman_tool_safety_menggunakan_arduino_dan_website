#include <SoftwareSerial.h>
//library wifi
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//Network SSID
const char* ssid = "ernitamelia";
const char* password = "12345678";

//pengenal host (server) = IP Address komputer server
const char* host = "192.168.43.177";

SoftwareSerial node(4, 5); // RX, TX
unsigned long previousMillis = 0;
const long interval = 1000;
String dataMega = "";
String arrMega[5];
int indexMega = 0;
String payload = "";
String dataMega1 = "";
int led1 = 12;
int led2 = 14;
int rst = 2;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  node.begin(9600);

//  //setting koneksi wifi
  WiFi.mode(WIFI_STA);
  WiFi.hostname("NodeMCU");
  WiFi.begin(ssid, password);

  //cek koneksi wifi
  while(WiFi.status() != WL_CONNECTED)
  {
    //progress sedang mencari WiFi
    delay(500);
    Serial.print(".");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  Serial.println("Wifi Connected");
  Serial.println("IP Address : ");
  Serial.println(WiFi.localIP());

}

void loop() {
//  unsigned long currentMilis = millis();
//  if(currentMilis - previousMillis >= interval){
//    previousMillis = currentMilis;
//  }
  if(node.available() > 0) {
    dataMega += node.readStringUntil('\n');
  }
  
  dataMega.trim();
  if(dataMega != NULL){
    Serial.println(dataMega);
    for(int i = 0; i <= dataMega.length(); i++){
      char delimiter = '#';
      if(dataMega[i] != delimiter){
        arrMega[indexMega] += dataMega[i];    
      }else{
        indexMega++;
      }
    }
    Serial.println(arrMega[0]);
    Serial.println(arrMega[1]);
    Serial.println(arrMega[2]);
    Serial.println(arrMega[3]);
    Serial.println(arrMega[4]);
    WiFiClient client;
    const int httpPort = 80;
    if(!client.connect(host, httpPort))
    {
      Serial.println("Connection Failed");
      return;
    }

    String Link;
    HTTPClient http;
    if(arrMega[4] == "Pinjam" || arrMega[4] == "Balik"){
      Link = "http://192.168.43.177/ernita/transaksi.php?nokartu=" + arrMega[0] + "&pass=" + arrMega[1] + "&jml=" + arrMega[2] + "&lemari=" + arrMega[3] + "&stat=" + arrMega[4];  
    }else{
      Link = "http://192.168.43.177/ernita/kirimkartu.php?nokartu=" + arrMega[0] + "&pass=" + arrMega[1];
    }
    http.begin(Link);

    int httpCode = http.GET();
    payload = http.getString();
    payload.trim();
    Serial.println(payload);
    node.println(payload);
    http.end();
    payload = "";
    node.flush();
    arrMega[0] = "";
    arrMega[1] = "";
    arrMega[2] = "";
    arrMega[3] = "";
    arrMega[4] = "";
    indexMega = 0;
    pinMode(rst, OUTPUT);
    digitalWrite(rst, LOW);
    delay(200);
    digitalWrite(rst,HIGH);
  }
  dataMega = "";
  dataMega1 = "";
  
  delay(1000);
}

String bacaDataMega(){
  while(node.available() > 0) {
    dataMega1 += char(node.read());
  }
  dataMega1.trim();
//  Serial.println(dataMega);

  return dataMega1;
}
