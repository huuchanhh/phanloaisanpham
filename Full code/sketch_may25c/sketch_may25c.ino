#include <Wire.h> 
#include <Servo.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2); 
 
//-----ĐKĐC 
int enb = 11;//11 
int in3 = 12;//12 
int in4 = 13;//13 
int giatri; 
int bamxung; 
 
//-----Đếm 
int giatridem; 
int gtmacdinh = 1; 
int dem; 
 
//-----cảm biến 
int cambien = 10; //10 
 
//-----Đếm màu 
int spR=0,spG=0,spB=0; 
 
//Reset 
int start = 9;//9 
int gtstart; 
 
//strat 
// int start =8; 
// int gtstart; 
 
//-----servo 
Servo myservo1, myservo2; 
 
//-----TCS3200 
#define S0 4 
#define S1 2 
#define S2 6 
#define S3 7 
#define sensorOut 5 
int PW = 0; 
int colour=0; 
 
void hienthiLCD() 
{  
  lcd.setCursor(3,1);   lcd.print(spR);   
  lcd.setCursor(8,1);   lcd.print(spG);   
  lcd.setCursor(13,1);   lcd.print(spB);
} 
void setup()  
{ 
  Serial. begin (9600); 
 
  //-----DKDC 
  pinMode (enb, OUTPUT); 
  pinMode (in3, OUTPUT); 
  pinMode (in4, OUTPUT); 
 
  //start 
  pinMode(start, INPUT_PULLUP); 
   
  //dem 
  pinMode(cambien, INPUT); 
   
  //-----MÀU SẮC 
  pinMode(S0, OUTPUT); 
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT); 
  pinMode(S3, OUTPUT); 
  pinMode(sensorOut, INPUT); 
   
  myservo1.attach(8); 
  myservo2.attach(3);  
  //-----TẦN SỐ 20% 
  digitalWrite(S0, HIGH); 
  digitalWrite(S1, LOW); 
   
  lcd.init(); 
  lcd.backlight(); 
  lcd.setCursor(0,0); 
  lcd.print("     DANH CHANH     ");delay(1000); 
  lcd.setCursor(0,1); 
  lcd.print("      DO AN 1    ");delay(1000); 
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("HE THONG DEM VA");delay(700); 
  lcd.setCursor(0,1); 
  lcd.print("PHAN LOAI S.PHAM"); 
  delay(2500); 
  lcd.clear(); 
} 

// điều khiển động cơ

void servo()
{
    myservo2.write(104);
   delay(2000);                 
   myservo2.write(55);
   delay(1000);
}
void loop()  
{ 
   
  gtstart = digitalRead(start); 
  if(gtstart == 1) 
  { 
    digitalWrite (in3, LOW);  
    digitalWrite (in4, LOW); 
    lcd.setCursor(0,0); 
    lcd.print("   PRESS START  "); 
    lcd.setCursor(0,1); 
    lcd.print("                "); 
  } 
  else 
  { 
  
   lcd.clear(); 
    lcd.setCursor(1,0); 
    lcd.print("SO LUONG SP:"); 
    //Serial.println(dem); 
    // lcd.setCursor(9,0);  
    // lcd.print(dem); 
    lcd.setCursor(0,1); 
    lcd.print(" R:   G:   B:"); 
    hienthiLCD(); 
      
    hienthiLCD();
    servo();
    
    colour = readColour(); 
    
    switch (colour)  
    { 
    case 1: myservo1.write(75); break; 
    case 2: myservo1.write(90); break; 
    case 3: myservo1.write(105); break; 
    }
    delay(1000);
    myservo2.write(15);
   delay(2500);
  
  } 
  // dem san pham len 1
      if(colour==1) 
      spR ++; 
      if(colour==2) 
      spG ++; 
      if(colour==3) 
      spB ++;
      
} 
 
//---------màu 
int readColour()  
{ 
  //-----KHỞI TẠO MÀU ĐỎ
 digitalWrite(S2, LOW); 
  digitalWrite(S3, LOW); 
  PW = pulseIn(sensorOut, LOW);   
  int R = PW; 
  //-----IN MÀU ĐỎ LÊN MH 
  Serial.print("R = ");          
  Serial.print(PW);              
  Serial.print("  "); 
  delay(50); 
   
  //-----KHỞI TẠO MÀU LỤC 
  digitalWrite(S2, HIGH); 
  digitalWrite(S3, HIGH); 
  PW = pulseIn(sensorOut, LOW);  // ĐỌC ĐỘ RỘNG XUNG ĐẦU RA 
  int G = PW; 
  //-----IN MÀU LỤC LÊN MH 
  Serial.print("G = ");           
  Serial.print(PW);               
  Serial.print("  "); 
  delay(50); 
   
  //-----KHỞI TẠO MÀU LAM 
  digitalWrite(S2, LOW); 
  digitalWrite(S3, HIGH); 
  PW = pulseIn(sensorOut, LOW);   
  int B = PW; 
//-----IN MÀU LAM LÊN MH 
  Serial.print("B = ");           
  Serial.print(PW);               
  Serial.print("   colour: ");    
  Serial.print(" "); 
  delay(50); 
   
  if(R < 60 && R > 10 && G < 130 && G> 80 && B < 100 && B > 50 ) 
  { 
    colour = 1;              // Red     
  } 
  if(R < 170 && R > 80 && G < 150 && G > 90 && B < 90 && B > 40) 
  { 
    colour =  3;            // Blue 
  } 
  if (R < 130 && R > 85 && G < 80 && G > 30 && B < 110 && B > 60) 
  { 
    colour =  2;            // Green     
  } 
   
  return colour; 
   
}
//--------- Hàm reset  
void resetBoard() 
{ 
  asm volatile ("jmp 0"); //Nhảy về dòng đầu tiên của chương trình 
} 
