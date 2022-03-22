// 최종

#include <Adafruit_NeoPixel.h>

int swc1 = 11;  // switch 11번핀. 거리감지
int swc2 = 12;  // switch2 12번핀. 스피커
//int swc3 = 13;  // switch3 13번핀. LED
int bg = 13;  // 초기값. 택트스위치. 13번핀.
#define PIN 7          // 제어 신호핀
#define NUMPIXELS 12   // 제어하고 싶은 LED 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int vib = 6;  // 진동 6번핀
int buzz = 10;  // 피에조 부저 10번
int t = 8;  // trig 8번
int e = 9;  // echo 9번
int tt = 2;  // 계단 trig
int et = 3;  // 계단 echo
long Dur;
long Durt;
long dt;  // 초음파2 거리 계산
long avr;  // 초기 거리
int lock1;  // 스위치 1의 상태
int lock2;  // 스위치 2의 상태
int lock3;  // 스위치 3의 상태
int tact;   // 택트 스위치의 상태
// 조도센서 A3

void setup() {
  pinMode(swc1, INPUT);
  pinMode(swc2, INPUT);
  pinMode(bg, INPUT_PULLUP);
  pinMode(t,OUTPUT);
  pinMode(e,INPUT);
  pinMode(tt,OUTPUT);
  pinMode(et,INPUT);
  pinMode(vib,OUTPUT);
  pinMode(buzz,OUTPUT);
  Serial.begin(9600);
  pixels.begin();

  
}

void loop() {

  // 조도센서
  int x = analogRead(A3);



// 1) 거리 감지. 스위치1

  // 스위치1
  lock1 = digitalRead(11);
  if(lock1 == 1) {  // 스위치 눌렀을 때
  
    // 초음파센서1
    digitalWrite(t,LOW);
    delayMicroseconds(2);
    digitalWrite(t,HIGH);
    delayMicroseconds(10);
    digitalWrite(t,LOW);
    Dur = pulseIn(e,HIGH);
    long dist=((Dur/2.9)/2)*0.1;

    // 거리에 따른 진동, 조도에 따른 led
    if(dist<=100){  // 거리
      if(x<400){   // 조도
        for(int i=0;i<NUMPIXELS;i++){
          if(i%2==1){
            pixels.setPixelColor(i, pixels.Color(150,180,100));
            pixels.show();}}}
      else{
        pixels.clear();
        pixels.show();}
      analogWrite(vib,250);
    }
    else if(dist>100 && dist<=200){
      if(x<400){
        for(int i=0;i<NUMPIXELS;i++){
          if(i%2==1){
            pixels.setPixelColor(i, pixels.Color(150,180,100));
            pixels.show();}}}
      else{
        pixels.clear();
        pixels.show();}
        analogWrite(vib,200);
    }
    else if(dist>200 && dist<=300){
      if(x<400){
        for(int i=0;i<NUMPIXELS;i++){
          if(i%2==1){
            pixels.setPixelColor(i, pixels.Color(150,180,100));
            pixels.show();}}}
      else{
        pixels.clear();
        pixels.show();}
      analogWrite(vib,150);
    }
    else{
      pixels.clear();
      pixels.show();
      analogWrite(vib,0);
    }
  }
  else{  // 스위치 눌러지지 않았을 때
    pixels.clear();
    pixels.show();
    analogWrite(vib,0);
  }
  delay(20);




// 2) 계단 감지. 스위치2

  // 스위치2
  lock2 = digitalRead(12);
  if(lock2 == 1) {  // 스위치 눌렀을 때


// 계단 감지 초음파센서 기본값
  tact = digitalRead(13);
  if(tact == 1) {  // 택트스위치 눌렀을 때

    digitalWrite(tt,LOW);
    delayMicroseconds(2);
    digitalWrite(tt,HIGH);
    delayMicroseconds(10);
    digitalWrite(tt,LOW);
    Durt = pulseIn(et,HIGH);
    avr =((Durt/2.9)/2)*0.1;
    delay(100);
    Serial.print(avr);
    Serial.println("nn");
  }
  else {
      Serial.print(avr);
      Serial.println("kk");
  }


    
    // 초음파센서2
      digitalWrite(tt,LOW);
      delayMicroseconds(2);
      digitalWrite(tt,HIGH);
      delayMicroseconds(10);
      digitalWrite(tt,LOW);
      Durt = pulseIn(et,HIGH);
      long dt=((Durt/2.9)/2)*0.1;

    // 거리에 따른 진동, 조도에 따른 led
    if(dt>(avr+20)){  // 거리가 멀면 (내려가는 계단)
        tone(buzz, 262);
        analogWrite(vib,250);  // 진동이 300;
    }
    else if(dt<(avr-20)){
      if(x<400){   // 조도
        for(int i=0;i<NUMPIXELS;i++){
          if(i%2==1){
            pixels.setPixelColor(i, pixels.Color(150,180,100));
            pixels.show();}}}
      else{
        pixels.clear();
        pixels.show();}
      noTone(buzz);
      analogWrite(vib,250);
    }
    else{
      pixels.clear();
      pixels.show();
      noTone(buzz);
      analogWrite(vib,0);
    }
  }
  else{  // 스위치 눌러지지 않았을 때
    pixels.clear();
    pixels.show();
    noTone(buzz);
    analogWrite(vib,0);
  }
  delay(20);

}
