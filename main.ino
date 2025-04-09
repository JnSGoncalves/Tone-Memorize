#include <LiquidCrystal.h>

struct Musica {
  char nome[15];
  int notas[15];
  int duracoes[15];
  int tamanho;
};

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
unsigned int buzzer = 7;

int bt1 = 6;
int bt2 = 5;
int bt3 = 4;
int bt4 = 3;
int bt5 = 2;
int bt6 = 1;
int bt7 = 0;

int ledVerm = 14;
int ledVerd = 15;


bool iniciado = false;

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

int notasBt[7] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_B4};

Musica musicas[5] = {
  {"Trilha Alegre", {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4}, {400, 400, 400, 400, 400, 400, 400, 400}, 8},
  {"Subida", {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C4}, {300, 300, 300, 300, 300, 300, 300, 300}, 8},
  {"Descida", {NOTE_C4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4}, {300, 300, 300, 300, 300, 300, 300, 300}, 8},
  {"Sinos", {NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_E4}, {400, 400, 400, 400, 400, 400, 400, 400}, 8},
  {"Eco", {NOTE_C4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_C4}, {500, 300, 400, 500, 300, 400, 500, 300}, 8}
};

void tocarMusica(Musica m, bool comNome, int qtdNotas);
bool getSequenciaBt(Musica m, int numNotas);
bool compararArrays(int arr1[], int arr2[], int tamanho);
void iniciarMusica(Musica m);
int menu();
void playBtTone();
void msg_inicio();
void mscAcerto();
void mscGameOver();

void setup() {
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  pinMode(bt5, INPUT_PULLUP);
  pinMode(bt6, INPUT_PULLUP);
  pinMode(bt7, INPUT_PULLUP);
  
  pinMode(ledVerm, OUTPUT);
  pinMode(ledVerd, OUTPUT);

  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  msg_inicio();
}

void loop() {
  if (!iniciado) {
    msg_inicio();
    if (digitalRead(bt1) == LOW) {
      iniciado = true;
      delay(1000);

      int atual = menu();
      delay(200);
      playBtTone();
      delay(2000);

      iniciarMusica(musicas[atual]);
    }
    delay(800);
  } else {
    lcd.clear();
    iniciado = false;
  }
}

