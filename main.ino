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
void getSequenciaBt(Musica m);
bool compararArrays(int arr1[], int arr2[], int tamanho);

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
      getSequenciaBt(musica1);
    }
    delay(800);
  }
}

void getSequenciaBt(Musica m){
  int seq[m.tamanho];
  int cont = 0;
  seq[0] = -1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Aperte na");
  lcd.setCursor(0,1);
  lcd.print("   Sequencia");

  delay(1000);
  lcd.clear();
  while (cont != m.tamanho){
    if (seq[0] != -1){
        String msg = "";
        for (int i = 0; i < cont; i++){
            msg = msg + String(seq[i]) + " ";
        }
        lcd.setCursor(0,0);
        lcd.print(msg);
    }
    
    if (digitalRead(bt1) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 1");
        seq[cont] = 1;
        cont++;
        delay(500);
    }else if (digitalRead(bt2) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 2");
        seq[cont] = 2;
        cont++;
        delay(500);
    }else if (digitalRead(bt3) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 3");
        seq[cont] = 3;
        cont++;
        delay(500);
    }else if (digitalRead(bt4) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 4");
        seq[cont] = 4;
        cont++;
        delay(500);
    }
  }

  String msg = "";
  for (int i = 0; i < cont; i++){
      msg = msg + String(seq[i]) + " ";
  }
  lcd.setCursor(0,0);
  lcd.print(msg);

  delay(2000);
  
  int notasSeq[m.tamanho];
  for (int i = 0; i < m.tamanho; i++) {
    notasSeq[i] = m.notasBt[seq[i] - 1];
  }

  lcd.clear();
  lcd.setCursor(0,0);
  if(!compararArrays(m.notas, notasSeq, m.tamanho)){  
    lcd.print("  Voce Errou a");
    lcd.setCursor(0,1);
    lcd.print("  a Sequencia!");
  }else{
    lcd.print("  Voce Acertou!");
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
    tone(buzzer, m.notasBt[i], 1000);
    delay(1500);
  }
  noTone(buzzer);
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

void msg_inicio(){
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print(" Precione Para ");
  lcd.setCursor(0,1);
  lcd.print(" Iniciar o Jogo");
}

bool compararArrays(int arr1[], int arr2[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }

  return true;
}