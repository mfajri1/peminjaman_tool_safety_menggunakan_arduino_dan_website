#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>
//libarary rfid
#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <Servo.h>
#include <DFPlayer_Mini_Mp3.h>

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

#define TX_PIN 12 //6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 13 //5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial thermal(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&thermal);     // Pass addr to printer constructor

SoftwareSerial megaMp3(10, 11);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'a'},
  {'4','5','6', 'b'},
  {'7','8','9', 'c'},
  {'*','0','#', 'd'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//konfig lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

//konfig rfid
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// inisiasi servo
Servo servo1;
Servo servo2;
Servo servo3;
int pos = 0;

String card1 = "14721017024";
String card2 = "5121116624";

bool keypass = false;


long int prokey = 0;
String stat = "";
long int nilaiPass = 0;
String modet = "";
//untuk milis
unsigned long previousMillis = 0;
const long interval = 1000;
long int jml = 0;
long int lmr = 0;
String arrNode[2];
String IDTAG = "";
String statKeypad = "";
int indexNode = 0;
String dataNode = "";
String kirim = "";
String dataNode1 = "";
int resetMega = 4;
void setup() {
  // put your setup code here, to run once:
  
  thermal.begin(9600);
  Serial.begin(9600);
  Serial1.begin(9600);
  megaMp3.begin(9600);
  
  printer.begin();
  servo1.attach(6);
  servo2.attach(7);
  servo3.attach(8);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servoNol();
  
  mp3_set_serial(megaMp3);
  delay(10);
  SPI.begin();
  // deklarasi rfid
  lcd.begin();
  lcd.backlight(); 
  lcd.clear();     
  // setting awal RFID  
  mfrc522.PCD_Init();
  mp3_set_volume (40);
  delay(10);
  mp3_play(01);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SIlahkan Mulai");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pilih Mode");
  delay(4000);
  mp3_play(02);
////  delay(9000);
}

void servoNol(){
  servo1.detach();
  servo2.detach();
  servo3.detach();
}

void loop() {
//   unsigned long currentMilis = millis();
//  if(currentMilis - previousMillis >= interval){
//    previousMillis = currentMilis;
//    
//    dataNode = bacaDataNode();
//    Serial.println(dataNode);  
//  }
  char key = keypad.getKey();
//  servoNol();
  switch(key){
    case '1' :
//      mp3_play(04);
      servoNol();
      lcd.clear();lcd.setCursor(0,1);lcd.print("Mode = Pinjam");
      delay(1000);
      lcd.clear();lcd.setCursor(0,0);lcd.print("Letakkan Kartu Anda");
      delay(1000);
      stat = "Pinjam";
      prosesKrmData(stat);
//      dataNode = "";
      IDTAG = "";
//      dataNode1 = "";
//      kirim = "";
    break;
    case '2' :
//      mp3_play (05);
      servoNol();
      lcd.clear();lcd.setCursor(0,1);lcd.print("Mode = Pengembalian");
      delay(1000);
      lcd.clear();lcd.setCursor(0,0);lcd.print("Letakkan Kartu Anda");
      delay(1000);
      stat = "Balik";
      prosesKrmData(stat);
//      dataNode = "";
      IDTAG = "";
//      dataNode1 = "";
//      kirim = "";
    break;
    case '3' :
      servoNol();
      lcd.clear();lcd.setCursor(0,1);lcd.print("Mode = Daftar");
      delay(1000);
      lcd.clear();lcd.setCursor(0,0);lcd.print("Letakkan Kartu Anda");
      delay(1000);
      stat = "Daftar";
      prosesKrmDataDaftar(stat);
//      dataNode = "";
      IDTAG = "";
//      dataNode1 = "";
//      kirim = "";
    break; 
    case '*' :
      servoNol();
    break;
  }
  Serial.println(dataNode);
  keypass = false;
  
}


