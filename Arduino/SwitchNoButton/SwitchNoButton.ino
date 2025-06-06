#define SWITCH_PIN 2       // Pino do magnetic switch
#define BUZZER_PIN 8       // Pino do buzzer

bool esperaConfirmacao = false;

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);  // Switch com pull-up
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.begin(9600);
}

void loop() {
  int estadoSwitch = digitalRead(SWITCH_PIN);

  if (estadoSwitch == HIGH && !esperaConfirmacao) {
    Serial.println("ATIVADO");
    esperaConfirmacao = true;
  }

  if (esperaConfirmacao && Serial.available()) {
    String resposta = Serial.readStringUntil('\n');
    resposta.trim();
    if (resposta == "CONFIRMADO") {
      tone(BUZZER_PIN, 2000);
      delay(200);
      noTone(BUZZER_PIN);
      esperaConfirmacao = false;

      // Aguarda até o switch ser solto para evitar repetição contínua
      while (digitalRead(SWITCH_PIN) == HIGH) {
        delay(10);
      }
    }
  }

  delay(50);
}

