#include <Arduino.h>

// 1. 定义连接 ULN2003 的 4 个引脚
const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 14;
const int IN4 = 27;

// 2. 步进延时（单位：毫秒）。决定了电机的转速！
// 注意：28BYJ-48 电机有物理极限，延时太小（比如小于 2ms）电机会因为反应不过来而只抖动不旋转。
int stepDelay = 3; 

// 3. 定义单四拍的步进矩阵 (4步一个循环)
const int stepSequence[4][4] = {
  {1, 0, 0, 0}, // 第一步
  {0, 1, 0, 0}, // 第二步
  {0, 0, 1, 0}, // 第三步
  {0, 0, 0, 1}  // 第四步
};

// 4. 核心函数：向 4 个引脚写入对应的电平状态
void writeStep(int stepIndex) {
  digitalWrite(IN1, stepSequence[stepIndex][0]);
  digitalWrite(IN2, stepSequence[stepIndex][1]);
  digitalWrite(IN3, stepSequence[stepIndex][2]);
  digitalWrite(IN4, stepSequence[stepIndex][3]);
}

void setup() {
  Serial.begin(9600);
  
  // 初始化所有驱动引脚为输出模式
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  Serial.println(">>> 开始正转一圈...");
  // 正转 2048 步
  for (int i = 0; i < 2048; i++) {
    int currentStep = i % 4; // 计算当前应该走 4 拍中的哪一拍 (0,1,2,3)
    writeStep(currentStep);
    delay(stepDelay); // 没走完一步，停顿一下
  }
  
  // 停止通电，防止电机发热
  writeStep(-1); // 传入非法值会让所有引脚输出低电平
  
  Serial.println("暂停 2 秒...");
  delay(2000); 
  
  Serial.println("<<< 开始反转一圈...");
  // 反转 2048 步
  for (int i = 0; i < 2048; i++) {
    int currentStep = 3 - (i % 4); // 倒序执行四拍 (3,2,1,0)
    writeStep(currentStep);
    delay(stepDelay);
  }
  
  writeStep(-1); // 停止通电
  
  Serial.println("暂停 2 秒...\n");
  delay(2000);
}
