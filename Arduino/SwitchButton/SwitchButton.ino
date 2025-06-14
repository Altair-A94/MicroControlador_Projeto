#define SWITCH_PIN 2        // Pino do magnetic switch
#define BUZZER_PIN 8        // Pino do buzzer
#define BUTTON_PIN 4        // Pino do botão

bool alarmeAtivo = true;        // Começa com o alarme ligado
bool ultimoEstadoBotao = HIGH; // Inicializa com o botão não pressionado (pull-up)
unsigned long ultimaTroca = 0;
const unsigned long debounceDelay = 50;
bool botaoPressionado = false; // Flag para controlar a ação do botão

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);   // Switch magnético
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Botão com pull-up interno
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);                  // Buzzer começa desligado
}

void loop() {
  // Leitura do botão
  bool estadoBotaoAtual = digitalRead(BUTTON_PIN);

  // Verifica se houve mudança no estado do botão
  if (estadoBotaoAtual != ultimoEstadoBotao) {
    ultimaTroca = millis(); // Registra o tempo da mudança
  }

  // Verifica se o tempo de debounce passou
  if ((millis() - ultimaTroca) >= debounceDelay) {
    // Se o estado do botão mudou *e* o debounce passou, então...
    if (estadoBotaoAtual == LOW && ultimoEstadoBotao == HIGH) {
      // ...e se o botão ainda não foi considerado pressionado...
      if (!botaoPressionado) {
        // ...alterna o estado do alarme
        alarmeAtivo = !alarmeAtivo;
        botaoPressionado = true; // Marca o botão como pressionado
      }
    }

    // Se o botão foi liberado...
    if (estadoBotaoAtual == HIGH && ultimoEstadoBotao == LOW) {
      botaoPressionado = false; // Reseta a flag quando o botão é liberado
    }

    // Atualiza o último estado do botão *após* o debounce
    ultimoEstadoBotao = estadoBotaoAtual;
  }

  // Lógica do alarme
  if (alarmeAtivo) {
    int estadoSwitch = digitalRead(SWITCH_PIN);

    if (estadoSwitch == HIGH) {
      tone(BUZZER_PIN, 2000);  // Alarme sonoro
      delay(100);
      noTone(BUZZER_PIN);
      delay(100);
    } else {
      noTone(BUZZER_PIN);
    }
  } else {
    // Modo desligado: sempre desliga o buzzer
    noTone(BUZZER_PIN);
  }
}