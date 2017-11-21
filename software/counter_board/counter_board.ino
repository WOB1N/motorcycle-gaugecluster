
/*
  This ATTiny85 is responsible for counting pulses coming from the speedo- and tacho-
  sensors. These incoming signal frequencies fluctuate between 1-350Hz. This unit has
  three main requirements:

  A) Correct: Meaure the pulses as accurately as possible. This is also partially
     covered by filtering/debouncing hardware).

  B) Up-to-date: Communicate readings that are as recent as possible. For now, 
     this translates to the number of pulses measured in the last 500ms.

  C) Responsive: Respond instantly to I2C requests, so that the master have high
     refresh rates on the display.

  TODO1: Current engine rpm and speed surely are nice, but we also need total distance 
         and trip distance.
  TODO2: And possibly gear position?
*/
#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS 0x3
#define SPEEDO_SIGNAL PCINT3
#define TACHO_SIGNAL PCINT4
#define BUFFER_SIZE 5
#define LOOP_DELAY 100
#define LED PB1

volatile uint8_t speedo_counter = 0;
volatile uint8_t tacho_counter = 0;

uint8_t cache_index = 0;
uint8_t speedo_buffer[BUFFER_SIZE] = {0, 0, 0, 0, 0};
uint8_t tacho_buffer[BUFFER_SIZE] = {0, 0, 0, 0, 0};

uint16_t SPEEDO_DEBOUNCE_TIME = 500; //us = 0.5 ms
uint16_t TACHO_DEBOUNCE_TIME = 300;  //us = 0.3 ms


void setup() {
  // speedo and tacho signal pins are inputs
  pinMode(SPEEDO_SIGNAL, INPUT);
  pinMode(TACHO_SIGNAL, INPUT);

  // yay a debugging led always comes in handy
  pinMode(LED, OUTPUT);

  // the ATTiny-way to setup interrupts
  GIMSK |= (1 << PCIE);           // pin change interrupt enable
  PCMSK |= (1 << SPEEDO_SIGNAL);  // pin change interrupt enabled for speedoSignal pin
  PCMSK |= (1 << TACHO_SIGNAL);   // pin change interrupt enabled for tachoSignal pin

  // start the i2c slave
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(incomingI2CRequest);

  // enable interrupts
  sei();
}

/**
  For each sensor, there is a pulse-counter which is incremented by an interrupt-
  service-routine (ISR). There is also a buffer containing measurements. Every 100ms,
  this main loop wakes up and overwrites the oldest value in the buffer with the value
  of the counter. The counter is cleared, and the main loop goes to sleep for another
  100ms.

  The buffer contains 5 'countings' of pulses per 100ms. When the I2C master requests
  data, all values in the buffer are added up which gives us the total number of pulses
  in the last 500ms. But this data is only 100ms old (worst case)

  I have considered simpler approaches, but I believe this is the easiest way to be both
  accurate (long measurement interval) and up-to-date.

  Simply count with interrupts and clear the counters every 500ms: This won't work
  because we never know when the I2C master will request data. It's totally possible
  that we've only been counting for 400ms when the data-request comes in, and then we
  would miss out on the last 100ms (requirement A). In this case we could return the
  last known value of a completed measurement, but this data is 400ms old and this
  would not result in a very responsive display (hence requirement B).

  Decrease measurement interval and extrapolate the counters. Due to the relatively
  low signal frequencies I believe it's not acceptable to decrease the measurement
  interval (to +/-10ms?) and multiply the number of counted pulses (by 50?). I think
  this would result in a very high (multiplied) error ratio (which would clash with
  requirement A).
*/
void loop() {
  tws_delay(LOOP_DELAY);
  speedo_buffer[cache_index] = speedo_counter;
  speedo_counter = 0;
  tacho_buffer[cache_index] = tacho_counter;
  tacho_counter = 0;
  cache_index = (cache_index + 1) % BUFFER_SIZE;
  TinyWireS_stop_check();
}

/**
  ISR routine which does some very crude microsecond-time based debouncing. Notice
  that the debounce on the tacho is "tigher" than on the speedo, since the expected
  signal frequencies on the tacho are a bit higher. Also, this code only increments
  the counters on rising edge (while the routine is called on both rising and falling
  edge).

  NOTE TO SELF1: check if there is an easier way for edge detection? MCUCR?
  NOTE TO SELF2: buy oscilloscope to check if the debouncing actually works.
*/
uint8_t porthistory = 0x00;
ISR(PCINT0_vect) {
  uint32_t current_time = 0;
  uint8_t changedbits = PINB ^ porthistory;
  porthistory = PINB;

  static boolean tacho_toggle = true; // act on rising edge only
  tacho_toggle = !tacho_toggle;
  if (tacho_toggle) {
    current_time = micros(); // very crude debouncing
    if (changedbits & (1 << TACHO_SIGNAL)) {
      static uint32_t last_tacho_interrupt = 0;
      if (current_time - last_tacho_interrupt > TACHO_DEBOUNCE_TIME) {
        tacho_counter++;
      }
      last_tacho_interrupt = current_time;
    }
  }

  static boolean speedo_toggle = true; // act on rising edge only
  speedo_toggle = !speedo_toggle;
  if (speedo_toggle) {
    current_time = micros(); // very crude debouncing
    if (changedbits & (1 << SPEEDO_SIGNAL)) {
      static uint32_t last_speedo_interrupt = 0;
      if (current_time - last_speedo_interrupt > SPEEDO_DEBOUNCE_TIME) {
        speedo_counter++;
      }
      last_speedo_interrupt = current_time;
    }
  }
}

/*
  When the I2C-master requests for data, this function:
  A) Calculates the sum of both buffers (which gives us total pulses over the last 500ms).
      This results in two 16bit integers: totalSpeedo and totalTacho.
  B) Instructs TinyWire to respond with 4 bytes:
     1: Most significant byte of totalSpeedo
     2: Least significant byte of totalSpeedo
     3: Most significant byte of totalTacho
     4: Least significant byte of totalTacho
*/
boolean led_state = LOW;
void incomingI2CRequest() {
  led_state = !led_state;
  digitalWrite(LED, led_state);

  uint16_t totalSpeedo = 0;
  uint16_t totalTacho = 0;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    totalSpeedo += speedo_buffer[i];
    totalTacho += tacho_buffer[i];
  }

  TinyWireS.send(totalSpeedo >> 8);
  TinyWireS.send(totalSpeedo & 0xFF);
  TinyWireS.send(totalTacho >> 8);
  TinyWireS.send(totalTacho & 0xFF);
}
