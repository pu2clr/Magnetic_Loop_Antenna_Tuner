
/*
** Antenna Tuner for Magnetic Loop 
**
** V1.2 - Ajuste no auto-tune - 3/10/2013
**
** Ricardo Lima Caratti - 3/11/2013
*/

#include <Servo.h>
#include <math.h>

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

 	
int Capacitor::move(int pos) {
    if ( pos >= _min && pos <= _max ) {
	   _pos = pos;	
	   servo.writeMicroseconds(pos);
           delay(8);
	   return 1;
	}
	return 0;
}

int Capacitor::clockwise(int pulse) {
  
  int tmp = pulse + _pos;
  
  blink(_alert_led);
  
  if ( tmp <= _max ) {
      _pos += pulse;
      servo.writeMicroseconds(_pos);
      delay(10);
     return 1; 
  }
  blink(_alert_led,5,100);
  return 0;
  
}

int Capacitor::counterClockwise(int pulse) {

  int tmp = _pos - pulse;

  blink(_alert_led);

  if ( tmp >= _min ) {
      _pos -= pulse;
      servo.writeMicroseconds(_pos);
      delay(10);
     return 1; 
  }
  blink(_alert_led,5,100);
  return 0;  
}

void Capacitor::maxPos() {
    _pos = _max;
    servo.writeMicroseconds(_max);
    blink(_alert_led,3,100);
}

void Capacitor::minPos() {
	_pos = _min;
	servo.writeMicroseconds(_min);
        blink(_alert_led,3,100);
}

int Capacitor::getPos() {
  return _pos;
}

void Capacitor::center() {
     _pos = _min + ( _max - _min) / 2; 
     servo.writeMicroseconds( _pos );
}

void Capacitor::blink(int pinLED, int times, int timeslice) {
      	
      int i;
      for ( i = 0; i < times; i++ ) {
		digitalWrite(pinLED, HIGH);
		delay(timeslice);
		digitalWrite(pinLED, LOW);		
      }
     
      	
}



// Define une steps (pulses)
#define FINE_TUNE            5            // 5 pulses for fine tune
#define NORMAL_TUNE          15           // 15 pulses for regular tune
#define LARGE_TUNE           50           // 50 pulses for large step tune

#define SERVO_PIN            9            // Pin where is connected the servo
#define CAP_LED_PIN         13            // Define the status LED pin of the capacitor

#define MIN_PULSE          800          // Min. pulse of the servo (you need to know abour you servo specification)
#define MAX_PULSE         2200          // Max. pulse of the servo (you need to know abour you servo specification)

// Initiate the Servo (Capacitor) on Arduino PIN 9 and status LED on pin 13
// Capacitor cap(SERVO_PIN, CAP_LED_PIN, MIN_PULSE, MAX_PULSE); 


Capacitor cap; 

void setup() {

  Serial.begin(9600);  

  // Serial.println("Iniciando o Capacitor");

  // Attach the Capacitor to Servo and LED and setup Servo parameters as well   
  cap.initCapacitor(SERVO_PIN, CAP_LED_PIN, MIN_PULSE, MAX_PULSE);

  cap.maxPos();
  delay(200);
  cap.minPos();
  

  delay(200);
   
  cap.center();
  delay(200);
  cap.center();
   
 
}



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
           cap.clockwise(FINE_TUNE); 
           break;
      case '-':
           cap.counterClockwise(FINE_TUNE);
           break;     
      case 'r':
           cap.clockwise(NORMAL_TUNE);
           break;
      case 'l':
           cap.counterClockwise(NORMAL_TUNE);     
           break;
      case 'R':
           cap.clockwise(LARGE_TUNE); 
           break;
      case 'L':
           cap.counterClockwise(LARGE_TUNE);        
           break;  
      case 'M':
           cap.maxPos();
           delay(200);
           cap.maxPos();
           break;  
      case 'm':
           cap.minPos();
           delay(200);
           cap.minPos();
           break;  
      case 'C': 
      case 'c': 
           cap.center();
           delay(200);
           cap.center();
           break;    
      case 'F': 
           // cap.move(translatePosition());
           cap.move(translatePosition());
           break;
       case 'T':
           cap.move(translatePosition());
           break;
       default:
           Serial.flush();
          break;
    }
    
    // Serial.print("Tune: ");
    // Serial.println(cap.getPos());
    // Serial.print("Fine: ");
    // Serial.println(cap.getPos()); 
    // Serial.println("Leitura: "); 
    // Serial.print(c);  
    
     

  }   // End serial read process

 }
// End file (PU2CLR). 
