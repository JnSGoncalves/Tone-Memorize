# Tone-Memorize
Projeto de computação móvel.

Este projeto visa desenvolver um jogo da memória musical utilizando Arduino, onde o jogador deve repetir corretamente sequências de notas musicais tocadas por um buzzer. O jogo busca testar a memória auditiva e a atenção do usuário, com aumento progressivo de dificuldade conforme o jogador acerta as sequências. O objetivo principal é aplicar conceitos de eletrônica e programação embarcada para criar uma experiência interativa e educativa.

Descrição dos Materiais Utilizados

Arduino UNO
7 botões (push-buttons)
2 LEDs (verde e vermelho)
1 Buzzer
Display LCD 16x2 com interface paralela
Resistores
Protoboard e jumpers
Fonte de alimentação USB ou bateria 9V

O projeto foi desenvolvido utilizando a IDE do Arduino. A estrutura do código foi pensada para organizar o jogo em fases, com níveis de dificuldade crescentes. O LCD exibe mensagens de orientação, o buzzer toca as notas, e os botões servem como interface de entrada para o jogador repetir a sequência.

// Define os pinos do LCD
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Pinos dos botões e buzzer
int bt1 = 6;
int bt2 = 5;
// ... até bt7
unsigned int buzzer = 7;

// Array com frequências musicais associadas aos botões
int notasBt[7] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_B4};

Fluxo do Jogo:
O jogador pressiona o botão para iniciar.
É exibido um menu com diferentes músicas.
A música escolhida toca parcialmente.
O jogador deve repetir a sequência correta nos botões.
Se acertar, avança para o próximo nível. Se errar, perde uma vida.
O jogo termina com vitória (ao completar todos os níveis) ou derrota (ao perder todas as vidas).

O desenvolvimento do jogo da memória musical proporcionou uma rica oportunidade de aplicar conhecimentos de eletrônica, lógica de programação e criatividade. O projeto não só cumpriu seu objetivo de criar um jogo interativo e educativo, mas também evidenciou a capacidade do Arduino em controlar múltiplos dispositivos de forma coordenada. A experiência foi enriquecedora, principalmente pela combinação de estímulos visuais (LEDs e LCD) e auditivos (buzzer), o que tornou o jogo envolvente e desafiador. Além disso, a modularidade do código e do hardware permite futuras expansões, como a adição de mais músicas, modos de jogo ou até comunicação com aplicativos externos.

Durante o desenvolvimento do projeto, algumas dificuldades técnicas e lógicas foram enfrentadas:
Limitações de pinos do Arduino: Com muitos botões, LEDs, LCD e o buzzer conectados, houve um planejamento cuidadoso da pinagem, além da necessidade de reutilizar pinos com lógica compartilhada e considerar expansores como shift registers em versões futuras.
Gerenciamento da lógica de fases: A estruturação do código para lidar com diferentes níveis, verificações de acertos e vidas restantes exigiu planejamento para manter o código legível e funcional.
Limite de memória do Arduino: Com múltiplas músicas, LCD e lógica de jogo, a memória do Arduino foi levada ao limite, exigindo otimização.