void prosesKrmData(String stat){
    // Baca Rfid
    
    if(! mfrc522.PICC_IsNewCardPresent()){
      return ;
    }
    if(! mfrc522.PICC_ReadCardSerial()){
      return ;
    }
    
    for(byte i=0; i<mfrc522.uid.size; i++)
    {
      IDTAG += mfrc522.uid.uidByte[i];
    }
    lcd.clear();lcd.setCursor(0,0);lcd.print("ID ");lcd.print(IDTAG);
    delay(1000);
    // Proses Masukkan Password  
    lcd.clear();lcd.setCursor(0,0);lcd.print("Masukkan Password");
    delay(500);
    statKeypad = "pass";
    prokey = ProsesKeypad(statKeypad);
    delay(500);
    // Proses Masukkan Jumlah Pinjam  
    lcd.clear();lcd.setCursor(0,0);lcd.print("Jumlah Pinjam");
    nilaiPass = 0;
    statKeypad = "jumlah";
    jml = ProsesKeypad(statKeypad);
    delay(500);
    // Proses Pemilihan Lemari
    lcd.clear();lcd.setCursor(0,0);lcd.print("Pilih Lemari");
    nilaiPass = 0;
    statKeypad = "lemari";
    lmr = ProsesKeypad(statKeypad);
    // Proses Kirim Data Ke Nodemcu
    kirim = IDTAG + '#' + prokey + '#' + jml + '#' + lmr + '#' + stat ;
    Serial1.println(kirim);
    lcd.clear();lcd.setCursor(0,0);lcd.print("Data Dikirim");
    delay(500);  
    nilaiPass = 0;
    // respon dari nodemcu
    delay(5000);
    dataNode = bacaDataNode();
    delay(200);
    if(dataNode != NULL){
      Serial.println(dataNode);
      for(int i = 0; i <= dataNode.length(); i++){
        char delimiter = '#';
        if(dataNode[i] != delimiter){
          arrNode[indexNode] += dataNode[i];    
        }else{
          indexNode++;
        }
      }
      Serial.println(arrNode[0]);
      Serial.println(arrNode[1]);
      if(arrNode[0] == "Berhasil"){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(arrNode[0]);
        if(arrNode[1] == "1"){
          servo3.attach(8);
          servo3.write(140);
        }else if(arrNode[1] == "2"){
          servo3.attach(7);
          servo3.write(140);
        }else if(arrNode[1] == "3"){
          servo3.attach(6);
          servo3.write(140); 
        }
//        mp3_play (07);
        delay(5000);
        servo1.write(0);
        servo2.write(0);
        servo3.write(0);
        delay(1000);
        servo1.detach();
        servo2.detach();
        servo3.detach();
        cetak(String(IDTAG), String(prokey), String(jml), String(lmr), String(stat));
        arrNode[0] = "";
        arrNode[1] = "";
        indexNode = 0;
        dataNode = "";
        dataNode1 = "";
        kirim = "";
        lcd.clear();lcd.setCursor(0,0);lcd.print("Pilih Mode");
        pinMode(resetMega, OUTPUT);
        digitalWrite(resetMega, HIGH);
        delay(250);
      }else{
        lcd.clear();lcd.setCursor(0,0);lcd.print("Tidak Ada Stock");
        delay(2000);
        lcd.clear();lcd.setCursor(0,0);lcd.print("Pilih Mode");
        arrNode[0] = "";
        arrNode[1] = "";
        indexNode = 0;
        Serial1.flush();
        dataNode = "";
        dataNode1 = "";
        kirim = "";
        pinMode(resetMega, OUTPUT);
        digitalWrite(resetMega, HIGH);
        delay(250);
      }   
      
    }else{
//      mp3_play (07);
      lcd.clear();lcd.setCursor(0,0);lcd.print("Data Kosong");
      delay(2000);
      lcd.clear();lcd.setCursor(0,0);lcd.print("Pilih Mode");
      Serial1.flush();
      dataNode = "";
      dataNode1 = "";
      indexNode = 0;
       kirim = "";
       pinMode(resetMega, OUTPUT);
       digitalWrite(resetMega, HIGH);
      delay(250);
    }
}

void prosesKrmDataDaftar(String stat){
  
  // Baca Rfid
  if(! mfrc522.PICC_IsNewCardPresent()){
    return ;
  }
  if(! mfrc522.PICC_ReadCardSerial()){
      return ;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  for(byte i=0; i<mfrc522.uid.size; i++)
  {
    IDTAG += mfrc522.uid.uidByte[i];
  }
  lcd.clear();lcd.setCursor(0,0);lcd.print("ID ");lcd.print(IDTAG);
  delay(1000);
  // Proses Masukkan Password  
  lcd.clear();lcd.setCursor(0,0);lcd.print("Masukkan Password");
  delay(1000);
  statKeypad = "pass";
  prokey = ProsesKeypad(statKeypad);
  delay(1000);
  Serial.println(stat);
  kirim = IDTAG + '#' + prokey + '#' + stat ;
  Serial1.println(kirim);
  lcd.clear();lcd.setCursor(0,0);lcd.print("Data Dikirim");
  delay(1000);  
}

void cetak(String idtag, String pass, String jumlah, String lemari, String status1){
  lcd.clear();lcd.setCursor(0,0);lcd.print("Cetak Struk");
  printer.setSize('L');
  printer.justify('C');
  printer.println(F("PT.Sawit Padang"));
  printer.println(F("Sumatera Barat"));
  printer.setSize('M');
  printer.println(F("Ernita Meliana"));
  printer.println(F("082287777099"));
  printer.setSize('S');
  printer.justify('L');
  printer.print(F("ID     = "));
  printer.println(idtag);
  printer.print(F("Jumlah = "));
  printer.println(jumlah);
  printer.print(F("Lemari = "));
  printer.println(lemari);
  printer.print(F("Status = "));
  printer.println(status1);
  printer.println(F(""));
  printer.println(F("Terima Kasih"));
  printer.feed(2);
  printer.sleep();
  delay(3000L);
  printer.wake();
  printer.setDefault();
}

long int ProsesKeypad(String statKeypad){
  
  while(1){
    char key = keypad.getKey();
    switch(key){
      case '0' ... '9' :
        lcd.clear();
        nilaiPass = nilaiPass * 10 + (key - '0');
        if(statKeypad == "pass"){
          lcd.setCursor(0,1);lcd.print("Pass = ");lcd.print(nilaiPass);  
        }else if(statKeypad == "jumlah"){
          lcd.setCursor(0,1);lcd.print("Jumlah = ");lcd.print(nilaiPass);
        }else if(statKeypad == "lemari"){
          lcd.setCursor(0,1);lcd.print("No = ");lcd.print(nilaiPass);
        }
      break;
      case '#' :
          return nilaiPass;
       break;
       case '*' :
        lcd.clear();
        nilaiPass = 0;
       break;
    }
  }
}

String bacaDataNode(){
  
  if(Serial1.available() > 0) {
    dataNode1 += Serial1.readStringUntil('\n');
  }
  dataNode1.trim();
  return dataNode1;
}
