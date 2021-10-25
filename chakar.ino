/* Ekim 2021 Dr.TRonik YouTube
 * RF kumandalı, butonlu, 6 modlu 
 * 7 segment led mod göstergeli
 * Bir çakar denemesi...
 */

 // Kütüphane (Library) ve global tanımlamalar 
 
#include <RCSwitch.h> //Uzaktan kumanda için kullandığımız kütüphane 433Mhz...
RCSwitch mySwitch = RCSwitch(); //RF Modül ismini belirtelim...

#define mavi     12    //Mavi Led 1.grup pin 12
#define mavi_1   11    //Mavi Led 2.grup pin 11
#define mavi_2   10    //Mavi Led 3.grup pin 10

#define beyaz     9    //Beyazi Led pin 9

#define kirmizi   8    //Kırmızı Led 1.grup pin 8
#define kirmizi_1 7    //Kırmızı Led 2.grup pin 7
#define kirmizi_2 6    //Kırmızı Led 3.grup pin 6

#define button    4    //Butonun bağlandığı pin 4

int buton_sayac = 0;   //Butonumuzun kaç defa basıldığı değerini tutan değişken
int btn_degeri =  0;   // Butonun LOW ya da HIGH olduğunu tutan değişken

int x = 52; //Bekleme süresi 37

int latchPin = A0; //pin 12 on the 595
int dataPin = A1; //pin 14 on the 595
int clockPin = A2; //pin 11 on the 595


//-----SET UP---SET UP---SET UP---

void setup() {
  //Serial.begin(9600);
  mySwitch.enableReceive(0); // Rf alıcı, nano kart 0.kesme pini olan D2'a bağlandı...
  
  //Tanımladığımız led pinlerini for döngüsü ile çıkış olarak ayarlayalım
  for (int i = 12; i > 5; i--) 
  {
    pinMode(i, OUTPUT) ;
  }
  
  pinMode (latchPin, OUTPUT);
  pinMode (dataPin, OUTPUT);
  pinMode (clockPin, OUTPUT);


  pinMode(4, INPUT_PULLUP);//Tanımladığımız buton pinini giriş olarak ayarlayalım, ve pull up direncini tanımlayalım...
  btn_degeri == HIGH; // İlk açılışta buton değerimiz HIGH / 1 olsun...


  
}

//-----VOID LOOP---VOID LOOP---VOID LOOP---

void loop() {

  //______Buton Sayacı_____

  btn_degeri = digitalRead(button);//Buton değerini oku ve "btn_degeri" ne ata...
  //Serial.println(buton_sayac);
  if (btn_degeri == LOW) //Butona basıldığında sayaç değişkenini bir arttır...
  { buton_sayac = buton_sayac + 1;
    delay (500); //Buton değeri LOW değeri alır almaz sayaç bir artar ve 500 ms bekler ki elektriksel parazitlerden etkilenmesin... 

    if (buton_sayac > 5) //Eğer butona 5 defa basılırsa (0, 1, 2, 3, 4)
    {
      buton_sayac = 0; // 6. basılışta buton değeri başa döner ve 0 değerini alır

    }
   // Serial.println(buton_sayac);
  }
  
  //____RF MODUL_____BAŞLANGIÇ____
  if (mySwitch.available()) 
    {    
//    Serial.print("Received ");
//    Serial.print( mySwitch.getReceivedValue() );
//    Serial.print(" / ");
//    Serial.print( mySwitch.getReceivedBitlength() );
//    Serial.print("bit ");
//    Serial.print("Protocol: ");
//    Serial.println( mySwitch.getReceivedProtocol() );
    
    if (mySwitch.getReceivedValue() == 5592512)  buton_sayac = 0; // 1.Tuşa basıldığında, sayac değeri 0 olur...
    if (mySwitch.getReceivedValue() == 5592368)  buton_sayac = 1; // 2.Tuşa basıldığında, sayac değeri 1 olur...
    if (mySwitch.getReceivedValue() == 5592560)  buton_sayac = 2; // 3.Tuşa basıldığında, sayac değeri 2 olur...
    if (mySwitch.getReceivedValue() == 5592332)  buton_sayac = 3; // 4.Tuşa basıldığında, sayac değeri 3 olur...
    if (mySwitch.getReceivedValue() == 5592524)  buton_sayac = 4; // 5.Tuşa basıldığında, sayac değeri 4 olur...
    if (mySwitch.getReceivedValue() == 5592380)  buton_sayac = 5; // 6.Tuşa basıldığında, sayac değeri 5 olur...
    
    mySwitch.resetAvailable();
    }
//____RF MODUL_____SON____

//_____SWITCH CASE BAŞLANGIÇ_____

  switch (buton_sayac) //Anahtarımız buton sayac değişkeni
  {
    case 0: //Anahtarımız 0 döndürürse durum_0 fonsiyonunu çalıştır...
      durum_0();
       //0
//  digitalWrite(latchPin, LOW);
//  shiftOut(dataPin, clockPin, MSBFIRST, 64);
//  digitalWrite(latchPin, HIGH);

        //1
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 121);
      digitalWrite(latchPin, HIGH);
  
      break;

    case 1: //Anahtarımız 1 döndürürse durum_1 fonsiyonunu çalıştır...
      durum_1();
       
      //2
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 36);
    digitalWrite(latchPin, HIGH);
      break;

    case 2: //Anahtarımız 2 döndürürse durum_2 fonsiyonunu çalıştır...
      durum_2();
      //3
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 48);
    digitalWrite(latchPin, HIGH);
      break;

    case 3: //Anahtarımız 3 döndürürse durum_3 fonsiyonunu çalıştır...
      durum_3();
      digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 25);
  digitalWrite(latchPin, HIGH);
      break;

    case 4: //Anahtarımız 4 döndürürse durum_4 fonsiyonunu çalıştır...
      durum_4();
      //5
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 18);
  digitalWrite(latchPin, HIGH);
      break;

    case 5: //Anahtarımız 5 döndürürse durum_5 fonsiyonunu çalıştır...
      durum_5();
      //6
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 2);
  digitalWrite(latchPin, HIGH);
 
      break;

    default:
      //Eğer bunlardan hiçbiri olmazsa buraya çalışacak kodları belirtebiliriz...
      break;
  }
}

