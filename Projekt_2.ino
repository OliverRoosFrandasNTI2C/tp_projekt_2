const int button1 = 2; // första knappen är på pin 2
const int button2 = 3; // andra knappen är på pin 3
const int button3 = 4; // tredje knappen är på pin 4
const int button4 = 5; // fjärde knappen är på pin 5
const int button5 = 6; // femte knappen är på pin 6
const int button6 = 7; // sjätte knappen är på pin 7
const int LED[] = {14, 15, 16, 17, 18, 19}; // LED-pinnar för varje knapp

const int Red = 8;      // röd LED på pin 8
const int greenLed = 9; // grön LED på pin 9

void checkEntered1(int button);

int code[] = {6, 5, 5, 4, 3, 2}; // önskad kod som ska matas in

int entered[7]; // array för användarens inmatade kod

void setup() {
  Serial.begin(9600); // starta Serial kommunikation

  // Konfigurera knappar som input med standard värde HIGH
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);

  pinMode(Red, OUTPUT);      // röd LED som output
  pinMode(greenLed, OUTPUT); // grön LED som output

  digitalWrite(Red, LOW); // slå på den röda LED-lampan
  for (int i = 0; i < 6; i++) {
    Serial.println(code[i]);       // skriv varje siffra i koden
    Serial.println(entered[i]);    // skriv varje element i entered[] (för felsökning)
    pinMode(LED[i], OUTPUT);        // konfigurera LED-pinnar som output
  }
}

void loop() {
  // Kolla vilken knapp som är tryckt och anropa checkEntered1 med motsvarande index
  if (digitalRead(button1) == LOW) {
    checkEntered1(1);
    delay(250);
  } else if (digitalRead(button2) == LOW) {
    checkEntered1(2);
    delay(250);
  } else if (digitalRead(button3) == LOW) {
    checkEntered1(3);
    delay(250);
  } else if (digitalRead(button4) == LOW) {
    checkEntered1(4);
    delay(250);
  } else if (digitalRead(button5) == LOW) {
    checkEntered1(5);
    delay(250);
  } else if (digitalRead(button6) == LOW) {
    checkEntered1(6);
    delay(250);
  }
}

// Funktion för att kontrollera första elementet i entered[] arrayen
void checkEntered1(int button) {
  digitalWrite(LED[button - 1], HIGH);
  if (entered[0] != 0) {
    // Om det inte är noll har det redan matats in, gå vidare till nästa steg
    checkEntered2(button);
  } else if (entered[0] == 0) {
    // Om det är noll, sätt första elementet som den tryckta knappen
    entered[0] = button;
    Serial.print("1: ");
    Serial.println(entered[0]);
  }
}

// Lika för de följande checkEnteredX-funktionerna
// Varje funktion kollar nästa element i arrayen och går vidare om det inte är noll
// Annars sätts det aktuella elementet till den tryckta knappen och skriver ut för felsökning

// Funktion för att jämföra den inmatade koden med den önskade koden
void compareCode() {
  for (int i = 0; i < 6; i++) {
    Serial.println(entered[i]);
  }
  if ((entered[0] == code[0]) && (entered[1] == code[1]) && (entered[2] == code[2]) &&
      (entered[3] == code[3]) && (entered[4] == code[4]) && (entered[5] == code[5])) {
    // Om alla element i varje array är lika, slå av den röda LED:en och slå på den gröna LED:en
    digitalWrite(Red, LOW);
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(greenLed, LOW);

    // Återställ entered[] arrayen och återgå till loop() (inte nödvändigt)
    for (int i = 0; i < 7; i++) {
      entered[i] = 0;
    }
    loop();
  } else {
    // Om koden är fel, blinka den röda LED:en och återställ entered[] arrayen
    digitalWrite(Red, HIGH);
    delay(1000);
    digitalWrite(Red, LOW);
    Serial.println("Red OFF");
    for (int i = 0; i < 7; i++) {
      entered[i] = 0;
    }
  }
  // Stäng av alla LED-lampor
  close_all();
}

// Funktion för att stänga av alla LED-lampor
void close_all() {
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], LOW);
  digitalWrite(LED[4], LOW);
  digitalWrite(LED[5], LOW);
}
