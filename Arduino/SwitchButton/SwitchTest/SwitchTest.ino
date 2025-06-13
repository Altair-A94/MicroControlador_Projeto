#define SWITCH_PIN 2
#define BUZZER_PIN 8
#define BUTTON_PIN 4

bool alarmeAtivo = true;
bool ultimoEstadoBotao = HIGH;
unsigned long ultimaTroca = 0;
const unsigned long debounceDelay = 50;
bool botaoPressionado = false;

unsigned long waitStartTime = 0;
const unsigned long waitTimeout = 3000;
bool waitingForPermission = false;
bool permissionGranted = false;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);


  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Aviso: Botão não está conectado.");
  }
}

void loop() {

  bool estadoBotaoAtual = digitalRead(BUTTON_PIN);


  if (estadoBotaoAtual != ultimoEstadoBotao) {
    ultimaTroca = millis();
  }


  if ((millis() - ultimaTroca) >= debounceDelay) {

    if (estadoBotaoAtual == LOW && ultimoEstadoBotao == HIGH) {

      if (!botaoPressionado) {

        alarmeAtivo = !alarmeAtivo;
        Serial.println("Botão pressionado, estado do alarme alterado.");
        botaoPressionado = true; //
      }
    }

    //
    if (estadoBotaoAtual == HIGH && ultimoEstadoBotao == LOW) {
      botaoPressionado = false; //
    }

    //
    ultimoEstadoBotao = estadoBotaoAtual;
  }

  //
  if (alarmeAtivo) {
    int estadoSwitch = digitalRead(SWITCH_PIN);

    if (estadoSwitch == HIGH) {
      if (!waitingForPermission && !permissionGranted) {
        Serial.println("ATIVADO"); //
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
        tone(BUZZER_PIN, 4000);
        delay(100);
        noTone(BUZZER_PIN);
        delay(100);
      } else {
        noTone(BUZZER_PIN);
      }
    } else {
      noTone(BUZZER_PIN);
      permissionGranted = false;
      waitingForPermission = false;
    }
  } else {

    noTone(BUZZER_PIN);
    permissionGranted = false;
    waitingForPermission = false;
  }
}
