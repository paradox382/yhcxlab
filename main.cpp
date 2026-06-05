#include <Arduino.h>  // PlatformIO 必备头文件

// 1. 引脚名单（如果蓝灯GPIO 2还是没反应，你可以把它改成其他接了线的引脚）
int ledPins[] = {2, 4, 5, 18, 19}; 

// 2. LED 的总数
int numLeds = 5; 

// 3. 闪烁速度（数字越小，灯跑得越快，200毫秒刚刚好）
int delayTime = 200; 

void setup() {
  Serial.begin(115200);
  Serial.println("--- 经典单点流水灯程序已启动！ ---");

  // 初始化所有引脚为输出模式
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); 
  }
}

void loop() {
  // 核心逻辑：单灯移动，不留尾巴
  for (int i = 0; i < numLeds; i++) {
    
    // 在串口监视器里打印当前亮灯的引脚，方便调试
    Serial.print("当前闪烁引脚: ");
    Serial.println(ledPins[i]);

    digitalWrite(ledPins[i], HIGH); // 1. 点亮当前的灯
    delay(delayTime);               // 2. 让它亮一小会儿
    digitalWrite(ledPins[i], LOW);  // 3. 核心：立刻熄灭它！保证不留尾巴
  }
}
