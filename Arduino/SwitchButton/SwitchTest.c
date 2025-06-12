#define SWITCH_PIN 2        // Pino do magnetic switch
#define BUZZER_PIN 8        // Pino do buzzer
#define BUTTON_PIN 4        // Pino do botão

bool alarmeAtivo = true;        // Começa com o alarme ligado
bool ultimoEstadoBotao = HIGH; // Inicializa com o botão não pressionado (pull-up)
unsigned long ultimaTroca = 0;
const unsigned long debounceDelay = 50;
bool botaoPressionado = false; // Flag para controlar a ação do botão

unsigned long waitStartTime = 0;
const unsigned long waitTimeout = 3000; // 3 seconds timeout for permission
bool waitingForPermission = false;
bool permissionGranted = false;

void setup() {
  Serial.begin(9600);                  // Inicializa comunicação serial
  pinMode(SWITCH_PIN, INPUT_PULLUP);   // Switch magnético
  pinMode(BUTTON_PIN, INPUT_PULLUP);   // Botão com pull-up interno
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);                  // Buzzer começa desligado

  // Verifica se o botão está conectado (estado sempre HIGH indica desconectado)
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Aviso: Botão não está conectado.");
  }
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
        Serial.println("Botão pressionado, estado do alarme alterado."); // Envia mensagem para o monitor serial
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
      if (!waitingForPermission && !permissionGranted) {
        Serial.println("ATIVADO"); // Solicita permissão para Python
        waitingForPermission = true;
        waitStartTime = millis();
      }

      if (waitingForPermission) {
        if (Serial.available() > 0) {
          String response = Serial.readStringUntil('\n');
          response.trim();
          if (response == "CONFIRMADO") {
            permissionGranted = true;
            waitingForPermission = false;
          }
        } else if (millis() - waitStartTime > waitTimeout) {
          // Timeout, cancela permissão
          waitingForPermission = false;
        }
      }

      if (permissionGranted) {
        tone(BUZZER_PIN, 2000);  // Alarme sonoro
        delay(100);
        noTone(BUZZER_PIN);
        delay(100);
      } else {
        noTone(BUZZER_PIN);
      }
    } else {
      noTone(BUZZER_PIN);
      permissionGranted = false; // Reset permission when switch is off
      waitingForPermission = false;
    }
  } else {
    // Modo desligado: sempre desliga o buzzer
    noTone(BUZZER_PIN);
    permissionGranted = false;
    waitingForPermission = false;
  }
}
