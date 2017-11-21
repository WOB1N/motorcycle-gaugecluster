#include <Wire.h>

#define TURN_LEFT_PIN 0
#define TURN_RIGHT_PIN 1
#define HIGH_BEAM_PIN 2
#define NEUTRAL_PIN 3
#define OIL_WARNING_PIN 4

#define WATER_TEMP_PIN 17
#define FUEL_WARNING_2_PIN  16
#define FUEL_WARNING_1_PIN 15
#define BATTERY_VOLTAGE_PIN 14

volatile uint16_t speedoTicks = 0;
volatile uint16_t tachoTicks = 0;

bool turningLeft = false;
bool turningRight = false;
bool highBeam = false;
bool neutral = false;
bool oilWarning = false;
bool waterTempWarning = false;
bool fuelWarning1 = false;
bool fuelWarning2 = false;

void setup() {
  initializeIndicatorInputs();

  pinMode(A0, OUTPUT);

  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  readIndicatorInputs();

  // read speedo and tacho
  Wire.requestFrom(3, 4);    // request x bytes from slave device #3
  while (Wire.available()) { // slave may send less than requested
    int a = Wire.read();
    int b = Wire.read();
    int c = Wire.read();
    int d = Wire.read();

    speedoTicks = (a << 8) | b;
    tachoTicks = (c << 8) | d;

    Serial.print(speedoTicks);
    Serial.print("\t");
    Serial.println(tachoTicks);
  }

  delay(100);
}

void initializeIndicatorInputs(){
  pinMode(TURN_LEFT_PIN, INPUT);
  pinMode(TURN_RIGHT_PIN, INPUT);
  pinMode(HIGH_BEAM_PIN, INPUT);
  pinMode(NEUTRAL_PIN, INPUT);
  pinMode(OIL_WARNING_PIN, INPUT);
  pinMode(WATER_TEMP_PIN, INPUT);
  pinMode(FUEL_WARNING_1_PIN, INPUT);
  pinMode(FUEL_WARNING_2_PIN, INPUT);
}

void readIndicatorInputs(){
  turningLeft = digitalRead(TURN_LEFT_PIN);
  turningRight = digitalRead(TURN_RIGHT_PIN);
  highBeam = digitalRead(HIGH_BEAM_PIN);
  neutral = digitalRead(NEUTRAL_PIN);
  oilWarning = digitalRead(OIL_WARNING_PIN);
  waterTempWarning = digitalRead(WATER_TEMP_PIN);
  fuelWarning1 = digitalRead(FUEL_WARNING_1_PIN);
  fuelWarning2 = digitalRead(FUEL_WARNING_2_PIN);
  
  //read analog inputs:
  // - TODO: do something with BATTERY_VOLTAGE_PIN
}