void iniciarMusica(Musica m) {
  bool correto = true;
  int dificuldade = 2;
  int vida = 5;

  digitalWrite(ledVerm, HIGH);
  digitalWrite(ledVerd, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Acerte as   ");
  lcd.setCursor(0,1);
  lcd.print("   Sequencias   ");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Para Ganhar!  ");
  delay(1500);
  lcd.clear();

  char msg1[17];
  char msg2[17];
  while (vida != 0 && dificuldade <= 8) {
    digitalWrite(ledVerm, HIGH);
    digitalWrite(ledVerd, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    sprintf(msg1, "    Nivel: %d    ", (dificuldade / 2));
    lcd.print(msg1);

    delay(1500);
    lcd.setCursor(0, 0);
    lcd.print("  Voce Possui   ");
    lcd.setCursor(0,1);
    sprintf(msg2, "   %d Vidas     ", vida);
    lcd.print(msg2);
    delay(1500);

    tocarMusica(m, true, dificuldade);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Aperte na");
    lcd.setCursor(0, 1);
    lcd.print("   Sequencia");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 1);
    sprintf(msg2, "Vidas: %d", vida);
    lcd.print(msg2);

    digitalWrite(ledVerm, LOW);
    digitalWrite(ledVerd, HIGH);

    correto = getSequenciaBt(m, dificuldade);

    digitalWrite(ledVerd, LOW);

    delay(500);

    lcd.clear();
    lcd.setCursor(0, 0);
    if (correto) {
      lcd.print("  Voce Acertou!");

      digitalWrite(ledVerd, HIGH);
      delay(400);
      digitalWrite(ledVerd, LOW);
      delay(400);
      digitalWrite(ledVerd, HIGH);
      delay(400);
      digitalWrite(ledVerd, LOW);
      delay(400);
      digitalWrite(ledVerd, HIGH);
      
      mscAcerto();

      dificuldade += 2;
    } else {
      lcd.print("  Voce Errou a");
      lcd.setCursor(0, 1);
      lcd.print("  a Sequencia!");
      perdaVida();

      digitalWrite(ledVerm, HIGH);
      delay(400);
      digitalWrite(ledVerm, LOW);
      delay(400);
      digitalWrite(ledVerm, HIGH);
      delay(400);
      digitalWrite(ledVerm, LOW);
      delay(400);
      digitalWrite(ledVerm, HIGH);

      lcd.clear();
      lcd.print(" Tente De Novo! ");
      delay(1500);
      vida -= 1;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  if (vida != 0) {
    lcd.print("  Voce Ganhou!");
    mscGanho();
  } else {
    lcd.print("  Voce Perdeu!");
    mscGameOver();
  }
  delay(500);
}

bool getSequenciaBt(Musica m, int numNotas) {
  if (numNotas > m.tamanho) numNotas = m.tamanho;

  int seq[numNotas];
  int cont = 0;
  seq[0] = -1;

  while (cont != numNotas) {
    if (seq[0] != -1) {
      String msg = "";
      for (int i = 0; i < cont; i++) {
        msg += String(seq[i]) + " ";
      }
      lcd.setCursor(0, 0);
      lcd.print(msg);
    }

    if (digitalRead(bt1) == LOW) {
      seq[cont] = 1;
      cont++;
      delay(500);
    } else if (digitalRead(bt2) == LOW) {
      seq[cont] = 2;
      cont++;
      delay(500);
    } else if (digitalRead(bt3) == LOW) {
      seq[cont] = 3;
      cont++;
      delay(500);
    } else if (digitalRead(bt4) == LOW) {
      seq[cont] = 4;
      cont++;
      delay(500);
    } else if (digitalRead(bt5) == LOW) {
      seq[cont] = 5;
      cont++;
      delay(500);
    } else if (digitalRead(bt6) == LOW) {
      seq[cont] = 6;
      cont++;
      delay(500);
    } else if (digitalRead(bt7) == LOW) {
      seq[cont] = 7;
      cont++;
      delay(500);
    }
  }

  String msg = "";
  for (int i = 0; i < cont; i++) {
    msg += String(seq[i]) + " ";
  }
  lcd.setCursor(0, 0);
  lcd.print(msg);
  delay(2000);

  int notasSeq[numNotas];
  for (int i = 0; i < numNotas; i++) {
    notasSeq[i] = notasBt[seq[i] - 1];
  }

  return compararArrays(m.notas, notasSeq, numNotas);
}

void playBtTone() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Memorize as  ");
  lcd.setCursor(0,1);
  lcd.print("notas dos botoes");
  delay(2000);

  String msg;
  for(int i = 0; i < 7; i++) {
    msg = "     Botao " + String(i + 1);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
    tone(buzzer, notasBt[i], 1000);
    delay(1500);
  }
  noTone(buzzer);
}

void tocarMusica(Musica m, bool comNome, int qtdNotas) {
  if (qtdNotas > m.tamanho) qtdNotas = m.tamanho;

  if(comNome) {
    lcd.clear();
    lcd.print("Tocando Musica");
    lcd.setCursor(0,1);
    lcd.print(m.nome);
  }
  delay(1000);
  for(int i = 0; i < qtdNotas; i++) {
    tone(buzzer, m.notas[i], m.duracoes[i]);
    delay(m.duracoes[i] + 100);
  }
  noTone(buzzer);
}

int menu() {
  int atual = 0;
  bool selecionado = false;

  lcd.clear();
  char msg1[17];
  char msg2[17];

  while (!selecionado) {
    if (digitalRead(bt1) == LOW) {
      if(atual > 0) atual--;
      delay(250);
    }

    if (digitalRead(bt2) == LOW) {
      if(atual < 4) atual++;
      delay(250);
    }

    if (digitalRead(bt7) == LOW) {
      selecionado = true;
      delay(250);
    }

    snprintf(msg1, 17, "-> %-13s", musicas[atual].nome);
    if(atual == 4) {
      snprintf(msg2, 17, "%-16s", " ");
    } else {
      snprintf(msg2, 17, "   %-13s", musicas[atual + 1].nome);
    }

    lcd.setCursor(0,0);
    lcd.print(msg1);
    lcd.setCursor(0,1);
    lcd.print(msg2);
  }
  return atual;
}

void msg_inicio() {
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print(" Precione Para ");
  lcd.setCursor(0,1);
  lcd.print(" Iniciar o Jogo");
}

bool compararArrays(int arr1[], int arr2[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (arr1[i] != arr2[i]) return false;
  }
  return true;
}

void mscGanho() {
  Musica levelComplete = {
    "Level",
    {523, 659, 784, 1047, 1319, 1568, 1760, 1397, 1568, 1319, 1047, 1175, 987, 1047},
    {200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 200, 200, 200, 400},
      14
  };
  tocarMusica(levelComplete, false, 14);
}

void mscGameOver() {
  int notas[] = {659, 659, 659, 523, 659, 784, 392, 523};

  int duracoes[] = {180, 180, 180, 360, 180, 720, 180, 720};

  const float factor = 1.3; 

  for (int i = 0; i < 8; i++) {
    tone(buzzer, notas[i], duracoes[i]);
    delay(duracoes[i] * factor); 
    noTone(buzzer);

    if(i == 2 || i == 5) delay(100 * factor); 
  }
}

void mscAcerto() {
  int notas[] = {440, 554, 659, 880};
  int duracoes[] = {60, 60, 60, 120}; 

  const float decay = 0.8;
  const float n64Factor = 1.18;

  for (int i = 0; i < 4; i++) {
    int duracaoReal = duracoes[i] * n64Factor;
    tone(buzzer, notas[i], duracaoReal * decay);
    delay(duracaoReal);
    noTone(buzzer);

    if(i < 3) tone(buzzer, notas[i]+15, 20);
  }
}

void perdaVida() {
  int notas[] = {659, 659, 523};

  int duracoes[] = {150, 150, 300};

  float delayFator = 1.2;
  int pausaFinal = 200;

  for (int i = 0; i < 3; i++) {
    tone(buzzer, notas[i], duracoes[i]);
    delay(duracoes[i] * delayFator);
    noTone(buzzer);
  }
  delay(pausaFinal);
}