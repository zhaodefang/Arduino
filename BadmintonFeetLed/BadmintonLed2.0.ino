#include <SCoop.h>
defineTask(TaskTest1);//创建子线程1
defineTask(TaskTest2);//创建子线程2

//各种显示图形
int dat[][7] = {
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 0, 1, 1, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {0, 1, 1, 1, 1, 0, 1}, //3
  {0, 0, 1, 1, 0, 1, 1}, //4
  {0, 1, 1, 0, 1, 1, 1}, //5
  {1, 1, 1, 0, 1, 1, 1}, //6
  {0, 0, 1, 1, 1, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {0, 1, 1, 1, 1, 1, 1}, //9
};
const int datsize = sizeof(dat) / 14;
#define D_ON HIGH
#define D_OFF LOW
const int DPins[] = {5,6,7,1,2,3,4,8};//每个8的脚位
const int DPinCount = sizeof(DPins) / 2;
void showdat(int d){
  if(d < 0 || d > 9) 
  {
    for(int i=0;i<7;i++) digitalWrite(DPins[i],0);
    return;
  }
  for(int i=0;i<7;i++) digitalWrite(DPins[i],dat[d][i]);
}

#define SPEEDPIN A5
int speednow = 5;
//速度调整档位
const int SpeedData[10] = { 0,
              3600,
              3200,
              2800,
              2400,
              2000,
              1500,
              1200,
              1000,
              800
             };

             
//LED灯和BUTTON脚位存储
const int ButtonPins[] = { 11,12 }; //左右按纽的脚位
const int LedPins[] = { 9,10 }; //左右LED灯的脚位
const int LedPinsCount = sizeof(LedPins) / 2; //LED灯数目
int Ledindex = -1;  //当前亮起的LED

void OnAllLed()
{
  for (int i = 0; i < LedPinsCount; i++) digitalWrite(LedPins[i], HIGH);
}
void OffAllLed()
{
  for (int i = 0; i < LedPinsCount; i++) digitalWrite(LedPins[i], LOW);
 }

void FlickLedOnebyone(){
  int c = 2;
  while(c-- >= 0){
    for (int i = 0; i < LedPinsCount; i++) {
      digitalWrite(LedPins[i], HIGH);
      delay(300);
      digitalWrite(LedPins[i], LOW);
    }
  }
}
//对所有的LED灯进行闪烁
void FlickLed()
{
  OffAllLed();
  delay(100);
  OnAllLed();
  delay(100);
  OffAllLed();
  delay(100);
  OnAllLed();
  delay(1000);
  OffAllLed();
}

void TaskTest1::setup()//线程1设定
{

}
//调整速度
void TaskTest1::loop()//线程1循环
{
  static int showtime(0);
  int data = analogRead(SPEEDPIN);
  speednow = map(data, 0, 1023, 1, 9);
  showdat(speednow);
  sleep(100);
}

 
void TaskTest2::setup()//线程2设定
{

}
void TaskTest2::loop()//线程2循环
{
    //如果还没有亮灯,则开始动作
  if (Ledindex < 0) {
    
    int timer = random(SpeedData[speednow] - 200, SpeedData[speednow] + 200);
    Ledindex = random(0, 2);
    sleep(timer);
    beep();
    sleep(200);
    digitalWrite(LedPins[Ledindex], HIGH);
  }
  //如果当前有亮灯,则去等待按纽按下
  if (Ledindex >= 0) {
    int buttonState = digitalRead(ButtonPins[Ledindex]);
    if (buttonState == HIGH) {
      beep_ok();
      digitalWrite(LedPins[Ledindex], LOW);
      Ledindex = -1;
    }
  }
  sleep(100);
}
/*
8LED 显示演示
 */

int speakerPin=0;
#define D0 -1
#define D1 262
#define D2 293
#define D3 329
#define D4 349
#define D5 392
#define D6 440
#define D7 494

#define M1 523
#define M2 586
#define M3 658
#define M4 697
#define M5 783
#define M6 879
#define M7 987

#define H1 1045
#define H2 1171
#define H3 1316
#define H4 1393
#define H5 1563
#define H6 1755
#define H7 1971
//列出全部D调的频率
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

int songs[][2]={
  {M3,1},
  {M2,1},
  {M3,1},
  {M2,1},
   {M3,1}
};
void playsong(int s[][2]){
  int length=5;   //计算长度
  for(int i=0;i<length;i++){
    tone(speakerPin,songs[i][0]);
    delay(200*songs[i][1]);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
    noTone(speakerPin);
  }
  noTone(speakerPin);
}
void beep_begin(){
  FlickLedOnebyone();
  delay(200);
  OnAllLed();
  tone(speakerPin,M3);
  delay(100);   
  noTone(speakerPin);

  OffAllLed();;
  tone(speakerPin,M2);
  delay(100);   
  noTone(speakerPin);

  OnAllLed();
  tone(speakerPin,M3);
  delay(100);   
  noTone(speakerPin);

  OffAllLed();
  tone(speakerPin,M2);
  delay(100);   
  noTone(speakerPin);

  OnAllLed();
  tone(speakerPin,M3);
  delay(100);   
  noTone(speakerPin);

  OffAllLed();
  tone(speakerPin,M2);
  delay(100);   
  noTone(speakerPin);
}
void beep_ok(){
  tone(speakerPin,H2);
  delay(100);   
  noTone(speakerPin);
  tone(speakerPin,H1);
  delay(100);   
  noTone(speakerPin);
}
void beep(){
  tone(speakerPin,H7);
  delay(100);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
  noTone(speakerPin);
}
void setup() {

  for (int i = 0; i < DPinCount; i++) { 
    pinMode(DPins[i], OUTPUT);
    digitalWrite(DPins[i], D_OFF);
  }
  for (int i = 0; i < LedPinsCount; i++) { 
    pinMode(LedPins[i], OUTPUT);
    digitalWrite(LedPins[i], D_OFF);
    pinMode(ButtonPins[i], INPUT);
  }
    pinMode(SPEEDPIN, INPUT);
    pinMode(speakerPin,OUTPUT);
    
//  Serial.begin(57600); 
//  while (!Serial); 
//    showdat(5);
    
//    FlickLed();

    beep_begin();

    mySCoop.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  mySCoop.sleep(100);
}
