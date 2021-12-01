#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>

volatile uint8_t pinChangeInterruptFlag = 0;

// Sensors and buttons
#define MAGNET_1 10
#define MAGNET_2 11
#define MAGNET_3 12
#define MAGNET_4 13
#define MAGNET_5 14
#define MAGNET_6 15
#define MAGNET_7 53
#define BTN_ALL_ON 51
#define BTN_OPEN_DOOR 50

// Outputs
#define OIL_1 36
#define OIL_2 35
#define OIL_3 34
#define OIL_4 33
#define OIL_5 32
#define OIL_6 31
#define OIL_7 30
#define FLAME_1 37
#define FLAME_2 22
#define FLAME_3 23
#define FLAME_4 24
#define FLAME_5 25
#define FLAME_6 26
#define FLAME_7 27
#define DOOR 29

// Status
volatile int oil1 = 0;
volatile int oil2 = 0;
volatile int oil3 = 0;
volatile int oil4 = 0;
volatile int oil5 = 0;
volatile int oil6 = 0;
volatile int oil7 = 0;
int oilCount = 0;
volatile int flame1 = 0;
volatile int flame2 = 0;
volatile int flame3 = 0;
volatile int flame4 = 0;
volatile int flame5 = 0;
volatile int flame6 = 0;
volatile int flame7 = 0;
int flameCount = 0;

volatile int forceAllOn = 0;
volatile int openDoorManually = 0;
// Only allow the door to open once to prevent the lock from burning out
volatile int doorWasOpened = 0;

void interruptFunction () {
  pinChangeInterruptFlag = arduinoInterruptedPin;
  switch (arduinoInterruptedPin) {
    case MAGNET_1: if (oilCount == 7) flame1 = 1; else oil1 = 1; break;
    case MAGNET_2: if (oilCount == 7) flame2 = 1; else oil2 = 1; break;
    case MAGNET_3: if (oilCount == 7) flame3 = 1; else oil3 = 1; break;
    case MAGNET_4: if (oilCount == 7) flame4 = 1; else oil4 = 1; break;
    case MAGNET_5: if (oilCount == 7) flame5 = 1; else oil5 = 1; break;
    case MAGNET_6: if (oilCount == 7) flame6 = 1; else oil6 = 1; break;
    case MAGNET_7: if (oilCount == 7) flame7 = 1; else oil7 = 1; break;
    case BTN_ALL_ON: forceAllOn = 1; break;
    case BTN_OPEN_DOOR: openDoorManually = 1; doorWasOpened = 0; break;
  }
}

