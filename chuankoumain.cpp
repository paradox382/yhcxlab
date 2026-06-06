#include <Arduino.h>

// 1. 定义你连接的 5 个 ESP32 引脚
const int LED_PINS[] = {2, 4, 5, 18, 19}; 
const int NUM_LEDS = 5; // 灯的总数

// 2. 用一个数组记录每盏灯的状态（false=灭，true=亮）
bool ledStates[] = {false, false, false, false, false};

void setup() {
  // 初始化串口
  Serial.begin(9600);
  
  // 循环初始化所有引脚为输出模式，并默认关闭
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void loop() {
  // 检查串口是否有数据
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim(); // 切除尾部换行符
    
    // 检查输入的字符是不是 '1' 到 '5'
    // 提示：'1' 的 ASCII 码是 49，这里转成数组索引 0 到 4
    if (input.length() == 1 && input[0] >= '1' && input[0] <= '5') {
      int index = input[0] - '1'; // 计算出对应的数组下标 (0~4)
      
      // 状态翻转
      ledStates[index] = !ledStates[index];
      
      // 执行控制
      digitalWrite(LED_PINS[index], ledStates[index] ? HIGH : LOW);
      
      // 串口反馈
      Serial.print("LED (引脚 ");
      Serial.print(LED_PINS[index]);
      Serial.print(") 状态变为: ");
      Serial.println(ledStates[index] ? "亮" : "灭");
    }
    // 如果收到的是 '6' 或者其他不在 1~5 范围内的指令，单片机将直接忽略，不执行任何动作
  }
}
