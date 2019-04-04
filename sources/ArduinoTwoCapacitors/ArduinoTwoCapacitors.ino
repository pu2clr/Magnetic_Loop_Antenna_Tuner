
/*
** Antenna Tuner for Magnetic Loop
** Simplified version of Antenna Tuner with two capacitors
** By PU2CLR
** Ricardo Lima Caratti
** April 3th, 2019.
*/

#include <Servo.h>

// Capacitor classe. It can help you to use more then one capacitor (servos) on your project
class Capacitor {
  private:
    Servo servo;
    int _max;
    int _min;
    int _pos;
    int _pin;
    int _alert_led;

  protected:
    void blink(int pinLED, int times = 1, int timeslice = 15);

  public:
    Capacitor();
    initCapacitor(int, int, int, int);
    int move(int);
    int clockwise(int);
    int counterClockwise(int);
    void maxPos(void);
    void minPos(void);
    void center(void);
    int getPos();
};

Capacitor::Capacitor()
{

}
// Attach the Servo (Capacitor) and LED to Arduino. Also define the servo pulses limits;
Capacitor::initCapacitor(int pinCap, int pinLed, int minPulse, int maxPulse)
{
  _pin = pinCap;
  _alert_led = pinLed;
  _min = minPulse;
  _max = maxPulse;
  pinMode(_alert_led, OUTPUT);
  pinMode(_pin, OUTPUT);
  servo.attach(_pin, _min, _max);
}

// Move the capacitor to a position
int Capacitor::move(int pos) {
  if ( pos >= _min && pos <= _max ) {
    _pos = pos;
    servo.writeMicroseconds(pos);
    delay(8);
    return 1;
  }
  return 0;
}

// turn the capacitor clockwise n pulses
int Capacitor::clockwise(int pulse) {

  int tmp = pulse + _pos;

  blink(_alert_led);

  if ( tmp <= _max ) {
    _pos += pulse;
    servo.writeMicroseconds(_pos);
    delay(10);
    return 1;
  }
  blink(_alert_led, 5, 100);
  return 0;

}

// turn the capacitor counter-clockwise n pulses
int Capacitor::counterClockwise(int pulse) {

  int tmp = _pos - pulse;

  blink(_alert_led);

  if ( tmp >= _min ) {
    _pos -= pulse;
    servo.writeMicroseconds(_pos);
    delay(10);
    return 1;
  }
  blink(_alert_led, 5, 100);
  return 0;
}

// turn the capacitor to the max position
void Capacitor::maxPos() {
  _pos = _max;
  servo.writeMicroseconds(_max);
  blink(_alert_led, 3, 100);
}

// turn the capacitor to the min position
void Capacitor::minPos() {
  _pos = _min;
  servo.writeMicroseconds(_min);
  blink(_alert_led, 3, 100);
}

// get the position of the servo (Capacitor)
int Capacitor::getPos() {
  return _pos;
}

// turn the capacitor to the center position
void Capacitor::center() {
  _pos = _min + ( _max - _min) / 2;
  servo.writeMicroseconds( _pos );
}

// blink the led attached to the capacitor
void Capacitor::blink(int pinLED, int times, int timeslice) {

  int i;
  for ( i = 0; i < times; i++ ) {
    digitalWrite(pinLED, HIGH);
    delay(timeslice);
    digitalWrite(pinLED, LOW);
  }


}

// Define pulse width modulation for fine, regular and large tune
#define FINE_TUNE 5    // short pulse on servo
#define NORMAL_TUNE 15 // regular pulse on servo
#define LARGE_TUNE 50  // large pulse on servo


#define SERVO_MAINCAP_PIN    9            // Arduino pin where the main capacitor (Servo) is connected
#define SERVO_FINECAP_PIN    8            // Arduino pin where the fine tune  capacitor (Servo) is connected

#define CAP_LED_PIN         13            // Define the status LED pin of the capacitor

#define MIN_PULSE          800          // Min. pulse of the servo (you need to know abour you servo specification)
#define MAX_PULSE         2200          // Max. pulse of the servo (you need to know abour you servo specification)

// Initiate the Servo (Capacitor) on Arduino PIN 9 and status LED on pin 13

Capacitor mainCap;   // Main capacitor
Capacitor fineCap;   // Fine tune capacitor 

void setup() {

     // Important: Drop out (disconnect) the Bluetooth from Arduino to upload this sketch to Arduino.
     Serial.begin(9600); // You have to know the speed of your bluetooth and set it up here. In this case it is 9600 bps

     // Attach the Capacitor to Servo and LED and setup Servo parameters as well
     mainCap.initCapacitor(SERVO_MAINCAP_PIN, CAP_LED_PIN, MIN_PULSE, MAX_PULSE);
     fineCap.initCapacitor(SERVO_FINECAP_PIN, CAP_LED_PIN, MIN_PULSE, MAX_PULSE);

     // Show that the capacitors are alive.
     mainCap.maxPos();
     delay(200);
     mainCap.minPos();
     delay(200);
     mainCap.center();
     delay(200);
     mainCap.center();

     fineCap.maxPos();
     delay(200);
     fineCap.minPos();
     fine(200);
     fineCap.center();
     delay(200);
     fineCap.center();

     // The system is ready to be used.
     // Now you can connect this device to your Android mobile via Bluetooth
}


// Convert the message sent by the Android Application to pulses (position of the servo) 
long translatePosition() {
  int i = 0;
  char cnumero;
  char snumero[11];
  long valor_numerico;

  while ( (cnumero = Serial.read()) != '#' && i < 11) {
    if ( cnumero >= '0' && cnumero <= '9' ) {
      snumero[i++] = cnumero;
      Serial.flush();
    }
  }
  if (i >= 11 ) i = 10;
  snumero[i] = 0;
  return atol(snumero);
}


void loop() {

  int c;
  // Begin serial communication read process begins
  if (Serial.available()) {
    switch ( c =  Serial.read() ) {
      case '+':
      case '=':
        fineCap.clockwise(FINE_TUNE);
        break;
      case '-':
        fineCap.counterClockwise(FINE_TUNE);
        break;
      case 'r':
        mainCap.clockwise(NORMAL_TUNE);
        break;
      case 'l':
        mainCap.counterClockwise(NORMAL_TUNE);
        break;
      case 'R':
        mainCap.clockwise(LARGE_TUNE);
        break;
      case 'L':
        mainCap.counterClockwise(LARGE_TUNE);
        break;
      case 'M':
        mainCap.maxPos();
        delay(200);
        fineCap.maxPos();
        break;
      case 'm':
        mainCap.minPos();
        delay(200);
        fineCap.minPos();
        break;
      case 'C':
      case 'c':
        mainCap.center();
        delay(200);
        fineCap.center();
        break;
      case 'F':
        mainCap.move(translatePosition());
        break;
      case 'T':
        mainCap.move(translatePosition());
        break;
      default:
        Serial.flush();
        break;
    }

  }   // End serial read process

}
// End file (PU2CLR).
