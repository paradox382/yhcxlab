#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// 🌟 初始化 U8g2 库（针对最常见的 SSD1306 128x64 OLED 屏幕，使用硬件 I2C）
// 如果你的屏幕是别种芯片，可能需要更换这个构造函数
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // 1. 初始化 U8g2 驱动
  u8g2.begin();
  
  // 2. 开启中文字符集支持（U8g2 支持中文，但需要选择带 _tf 后缀的字体）
  u8g2.enableUTF8Print(); 
}

void loop() {
  // 3. 清空屏幕缓冲区
  u8g2.clearBuffer();					
  
  // 4. 设置字体（ncenB14 是一个好看的英文字体）
  u8g2.setFont(u8g2_font_ncenB14_tr);	
  // 在坐标 (x=0, y=20) 处绘制英文
  u8g2.drawStr(0, 20, "Hello World!");	
  
  // 5. 设置一个中文字体（u8g2_font_wqy12_t_gb2312 是文泉驿 12号 中文字体）
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  // 在坐标 (x=0, y=45) 处绘制中文
  u8g2.setCursor(0, 45);
  u8g2.print("内训测试：成功！");

  // 在底部画一条分割线 (x1, y1, x2, y2)
  u8g2.drawLine(0, 55, 128, 55);
  
  // 6. 将缓冲区的内容一次性发送到屏幕上显示出来（这步至关重要，不写不亮）
  u8g2.sendBuffer();					
  
  // 屏幕不需要刷新太快，延迟 1 秒
  delay(1000);
}
