#define SWITCH_PIN 2       // Pino do magnetic switch
#define BUZZER_PIN 8       // Pino do buzzer

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);  // Switch com pull-up
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int estadoSwitch = digitalRead(SWITCH_PIN);

  if (estadoSwitch == HIGH) {
    // Toca buzzer a 2000 Hz por 200 ms
    tone(BUZZER_PIN, 2000);
    delay(100);
    noTone(BUZZER_PIN);

    // Aguarda até o switch ser solto para evitar repetição contínua
    while (digitalRead(SWITCH_PIN) == HIGH) {
      delay(10);
    }
  }

  delay(50);
}

