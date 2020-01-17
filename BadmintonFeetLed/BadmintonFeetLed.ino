//
//羽毛球步伐锻炼用
//原理:左右分别放置LED灯和按纽,LED灯随机亮起,按下相应的按纽才会灭掉.
//亮起的顺序和间隔是随机的,速度可以通过旋纽控制.
//
//LED灯和BUTTON脚位存储
const int ButtonPins[] = { 8, 9 }; //左右按纽的脚位
const int LedPins[] = { 10, 11 }; //左右LED灯的脚位
const int LedPinsCount = sizeof(LedPins) / 2; //LED灯数目
int Ledindex = -1;  //当前亮起的LED

const int SpeedSensor = A0;//调速器
//速度调整档位
const int LedTimers[] = { 6000,
						  5500,
						  5000,
						  4500,
						  4000,
						  3500,
						  3000,
						  2500,
						  2000,
						  1500,
						  1000
};
const int LedTimerCount = sizeof(LedTimers) / 2;
//当前档位
int LedTimerIndex = 5;

const int LedSpeedPin = 5;//用LED的亮度表示速度


// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin LED_BUILTIN as an output.
	randomSeed(analogRead(5));
	Serial.begin(115200);

	Init();
}

//初始化各器件
void Init() {
	pinMode(LedSpeedPin, OUTPUT);
	for (int i = 0; i < LedPinsCount; i++) {
		pinMode(LedPins[i], OUTPUT);
		digitalWrite(LedPins[i], LOW);

		pinMode(ButtonPins[i], INPUT);
	}
	Ledindex = -1;

	//初始化完成后闪灯提醒
	FlickLed();
}

void loop() {
	//调整速度
	AdjustSpeed();
	//如果还没有亮灯,则开始动作
	if (Ledindex < 0) {
		int timer = random(LedTimers[LedTimerIndex] - 1000, LedTimers[LedTimerIndex] + 1000);
		Ledindex = random(0, 2);
		delay(timer);
		OnLed(Ledindex);
	}
	//如果当前有亮灯,则去等待按纽按下
	if (Ledindex >= 0) {
		int buttonState = digitalRead(ButtonPins[Ledindex]);
		if (buttonState == HIGH) {
			OffLed(Ledindex);
			Ledindex = -1;
		}
	}
//	ShowInfo();
}

void OnLed(int index)
{
	digitalWrite(LedPins[index], HIGH);
}
void OffLed(int index)
{
	digitalWrite(LedPins[index], LOW);
}
void OnAllLed()
{
//  digitalWrite(LedSpeedPin, HIGH);
	for (int i = 0; i < LedPinsCount; i++) digitalWrite(LedPins[i], HIGH);
  
}
void OffAllLed()
{
//  digitalWrite(LedSpeedPin, LOW);
	for (int i = 0; i < LedPinsCount; i++) digitalWrite(LedPins[i], LOW);
 
}

//速度调整函数
void AdjustSpeed()
{
	int data = analogRead(SpeedSensor);
	int newindex = map(data, 0, 1023, 0, LedTimerCount - 1);
	LedTimerIndex = newindex;
  int ni = map(data, 0, 1023, 1, 255);
	analogWrite(LedSpeedPin,ni);
//  Serial.print(data);
//  Serial.print(" : ");
//  Serial.println(newindex);
}
//对LED进行轮流闪烁
int OnNextLed(int index)
{
	if (index >= LedPinsCount) index = 0;
	OffAllLed();
	OnLed(index);
	return index + 1;
}
//对所有的LED灯进行闪烁
void FlickLed()
{
	int j = 0;
	for (int i = 0; i < 10; i++) {
		j = OnNextLed(j);
		delay(100);
	}
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
void ShowInfo() {
	Serial.print(" LedTimerIndex:");
	Serial.print(LedTimerIndex);
	Serial.print(" Ledindex:");
	Serial.print(Ledindex);
	if (Ledindex < 0) return;
	int buttonState = digitalRead(ButtonPins[Ledindex]);
	Serial.print(" Button:");
	Serial.print(ButtonPins[Ledindex]);
	Serial.print(" Button:");
	Serial.print(buttonState);

	Serial.println();
}