//____FONKSİYON TANIMLARI____

void durum_0() {
  for (int tekrar = 0; tekrar < 4; tekrar++) {
    digitalWrite (mavi, 1);
    digitalWrite (mavi_1, 1);
    digitalWrite (mavi_2, 1);
    digitalWrite (beyaz, 1);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 0);
    digitalWrite (kirmizi_2, 0);
    delay (x);
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 0);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 0);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 0);
    digitalWrite (kirmizi_2, 0);
    delay (x);
  }
  for (int tekrar = 0; tekrar < 4; tekrar++) {
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 0);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 1);
    digitalWrite (kirmizi, 1);
    digitalWrite (kirmizi_1, 1);
    digitalWrite (kirmizi_2, 1);
    delay (x);
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 0);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 0);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 0);
    digitalWrite (kirmizi_2, 0);
    delay (x);
  }
}
void durum_1() {
  for (int tekrar = 0; tekrar < 3; tekrar++) {
    digitalWrite (mavi, 1);
    digitalWrite (mavi_1, 1);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 1);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 1);
    digitalWrite (kirmizi_2, 1);
    delay (x);
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 0);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 0);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 0);
    digitalWrite (kirmizi_2, 0);
    delay (x);
  }
  for (int tekrar = 0; tekrar < 3; tekrar++) {
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 1);
    digitalWrite (mavi_2, 1);
    digitalWrite (beyaz, 1);
    digitalWrite (kirmizi, 1);
    digitalWrite (kirmizi_1, 1);
    digitalWrite (kirmizi_2, 0);
    delay (x);
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 0);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 0);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 0);
    digitalWrite (kirmizi_2, 0);
    delay (x);
  }
}

void durum_2() {  
  digitalWrite (mavi_2, 1);
  digitalWrite (kirmizi, 1);
  delay(x);
  digitalWrite (mavi_1, 1);
  digitalWrite (kirmizi_1, 1);
  delay(x);
  digitalWrite (mavi, 1);
  digitalWrite (kirmizi_2, 1);
  delay(x),
  digitalWrite (beyaz, 1);  
  delay (x);  
  digitalWrite (mavi_2, 0);
  digitalWrite (kirmizi, 0);
  delay(x);
  digitalWrite (mavi_1, 0);
  digitalWrite (kirmizi_1, 0);
  delay(x);  
  digitalWrite (mavi, 0);
  digitalWrite (kirmizi_2, 0);
  delay (x);
}

void durum_3() {
  digitalWrite (mavi, 1);
  digitalWrite (mavi_1, 1);
  digitalWrite (mavi_2, 0);
  digitalWrite (beyaz, 1);
  digitalWrite (kirmizi, 1);
  digitalWrite (kirmizi_1,1);
  digitalWrite (kirmizi_2, 0);
  delay (150);
  digitalWrite (mavi, 0);
  digitalWrite (mavi_1, 1);
  digitalWrite (mavi_2, 1);
  digitalWrite (beyaz, 1);
  digitalWrite (kirmizi, 0);
  digitalWrite (kirmizi_1, 1);
  digitalWrite (kirmizi_2, 1);
  delay (150);
}

void durum_4() {
  for (int tekrar = 0; tekrar < 6; tekrar++) {
    digitalWrite (mavi, 1);
    digitalWrite (mavi_1, 1);
    digitalWrite (mavi_2, 1);
    digitalWrite (beyaz, 1);
    digitalWrite (kirmizi, 1);
    digitalWrite (kirmizi_1, 1);
    digitalWrite (kirmizi_2, 1);
    delay (x);
    digitalWrite (mavi, 0);
    digitalWrite (mavi_1, 0);
    digitalWrite (mavi_2, 0);
    digitalWrite (beyaz, 0);
    digitalWrite (kirmizi, 0);
    digitalWrite (kirmizi_1, 0);
    digitalWrite (kirmizi_2, 0);
    delay (x);
  }
  delay(300);
}

void durum_5() {
  for (int i = 12; i > 5; i--) {
    digitalWrite(i, 1);
    delay(2*x);
      }
      for (int i = 12; i > 5; i--) {
      digitalWrite(i, 0);
      delay(2*x);
    }
}

//Dr.TRonik YouTube...

//5592512  1
//5592368  2
//5592560  3
//5592332  4
//5592524  5
//5592380  6