#define setupInterrupt(x) \
  EI_printPSTR("Add pin: "); \
  EI_printPSTR(#x); \
  EI_printPSTR("\r\n"); \
  pinMode( x, INPUT_PULLUP); \
  enableInterrupt( x, interruptFunction, CHANGE)

void printValues() {
  Serial.print("OIL:   ");
  Serial.print(oil1);
  Serial.print(oil2);
  Serial.print(oil3);
  Serial.print(oil4);
  Serial.print(oil5);
  Serial.print(oil6);
  Serial.print(oil7);
  Serial.println();
  Serial.print("FLAME: ");
  Serial.print(flame1);
  Serial.print(flame2);
  Serial.print(flame3);
  Serial.print(flame4);
  Serial.print(flame5);
  Serial.print(flame6);
  Serial.print(flame7);
  Serial.println();
}

void allOn() {
  oil1 = 1;
  oil2 = 1;
  oil3 = 1;
  oil4 = 1;
  oil5 = 1;
  oil6 = 1;
  oil7 = 1;
  flame1 = 1;
  flame2 = 1;
  flame3 = 1;
  flame4 = 1;
  flame5 = 1;
  flame6 = 1;
  flame7 = 1;
  oilCount = 7;
  flameCount = 7;

  digitalWrite(OIL_1, LOW);
  delay(500);
  digitalWrite(OIL_2, LOW);
  delay(500);
  digitalWrite(OIL_3, LOW);
  delay(500);
  digitalWrite(OIL_4, LOW);
  delay(500);
  digitalWrite(OIL_5, LOW);
  delay(500);
  digitalWrite(OIL_6, LOW);
  delay(500);
  digitalWrite(OIL_7, LOW);
  delay(500);
  digitalWrite(FLAME_1, LOW);
  delay(500);
  digitalWrite(FLAME_2, LOW);
  delay(500);
  digitalWrite(FLAME_3, LOW);
  delay(500);
  digitalWrite(FLAME_4, LOW);
  delay(500);
  digitalWrite(FLAME_5, LOW);
  delay(500);
  digitalWrite(FLAME_6, LOW);
  delay(500);
  digitalWrite(FLAME_7, LOW);
}

void resetOutputs() {
  oil1 = 0;
  oil2 = 0;
  oil3 = 0;
  oil4 = 0;
  oil5 = 0;
  oil6 = 0;
  oil7 = 0;
  flame1 = 0;
  flame2 = 0;
  flame3 = 0;
  flame4 = 0;
  flame5 = 0;
  flame6 = 0;
  flame7 = 0;
  oilCount = 0;
  flameCount = 0;

  openDoorManually = 0;
  doorWasOpened = 0;

  digitalWrite(OIL_1, HIGH);
  digitalWrite(OIL_2, HIGH);
  digitalWrite(OIL_3, HIGH);
  digitalWrite(OIL_4, HIGH);
  digitalWrite(OIL_5, HIGH);
  digitalWrite(OIL_6, HIGH);
  digitalWrite(OIL_7, HIGH);
  digitalWrite(FLAME_1, HIGH);
  digitalWrite(FLAME_2, HIGH);
  digitalWrite(FLAME_3, HIGH);
  digitalWrite(FLAME_4, HIGH);
  digitalWrite(FLAME_5, HIGH);
  digitalWrite(FLAME_6, HIGH);
  digitalWrite(FLAME_7, HIGH);
  digitalWrite(DOOR, HIGH);
}

void setup() {
  Serial.begin(9600);
  EI_printPSTR("--- START ------------------------------------\r\n");
  setupInterrupt(SS);
  setupInterrupt(SCK);
  setupInterrupt(MOSI);
  setupInterrupt(MISO);
  setupInterrupt(10);
  setupInterrupt(11);
  setupInterrupt(12);
  setupInterrupt(13);
  setupInterrupt(14);
  setupInterrupt(15);

  pinMode(OIL_1, OUTPUT);
  pinMode(OIL_2, OUTPUT);
  pinMode(OIL_3, OUTPUT);
  pinMode(OIL_4, OUTPUT);
  pinMode(OIL_5, OUTPUT);
  pinMode(OIL_6, OUTPUT);
  pinMode(OIL_7, OUTPUT);
  pinMode(FLAME_1, OUTPUT);
  pinMode(FLAME_2, OUTPUT);
  pinMode(FLAME_3, OUTPUT);
  pinMode(FLAME_4, OUTPUT);
  pinMode(FLAME_5, OUTPUT);
  pinMode(FLAME_6, OUTPUT);
  pinMode(FLAME_7, OUTPUT);
  pinMode(DOOR, OUTPUT);

  resetOutputs();
  printValues();
}

void openDoor() {
  if (doorWasOpened == 1) {
    return;
  }

  doorWasOpened = 1;
  digitalWrite(DOOR, LOW);
  delay(1000);
  digitalWrite(DOOR, HIGH);
}

uint8_t current_pin_state = 0;
// In the loop, we just check to see where the interrupt count is at. The value gets updated by
// the interrupt routine.
void loop() {
  if (pinChangeInterruptFlag) {
    //EI_printPSTR("Pin Change interrupt, pin "); Serial.println(arduinoInterruptedPin);
    EI_printPSTR("pci: "); Serial.print(pinChangeInterruptFlag);
    EI_printPSTR(", state: "); Serial.println(arduinoPinState);
    arduinoInterruptedPin = 0;
    pinChangeInterruptFlag = 0;
    printValues();

    if (openDoorManually == 1) {
      openDoorManually = 0;
      openDoor();
    }

    if (forceAllOn > 0) {
      forceAllOn = 0;
      allOn();
      return;
    }

    if (oil1 > 0) {
      digitalWrite(OIL_1, LOW);
    }
    if (oil2 > 0) {
      digitalWrite(OIL_2, LOW);
    }
    if (oil3 > 0) {
      digitalWrite(OIL_3, LOW);
    }
    if (oil4 > 0) {
      digitalWrite(OIL_4, LOW);
    }
    if (oil5 > 0) {
      digitalWrite(OIL_5, LOW);
    }
    if (oil6 > 0) {
      digitalWrite(OIL_6, LOW);
    }
    if (oil7 > 0) {
      digitalWrite(OIL_7, LOW);
    }
    if (flame1 > 0) {
      digitalWrite(FLAME_1, LOW);
    }
    if (flame2 > 0) {
      digitalWrite(FLAME_2, LOW);
    }
    if (flame3 > 0) {
      digitalWrite(FLAME_3, LOW);
    }
    if (flame4 > 0) {
      digitalWrite(FLAME_4, LOW);
    }
    if (flame5 > 0) {
      digitalWrite(FLAME_5, LOW);
    }
    if (flame6 > 0) {
      digitalWrite(FLAME_6, LOW);
    }
    if (flame7 > 0) {
      digitalWrite(FLAME_7, LOW);
    }
    oilCount = oil1 + oil2 + oil3 + oil4 + oil5 + oil6 + oil7;
    flameCount = flame1 + flame2 + flame3 + flame4 + flame5 + flame6 + flame7;

    if (oilCount == 7 && doorWasOpened == 0) {
      openDoor();
      delay(5000);
      // For some reason turning off the door is causing phantom inrush
    }
  }

  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'R':
      resetOutputs();
      printValues();
      break;
      case '1':
      pinChangeInterruptFlag = MAGNET_1;
      flame1 = 1;
      oil1 = 1;
      break;
      case '2':
      pinChangeInterruptFlag = MAGNET_2;
      flame2 = 1;
      oil2 = 1;
      break;
      case '3':
      pinChangeInterruptFlag = MAGNET_3;
      flame3 = 1;
      oil3 = 1;
      break;
      case '4':
      pinChangeInterruptFlag = MAGNET_4;
      flame4 = 1;
      oil4 = 1;
      break;
      case '5':
      pinChangeInterruptFlag = MAGNET_5;
      flame5 = 1;
      oil5 = 1;
      break;
      case '6':
      pinChangeInterruptFlag = MAGNET_6;
      flame6 = 1;
      oil6 = 1;
      break;
      case '7':
      pinChangeInterruptFlag = MAGNET_7;
      flame7 = 1;
      oil7 = 1;
      break;
    }
  }
}
