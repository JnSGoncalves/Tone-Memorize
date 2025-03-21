#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);

unsigned int buzzer = 6;

int bt1 = 5;
int bt2 = 4;
int bt3 = 3;
int bt4 = 2;

bool iniciado = false;

void setup(){
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  msg_inicio();
}

void loop(){
  if(!iniciado){
  	msg_inicio();
    delay(800);
  }
}

void msg_inicio(){
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print(" Precione Para ");
  lcd.setCursor(0,1);
  lcd.print(" Iniciar o Jogo");
}
