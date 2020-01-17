/*
8LED 显示演示
 */
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
  {0,0,0,0,0,0,1},//10:中-
  {1,0,0,1,1,1,1},//11:[-
  {1,1,1,1,0,0,1}, //12:-]
  {1,0,0,0,0,0,0},//13:上-
  {0,0,0,1,0,0,0},//14:下_
  {0,0,0,0,0,0,0},//15:null
};
const int datsize = sizeof(dat) / 14;
#define D_ON HIGH
#define D_OFF LOW

const int DPins[] = {5,6,7,1,2,3,4,8};//每个8的脚位
const int DPinCount = sizeof(DPins) / 2;


void showdat(int d){
  if(d < 0 || d > 9) return;
  for(int i=0;i<7;i++) digitalWrite(DPins[i],dat[d][i]);
}


#define SPEEDBUTTONPIN 6

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(115200);
  for (int i = 0; i < DPinCount; i++) { 
    pinMode(DPins[i], OUTPUT);
    digitalWrite(DPins[i], D_OFF);
  }
 // Serial.println(datsize);

//  pinMode(SPEEDBUTTONPIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  static int i(0);
     showdat((i++)%10);
      delay(500);
  if(digitalRead(SPEEDBUTTONPIN) == HIGH){
 
  }
}
