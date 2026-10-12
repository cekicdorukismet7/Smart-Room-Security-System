#include <EEPROM.h>

#define trigPin 9
#define echoPin 10
#define sesPin 2
#define ledPin 7


bool alarmAktif = false;

unsigned long alarmBaslangic;

unsigned long sonLedDegisim;
unsigned long sonOlcum;

bool ledDurumu = false;


long eskiMesafe = 0;


int olaySayisi = 0;


unsigned long olcumAraligi = 500;



long mesafeOku()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);


  long sure = pulseIn(echoPin, HIGH, 30000);


  if(sure == 0)
  {
    return 999;
  }


  return sure * 0.034 / 2;
}





void komutKontrol()
{

  if(Serial.available())
  {

    String komut = Serial.readStringUntil('\n');

    komut.trim();



    if(komut == "olay")
    {
      Serial.print("Toplam olay sayisi: ");
      Serial.println(olaySayisi);
    }



    else if(komut == "durum")
    {

      if(alarmAktif)
      {
        Serial.println("ALARM AKTIF");
      }
      else
      {
        Serial.println("SISTEM GUVENLI");
      }

    }



    else if(komut == "sifirla")
    {

      olaySayisi = 0;

      EEPROM.put(0, olaySayisi);


      Serial.println("Olay sayisi sifirlandi");

    }


  }

}






void setup()
{

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(sesPin, INPUT);

  pinMode(ledPin, OUTPUT);


  Serial.begin(9600);



  EEPROM.get(0, olaySayisi);



  if(olaySayisi < 0 || olaySayisi > 10000)
  {
    olaySayisi = 0;
  }



  Serial.println("AKILLI ODA GUVENLIK SISTEMI");

  Serial.println("--------------------------");


  Serial.print("Kayitli olay: ");
  Serial.println(olaySayisi);



  Serial.println("Sistem hazirlaniyor");


  for(int i=20;i>0;i--)
  {
    Serial.print(i);
    Serial.println(" saniye");
    delay(1000);
  }




  eskiMesafe = mesafeOku();


  Serial.print("Baslangic mesafe: ");
  Serial.print(eskiMesafe);
  Serial.println(" cm");



  Serial.println("KORUMA AKTIF");

}

void loop()
{

  komutKontrol();


  unsigned long simdi = millis();



  if(simdi - sonOlcum >= olcumAraligi)
  {

    sonOlcum = simdi;


    long yeniMesafe = mesafeOku();


    bool hareket = false;


    int ses = digitalRead(sesPin);


    bool sesVar = false;




    // Sadece yaklaşmayı algıla

    if(yeniMesafe < eskiMesafe - 10)
    {
      hareket = true;
    }



    // Ses sensörü

    if(ses == LOW)
    {
      sesVar = true;
    }






    // Alarm başlat

    if((hareket || sesVar) && !alarmAktif)
    {


      alarmAktif = true;


      alarmBaslangic = millis();



      olaySayisi++;

      EEPROM.put(0, olaySayisi);




      Serial.println("----------------");


      if(hareket)
      {
        Serial.println("HAREKET ALGILANDI");
      }


      if(sesVar)
      {
        Serial.println("SES ALGILANDI");
      }



      Serial.println("ALARM BASLADI");


      Serial.print("Toplam olay: ");

      Serial.println(olaySayisi);


    }




    // Daha uzak olursa yeni normal mesafe yap

    if(yeniMesafe > eskiMesafe)
    {
      eskiMesafe = yeniMesafe;
    }


  }







  // LED sistemi

  if(alarmAktif)
  {


    unsigned long alarmSuresi =
    (millis()-alarmBaslangic)/1000;



    int hiz;



    if(alarmSuresi < 30)
    {
      hiz = 500;
    }

    else if(alarmSuresi < 50)
    {
      hiz = 200;
    }

    else
    {
      hiz = 80;
    }




    if(millis()-sonLedDegisim > hiz)
    {

      sonLedDegisim = millis();


      ledDurumu = !ledDurumu;


      digitalWrite(ledPin, ledDurumu);

    }


  }





  // Sistem aktif LED göstergesi

  else
  {


    if(millis()-sonLedDegisim > 2000)
    {

      sonLedDegisim = millis();


      ledDurumu = !ledDurumu;


      digitalWrite(ledPin, ledDurumu);

    }


  }








  // Alarm 20 saniye sonra kapanır

  if(alarmAktif && millis()-alarmBaslangic > 20000)
  {


    unsigned long sure =
    (millis()-alarmBaslangic)/1000;



    alarmAktif = false;


    digitalWrite(ledPin, LOW);



    Serial.println("----------------");


    Serial.println("ALARM KAPATILDI");


    Serial.print("Alarm suresi: ");

    Serial.print(sure);

    Serial.println(" saniye");



    Serial.println("Sistem guvenli");



    // Yeni başlangıç mesafesi

    eskiMesafe = mesafeOku();

  }


}
