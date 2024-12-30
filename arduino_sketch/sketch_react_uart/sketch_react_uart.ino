// Définir le pin de la LED intégrée (généralement pin 13)
const int ledPin = LED_BUILTIN;

// Variables pour suivre l'état de la LED
enum LedState { OFF, BLINK, ON };
LedState currentState = OFF;

// Variables de gestion du clignotement
unsigned long previousMillis = 0;
const long blinkInterval = 1000; // Intervalle de 1 seconde pour le clignotement

void setup() {
  // Initialiser la communication série
  Serial.begin(9600);

  // Configurer le pin de la LED comme une sortie
  pinMode(ledPin, OUTPUT);

  // Indicates readiness
  Serial.println("READY");
  Serial.flush();
}

void loop() {
  // Vérifier si des données sont disponibles sur le port série
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n'); // Lire le message jusqu'à un saut de ligne

    // Supprimer les espaces ou retours à la ligne en trop
    message.trim();

    // Réagir aux commandes reçues
    if (message == "SHINE") {
      currentState = BLINK;
      Serial.println("INSTRUCTION SHINE well received");
    } else if (message == "ON") {
      currentState = ON;
      Serial.println("INSTRUCTION ON well received");
    } else if (message == "OFF") {
      currentState = OFF;
      Serial.println("INSTRUCTION OFF well received");
    } else {
    Serial.println("Invalid command received");
    }
  }

  // Agir en fonction de l'état actuel de la LED
  switch (currentState) {
    case BLINK: {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, !digitalRead(ledPin)); // Basculer l'état de la LED
      }
      break;
    }

    case ON: {
      digitalWrite(ledPin, HIGH);
      break;
    }

    case OFF: {
      digitalWrite(ledPin, LOW);
      break;
    }
  }
}
