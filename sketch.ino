#include <Keypad.h>
#include <LowPower.h>

// Povezivanje pinova za LED diode, tipkalo, keypad i PIR senzor
const int led1Pin = 13;          // LED dioda 1
const int led2Pin = 12;         // LED dioda 2
const int tipkaloPin = 2;        // Tipkalo
const int pirSensorPin = 7;     // PIR senzor
const int buzzerPin = A0;

// Keypad konfiguracija
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {8, 9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int treptajLED = 0;           // Trajanje treptanja LED-a (u sekundama)
unsigned long pocetnitreptaj = 0; // Početno vrijeme za treptanje
unsigned long pocetnovrijemetreptaja = 0; //Pohrana vremena početka treptanja
const long interval = 500;        // Interval između treptanja (500ms)
bool treperi = false;          // Zastavica za treptanje LED-a

// Varijable za PIR senzor
volatile bool pirEnabled = false;         // Zastavica za omogućavanje PIR senzora
volatile bool simulationEnabled = false;  // Zastavica za simulaciju
bool simulateMotion = false;              // Zastavica za simulaciju pokreta
bool alarmActive = false;                 // Zastavica za aktivni alarm

// Varijable za debouncing
unsigned long lastDebounceTime = 0;    // Posljednje vrijeme kada je tipkalo aktivirano
const unsigned long debounceDelay = 200; // Kašnjenje za debouncing (200ms)

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(tipkaloPin, INPUT);  // Tipkalo bez pull-up otpornika
  pinMode(pirSensorPin, INPUT);      // PIR senzor
  pinMode(buzzerPin, OUTPUT);        // Buzzer za ton

  attachInterrupt(digitalPinToInterrupt(tipkaloPin), enableSimulation, FALLING); // Prekid za simulaciju

  Serial.begin(9600);
  Serial.println("Unesite broj sekundi (0-9) za svijetljenje LED diode putem Keypad-a:");
}

void loop() {
  // Očekuj unos trajanja treptanja
  char key = keypad.getKey();
  if (key) {
    Serial.print("Uneseno: ");
    Serial.println(key);

    if (key == '#') {
      // Prekida alarm
      if (alarmActive) {
        alarmActive = false;
        digitalWrite(led2Pin, LOW); // Ugasi LED2
        noTone(buzzerPin);          // Ugasi buzzer
        Serial.println("Alarm isključen.");
        pirEnabled = false;         // Onemogući PIR senzor nakon alarma
      }
    }

    if (key >= '0' && key <= '9') {
      treptajLED = key - '0'; // Postavi trajanje treptanja
      pocetnovrijemetreptaja = millis();
      treperi = true;
      Serial.print("Postavljeno vrijeme treptanja LED diode: ");
      Serial.print(treptajLED);
      Serial.println(" sekundi.");
    }
  }

  // Treptanje LED diode 1
  if (treperi) {
    unsigned long currentMillis = millis();
    if (currentMillis - pocetnovrijemetreptaja >= treptajLED * 1000) {
      treperi = false; // Zaustavi treptanje nakon isteka trajanja
      digitalWrite(led1Pin, LOW);

      // Ulazak u sleep mode na 4 sekunde
      Serial.println("Ulazak u Sleep mode na 4 sekunde...");
      LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
      Serial.println("Probudio se iz Sleep moda!");
    } else if (currentMillis - pocetnitreptaj >= interval) {
      pocetnitreptaj = currentMillis;
      digitalWrite(led1Pin, !digitalRead(led1Pin));
    }
  }

  // Provjera simulacije i PIR senzora
  if (simulationEnabled && pirEnabled) {
    int pirValue = digitalRead(pirSensorPin);
    if (pirValue == HIGH && !alarmActive) {
      alarmActive = true; // Aktiviraj alarm
      Serial.println("Pokret detektiran! Alarm aktiviran, isključi #.");
      activateAlarm();
    }
  }
}

// Funkcija za omogućavanje simulacije pokreta (prekid na tipkalo)
void enableSimulation() {
  unsigned long currentTime = millis();
  
  // Debouncing mehanizam
  if (currentTime - lastDebounceTime > debounceDelay) {
    lastDebounceTime = currentTime;

    if (simulationEnabled) {
      // Ako je simulacija već aktivna, deaktiviraj je
      simulationEnabled = false;
      pirEnabled = false;
      Serial.println("Simulacija deaktivirana.");
    } else {
      // Ako simulacija nije aktivna, aktiviraj je
      simulationEnabled = true;
      pirEnabled = true;
      Serial.println("Simulacija aktivna. Čeka se pokretanje.");
    }
  }
}

// Funkcija za aktivaciju alarma
void activateAlarm() {
  digitalWrite(led2Pin, HIGH);  // Uključi LED2
  tone(buzzerPin, 783, 30000); // Uključi buzzer s frekvencijom 783Hz
}
