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

  if (estadoSwitch == LOW && !esperaConfirmacao) {
    Serial.println("ATIVADO");
    esperaConfirmacao = true;
  }

  if (Serial.available()) {
    String resposta = Serial.readStringUntil('\n');
    resposta.trim();
    if (resposta == "CONFIRMADO") {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1000);
      digitalWrite(BUZZER_PIN, LOW);
      esperaConfirmacao = false;
    }
  }

  delay(100); // Para evitar excesso de leitura
}

