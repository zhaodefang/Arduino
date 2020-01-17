/*
8888LED 显示演示
 */
//各种显示图形
int dat[][7] = {
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}, //9
  {0,0,0,0,0,0,1},//10:中-
  {1,0,0,1,1,1,1},//11:[-
  {1,1,1,1,0,0,1}, //12:-]
  {1,0,0,0,0,0,0},//13:上-
  {0,0,0,1,0,0,0},//14:下_
  {0,0,0,0,0,0,0},//15:null
};
#define D_ON LOW
#define D_OFF HIGH
const int DPosPins[] = {6,5,4,3};//位数
const int DPosCount = 4;
const int DPins[] = {7,8,9,10,11,12,13};//每个8的脚位
const int DPinCount = sizeof(DPins) / 2;
int Speed_Animation_timer=500;

void setup() {
  Serial.begin(115200);
  for(int j=0;j<DPosCount;j++){
    pinMode(DPosPins[j], OUTPUT);
    digitalWrite(DPosPins[j], HIGH);
  }
  for (int i = 0; i < DPinCount; i++) { 
    pinMode(DPins[i], OUTPUT);
    digitalWrite(DPins[i], HIGH);
  }
}


int showwhat(4);
void loop() {
  switch(showwhat){
    case 0:
      showall(millis()/100);
      break;
    case 1:{
      int a[] = {0,1,2,3};
      showdata( a);
      break;
    }
    case 2:{
      int an[][4] = {
                {-1,-1,-1,11},
                {-1,-1,11,10},
                {-1,11,10,10},
                {11,10,10,10},
                {10,10,10,-1},
                {10,10,-1,-1},
                {10,-1,-1,-1},
                {-1,-1,-1,-1}
                };
      showanimation(an,(sizeof(an)/8));
      break;
    }
   
    case 3:{
        int a1[][4] = {
                    {13,13,13,13},
                    {10,10,10,10},
                    {14,14,14,14},
                    {15,15,15,15}
                    };
        static bool isok3(false);
        isok3 = showanimation(a1,(sizeof(a1)/8));
        break;
    }
     case 4: {
        int ra[] = {0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1};
        runanimation(ra,sizeof(ra)/2);
        break;
     }
    
  }
 
}

void OffAll()
{
  for(int i=1;i<=4;i++) digitalWrite(DPosPins[i-1], D_OFF);
}
void showdat(int dpos,int d){
  if(dpos <= 0 || dpos > DPosCount) return;
  if(d < 0 || d > 9) return;
  digitalWrite(DPosPins[dpos-1], D_ON);
  for(int i=0;i<DPinCount;i++) digitalWrite(DPins[i],dat[d][i]);
}
int showindex = 1;
void showall(int d){
  int alld[] = {0,
                d%10,
                (d%100) / 10,
                (d%1000) / 100,
                (d%10000) / 1000       
              };
   for(int i=4;i>=1;i--){
      if(alld[i] > 0) break;
      alld[i] = -1;
   }
   if(showindex > 4) showindex = 1;
   showdat(showindex,alld[showindex]);
   delayMicroseconds(5000); 
   digitalWrite(DPosPins[showindex-1], D_OFF);
   showindex++;
 //  OffAll();
}


//ds[4] 要显示的四位序列号
void showdata(int ds[4]){
  static int dsindex(0);
  if(dsindex >=4) dsindex = 0;
  if(ds[3-dsindex] >= 0)
  {
    digitalWrite(DPosPins[dsindex], D_ON);
    for(int i=0;i<DPinCount;i++) digitalWrite(DPins[i],dat[ds[3-dsindex]][i]);
    delayMicroseconds(5000); 
    digitalWrite(DPosPins[dsindex], D_OFF);
  }
  dsindex++;
}

//int an[][4] 要轮流显示的序列号组
bool showanimation(int an[][4],int s){
  static int anindex(0);
  static long oldtime = millis();
  bool re(false);
  if(anindex >= s) 
  {
    anindex = 0;
    re = true;
  }
  showdata(an[anindex]);
  if(millis() - oldtime > Speed_Animation_timer){
    oldtime = millis();
    anindex++;
  }

  return re;
 }

//an[] 跑马显示的序列号组
void runanimation(int an[],int s){
  static int anindex(0);
  static long oldtime = millis();
  int ds[4];
  for(int i=0;i<4;i++) 
  {
    if(anindex+i >= s) ds[i] = an[anindex+i-s];
    else ds[i] = an[anindex+i];
  }
  if(anindex >= s) anindex = 0;
  showdata(ds);
  if(millis() - oldtime > Speed_Animation_timer){
    oldtime = millis();
    anindex++;
  }
}
