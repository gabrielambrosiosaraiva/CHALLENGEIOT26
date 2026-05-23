#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 8
#define LED_VERDE 7
#define LED_VERMELHO 6

MFRC522 rfid(SS_PIN, RST_PIN);


byte autorizadaDrGabriel[4] = {0xD3, 0x67, 0xAA, 0x13};
byte negadaDraBarbara[4]    = {0x53, 0x4A, 0xD2, 0x26};

void setup() {
  Serial.begin(9600);
  SPI.begin();

  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("Aproxime a tag RFID...");
}

void loop() {
  
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID: ");

  bool ehGabriel = true;
  bool ehBarbara = true;

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");

    if (rfid.uid.uidByte[i] != autorizadaDrGabriel[i]) {
      ehGabriel = false;
    }
    if (rfid.uid.uidByte[i] != negadaDraBarbara[i]) {
      ehBarbara = false;
    }
  }
  Serial.println();

  if (ehGabriel) {
    Serial.println(">>> ACESSO LIBERADO <<<");
    
    digitalWrite(LED_VERDE, HIGH);
    tone(BUZZER_PIN, 2000, 150); 
    delay(500);
    digitalWrite(LED_VERDE, LOW);
  } 
  else if (ehBarbara) {
    Serial.println(">>> ACESSO NEGADO <<<");
    
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_VERMELHO, HIGH);
      tone(BUZZER_PIN, 350, 150); 
      delay(150);
      digitalWrite(LED_VERMELHO, LOW);
      delay(100);
    }
  } 
  else {
    Serial.println(">>> ACESSO NEGADO <<<");
    
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_VERMELHO, HIGH);
      tone(BUZZER_PIN, 350, 150); 
      delay(150);
      digitalWrite(LED_VERMELHO, LOW);
      delay(100);
    }
  }

  Serial.println();
  delay(500);
}