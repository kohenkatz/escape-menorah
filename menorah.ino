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
volatile int oilCount = 0;
volatile int flame1 = 0;
volatile int flame2 = 0;
volatile int flame3 = 0;
volatile int flame4 = 0;
volatile int flame5 = 0;
volatile int flame6 = 0;
volatile int flame7 = 0;
int flameCount = 0;

int oil1on = 0;
int oil2on = 0;
int oil3on = 0;
int oil4on = 0;
int oil5on = 0;
int oil6on = 0;
int oil7on = 0;
int flame1on = 0;
int flame2on = 0;
int flame3on = 0;
int flame4on = 0;
int flame5on = 0;
int flame6on = 0;
int flame7on = 0;

volatile int forceAllOn = 0;
volatile int openDoorManually = 0;
// Only allow the door to open once to prevent the lock from burning out
volatile int doorWasOpened = 0;

// To turn off the LEDs so they do not overheat (10 minutes in ms)
unsigned long autoResetTimeout = 10L * 60L * 1000L;
unsigned long timeSinceOilFilled = 0;

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
    case BTN_OPEN_DOOR: openDoorManually = 1; break;
  }
}

#define setupInterrupt(x) \
  EI_printPSTR("Add pin: "); \
  EI_printPSTR(#x); \
  EI_printPSTR("\r\n"); \
  pinMode( x, INPUT_PULLUP); \
  enableInterrupt( x, interruptFunction, CHANGE)

void(* resetFunc) (void) = 0; //declare reset function @ address 0

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
  oil1on = 1;
  oil2on = 1;
  oil3on = 1;
  oil4on = 1;
  oil5on = 1;
  oil6on = 1;
  oil7on = 1;
  flame1on = 1;
  flame2on = 1;
  flame3on = 1;
  flame4on = 1;
  flame5on = 1;
  flame6on = 1;
  flame7on = 1;
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
  oil1on = 0;
  oil2on = 0;
  oil3on = 0;
  oil4on = 0;
  oil5on = 0;
  oil6on = 0;
  oil7on = 0;
  flame1on = 0;
  flame2on = 0;
  flame3on = 0;
  flame4on = 0;
  flame5on = 0;
  flame6on = 0;
  flame7on = 0;
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

void openDoor(int force) {
  if (doorWasOpened == 1 && force == 0) {
    return;
  }

  if (force == 0) {
    doorWasOpened = 1;
  }

  Serial.println("open door - START");
  digitalWrite(DOOR, LOW);
  delay(1000);
  Serial.println("open door - END");
  digitalWrite(DOOR, HIGH);
  delay(100);
  // For some reason turning off the door is causing phantom inrush
  // on the inputs.
  // We do need to find a fix for this, but for now we just reset everything.
  flame1 = 0;
  flame2 = 0;
  flame3 = 0;
  flame4 = 0;
  flame5 = 0;
  flame6 = 0;
  flame7 = 0;
  forceAllOn = 0;
  openDoorManually = 0;
}

void syncLightsWithVars() {
  if (oil1 == 1 && oil1on == 0) {
    oil1on = 1;
    digitalWrite(OIL_1, LOW);
    timeSinceOilFilled = millis();
  }
  if (oil2 == 1 && oil2on == 0) {
    oil2on = 1;
    digitalWrite(OIL_2, LOW);
    timeSinceOilFilled = millis();
  }
  if (oil3 == 1 && oil3on == 0) {
    oil3on = 1;
    digitalWrite(OIL_3, LOW);
    timeSinceOilFilled = millis();
  }
  if (oil4 == 1 && oil4on == 0) {
    oil4on = 1;
    digitalWrite(OIL_4, LOW);
    timeSinceOilFilled = millis();
  }
  if (oil5 == 1 && oil5on == 0) {
    oil5on = 1;
    digitalWrite(OIL_5, LOW);
    timeSinceOilFilled = millis();
  }
  if (oil6 == 1 && oil6on == 0) {
    oil6on = 1;
    digitalWrite(OIL_6, LOW);
    timeSinceOilFilled = millis();
  }
  if (oil7 == 1 && oil7on == 0) {
    oil7on = 1;
    digitalWrite(OIL_7, LOW);
    timeSinceOilFilled = millis();
  }

  if (flame1 == 1 && flame1on == 0) {
    flame1on = 1;
    digitalWrite(FLAME_1, LOW);
    timeSinceOilFilled = millis();
  }
  if (flame2 == 1 && flame2on == 0) {
    flame2on = 1;
    digitalWrite(FLAME_2, LOW);
    timeSinceOilFilled = millis();
  }
  if (flame3 == 1 && flame3on == 0) {
    flame3on = 1;
    digitalWrite(FLAME_3, LOW);
    timeSinceOilFilled = millis();
  }
  if (flame4 == 1 && flame4on == 0) {
    flame4on = 1;
    digitalWrite(FLAME_4, LOW);
    timeSinceOilFilled = millis();
  }
  if (flame5 == 1 && flame5on == 0) {
    flame5on = 1;
    digitalWrite(FLAME_5, LOW);
    timeSinceOilFilled = millis();
  }
  if (flame6 == 1 && flame6on == 0) {
    flame6on = 1;
    digitalWrite(FLAME_6, LOW);
    timeSinceOilFilled = millis();
  }
  if (flame7 == 1 && flame7on == 0) {
    flame7on = 1;
    digitalWrite(FLAME_7, LOW);
    timeSinceOilFilled = millis();
  }

  oilCount = oil1on + oil2on + oil3on + oil4on + oil5on + oil6on + oil7on;
  flameCount = flame1on + flame2on + flame3on + flame4on + flame5on + flame6on + flame7on;
}

void loop() {
  if (pinChangeInterruptFlag) {
    EI_printPSTR("pci: "); Serial.print(pinChangeInterruptFlag);
    EI_printPSTR(", state: "); Serial.println(arduinoPinState);
    arduinoInterruptedPin = 0;
    pinChangeInterruptFlag = 0;
    printValues();

    if (forceAllOn == 1) {
      forceAllOn = 0;
      allOn();
      return;
    }

    if (openDoorManually == 1) {
      openDoorManually = 0;
      openDoor(1);
      return;
    }

    if (oilCount == 7 && doorWasOpened == 0) {
      delay(500);
      openDoor(0);
      delay(1000);
      // Reset flames for if they held the oil
      // there for too long
      flame1 = 0;
      flame2 = 0;
      flame3 = 0;
      flame4 = 0;
      flame5 = 0;
      flame6 = 0;
      flame7 = 0;
    }

    syncLightsWithVars();
  }

  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'r':
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
      case 'a':
      case 'A':
      allOn();
      break;
    }
  }

  if (timeSinceOilFilled > 0 && millis() > timeSinceOilFilled + autoResetTimeout) {
    resetFunc();
  }
}
