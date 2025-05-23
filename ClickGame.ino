// RGB светодиод
#define R_PIN 5
#define G_PIN 13
#define B_PIN 4
// Кнопки
#define R_B 9
#define B_B 7
#define BUZ_PIN 12
// Финальное кол-во очков
#define F_COUNT 30

// Инициализируем библиотеки
#include <GRGB.h>
#include <EncButton.h>

// Инициализируем
int b = 0;
int r = 0;

GRGB led(COMMON_CATHODE, R_PIN, G_PIN, B_PIN);

Button btnB(B_B);
Button btnR(R_B);

void setup() {
  // Запускаем монитор порта
  Serial.begin(9600);
}

void loop() {
  // "Тикаем" кнопки
  btnB.tick();
  btnR.tick();

  // Проверяем "клик" синей кнопки
  if (btnB.click()){
    b++;
    Serial.print("Blue - ");
    Serial.println(b);
  }
  // Проверяем "клик" красной кнопки
  if (btnR.click()){
    r++;
    Serial.print("Red - ");
    Serial.println(r);
  }
  // Проверяем не закончилась ли игра
  if (r + b >= F_COUNT){
    // Определяем победителя
    if (b > r){
      // Включаем индикацию победителя
      led.setRGB(0, 0, 255);
      tone(BUZ_PIN, 1000, 2500);
      delay(2500);
      b = 0;
      r = 0;
      led.setRGB(0, 0, 0);
    } else if (b < r) {
      led.setRGB(255, 0, 0);
      tone(BUZ_PIN, 1000, 2500);
      delay(2500);
      b = 0;
      r = 0;
      led.setRGB(0, 0, 0);
    } else {
      led.setRGB(255, 0, 255);
      tone(BUZ_PIN, 500, 2500);
      delay(2500);
      b = 0;
      r = 0;
      led.setRGB(0, 0, 0);
    }
    // Начинаем игру заново
    delay(2000);
    tone(BUZ_PIN, 2500, 500);
  }
}