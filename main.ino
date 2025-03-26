#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);
unsigned int buzzer = 6;

int bt1 = 5;
int bt2 = 4;
int bt3 = 3; 
int bt4 = 2;

bool iniciado = false;

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523


struct Musica {
  String nome;
  int notas[10];
  int duracoes[10];
  int tamanho;
  int notasBt[4];
};


Musica musica1 = {
  "Do Re Mi",
  {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_D4},
  {400, 400, 400, 400, 400},
  5,
  {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4}
};


void tocarMusica(Musica m);
void playBtTone(Musica m);

void setup(){
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16, 2);
  msg_inicio();
}

void loop(){
  if(!iniciado){
    msg_inicio();
    if(digitalRead(bt3) == LOW) {
      iniciado = true;
      delay(1000);

      playBtTone(musica1);
      delay(2000);
      tocarMusica(musica1);
    }
    delay(800);
  }
}

void playBtTone(Musica m){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Memorize as  ");
  lcd.setCursor(0,1);
  lcd.print("notas dos botoes");
  delay(2000);

  String msg;
  for(int i = 0; i < 4; i++){
    msg = "     Botao " + String(i + 1);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
    tone(buzzer, m.notasBt[i], 2500);
    delay(3000);
  }
  noTone(buzzer);
}

void msg_inicio(){
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print(" Precione Para ");
  lcd.setCursor(0,1);
  lcd.print(" Iniciar o Jogo");
}


void tocarMusica(Musica m) {
  lcd.clear();
  lcd.print("Tocando Musica");
  lcd.setCursor(0,1);
  lcd.print(m.nome);
  delay(1000);
  for(int i = 0; i < m.tamanho; i++) {
    tone(buzzer, m.notas[i], m.duracoes[i]);
    delay(m.duracoes[i] + 100);
  }
  noTone(buzzer);
}
