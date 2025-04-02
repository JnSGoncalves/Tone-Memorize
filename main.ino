#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);
unsigned int buzzer = 7;

int bt1 = 6;
int bt2 = 5;
int bt3 = 4; 
int bt4 = 3;
int bt5 = 2;
int bt6 = 1;
int bt7 = 0;

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
  char nome[13];
  int notas[15];
  int duracoes[15];
  int tamanho;
};

int notasBt[7] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_B4};

Musica musicas[5] = {
  {"Trilha Alegre", {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4}, {400, 400, 400, 400, 400, 400, 400, 400}, 8},
  {"Subida", {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5}, {300, 300, 300, 300, 300, 300, 300, 300}, 8},
  {"Descida", {NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4}, {300, 300, 300, 300, 300, 300, 300, 300}, 8},
  {"Sinos", {NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_E4}, {400, 400, 400, 400, 400, 400, 400, 400}, 8},
  {"Eco", {NOTE_C4, NOTE_G4, NOTE_E4, NOTE_C5, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_C5}, {500, 300, 400, 500, 300, 400, 500, 300}, 8}
};


void tocarMusica(Musica m, bool comNome);
void getSequenciaBt(Musica m);
bool compararArrays(int arr1[], int arr2[], int tamanho);
int menu();

void setup(){
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  pinMode(bt5, INPUT_PULLUP);
  pinMode(bt6, INPUT_PULLUP);
  pinMode(bt7, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16, 2);
  msg_inicio();
}

void loop(){
  if(!iniciado){
    msg_inicio();
    if(digitalRead(bt1) == LOW) {
      iniciado = true;
      delay(1000);
      
      int atual = menu();

      delay(200);

      playBtTone();
      delay(2000);
      tocarMusica(musicas[atual], true);
      getSequenciaBt(musicas[atual]);
    }
    delay(800);
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Tente de novo");
    delay(1000);
    iniciado = false;
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
    }else if (digitalRead(bt5) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 5");
        seq[cont] = 5;
        cont++;
        delay(500);
    }else if (digitalRead(bt6) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 6");
        seq[cont] = 6;
        cont++;
        delay(500);
    }else if (digitalRead(bt7) == LOW){
        lcd.setCursor(0,1);
        lcd.print("   Botao 7");
        seq[cont] = 7;
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
    notasSeq[i] = notasBt[seq[i] - 1];
  }

  lcd.clear();
  lcd.setCursor(0,0);
  if(!compararArrays(m.notas, notasSeq, m.tamanho)){  
    lcd.print("  Voce Errou a");
    lcd.setCursor(0,1);
    lcd.print("  a Sequencia!");
  }else{
    lcd.print("  Voce Acertou!");
    mscAcerto();
    delay(500);
  }
}

void playBtTone(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Memorize as  ");
  lcd.setCursor(0,1);
  lcd.print("notas dos botoes");
  delay(2000);

  String msg;
  for(int i = 0; i < 7; i++){
    msg = "     Botao " + String(i + 1);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
    tone(buzzer, notasBt[i], 1000);
    delay(1500);
  }
  noTone(buzzer);
}

void tocarMusica(Musica m, bool comNome) {
  if(comNome){
    lcd.clear();
    lcd.print("Tocando Musica");
    lcd.setCursor(0,1);
    lcd.print(m.nome);
  }
  delay(1000);
  for(int i = 0; i < m.tamanho; i++) {
    tone(buzzer, m.notas[i], m.duracoes[i]);
    delay(m.duracoes[i] + 100);
  }
  noTone(buzzer);
}

void formatarString(char *destino, const char *origem) {
    snprintf(destino, 17, "%-16s", origem);
}

int menu(){
  int atual = 0;

  bool selecionado = false;

  lcd.clear();

  char msg1[17];
  char msg2[17];
  while (!selecionado){
    if (digitalRead(bt1) == LOW){
      if(atual > 0){
        atual -= 1;
        delay(250);
      }
    }

    if (digitalRead(bt2) == LOW){
      if(atual < 4){
        atual += 1;
        delay(250);
      }
    }
    
    if (digitalRead(bt7) == LOW){
      selecionado = true;
      delay(250);
    }

    sprintf(msg1, "-> %s", musicas[atual].nome);
    if(atual == 4){
      sprintf(msg2, "                ");
    }else{
      sprintf(msg2, "   %s", musicas[atual + 1].nome);
      formatarString(msg2, msg2);
    }
    formatarString(msg1, msg1);

    lcd.setCursor(0,0);
    lcd.print(msg1);
    lcd.setCursor(0,1);
    lcd.print(msg2);    
  }
  
  return atual;
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

void mscAcerto(){
  Musica levelComplete = {
    "Level",
    {523, 659, 784, 1047, 1319, 1568, 1760, 1397, 1568, 1319, 1047, 1175, 987, 1047},
    {200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 200, 200, 200, 400},
    14
  };

  tocarMusica(levelComplete, false);
  delay(500);
}