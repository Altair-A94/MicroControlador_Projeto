#define SWITCH_PIN 2        // Pino do magnetic switch
#define BUZZER_PIN 8        // Pino do buzzer
#define BUTTON_PIN 4       // Botão agora está no pino 10

bool alarmeAtivo = true;        // Começa com o alarme ligado
bool ultimoEstadoBotao = HIGH;  // Estado anterior do botão
unsigned long ultimaTroca = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);   // Switch magnético com pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Botão com pull-up interno
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);       // Garante que o buzzer começa desligado
}

void loop() {
  // Leitura do botão com debounce
  bool estadoBotao = digitalRead(BUTTON_PIN);

  if (estadoBotao != ultimoEstadoBotao) {
    ultimaTroca = millis();  // Inicia debounce
  }

  if ((millis() - ultimaTroca) > debounceDelay) {
    if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
      // Botão foi pressionado => alterna estado do alarme
      alarmeAtivo = !alarmeAtivo;
    }
  }

  ultimoEstadoBotao = estadoBotao;

  // Lógica do alarme
  if (alarmeAtivo) {
    int estadoSwitch = digitalRead(SWITCH_PIN);

    if (estadoSwitch == HIGH) {
      // Switch aberto => buzzer apita em pulsos
      tone(BUZZER_PIN, 2000);
      delay(100);
      noTone(BUZZER_PIN);
      delay(100);
    } else {
      // Switch fechado => buzzer desligado
      noTone(BUZZER_PIN);
    }
  } else {
    // Alarme desligado => buzzer sempre desligado
    noTone(BUZZER_PIN);
  }
}
