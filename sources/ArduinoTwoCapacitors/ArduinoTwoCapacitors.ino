
/*
** Antenna Tuner with two capacitors
** 
** Ricardo Lima Caratti - PU2CLR
*/

#include "Servo.h"

// Class to controll Capacitor

class Capacitor {
  	private:
  		Servo servo;
  		int _max;        
  		int _min;
  		int _pos;
                int _pin;
                int _alert_led;
                int _relay_pin;
  		
  		
  	protected:
  	    void blink(int pinLED, int times = 1, int timeslice = 15);	
  	    int cancel();
            void switchToSWR();        // Switch from Antenna to SWR meter
            void switchToAntenna();  // Switch from SWR meter to Antenna
  		
	public:  
    	    Capacitor(int );
    	    int attach(int pin = 9, int min = 500, int max = 2500);
	    int move(int);
            int clockwise(int, int);
            int counterClockwise(int, int);
    	    void maxPos(void);
    	    void minPos(void);
            void center(void);
    	    int autoTune(int resolution = 1,  int adjust = 0, int led = 13, int analogPin = 3, int checkCancel = 0);
            int autoTune(int resolution, int adjust, int pinLED, int analogPin);  
            void setAlertLed(int led = 13);
            int getPos();
            void setRelayPin(int pin);
            
}; 


Capacitor::Capacitor(int pin) {
      _pin = pin;
      _alert_led = 13;	
}

// Connect the capacitor to the servo
int Capacitor::attach(int pin, int min, int max) {
    _min = min;
    _max = max;
    _pin = pin;
    servo.attach(_pin, min, max);	
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

int Capacitor::clockwise(int pulse, int led = 13) {
  
  int tmp = pulse + _pos;
  
  blink(led);
  
  if ( tmp <= _max ) {
      _pos += pulse;
      servo.writeMicroseconds(_pos);
      delay(10);
     return 1; 
  }
  blink(_alert_led,5,100);
  return 0;
  
}

int Capacitor::counterClockwise(int pulse, int led = 13) {

  int tmp = _pos - pulse;

  blink(led);

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

void Capacitor::setAlertLed(int led) {

      _alert_led = led;
}


int Capacitor::autoTune(int resolution, int adjust, int pinLED, int analogPin, int checkCancel) {

     int i; 
     int j;
     
     int tuned;
   
     // Start scaning. Positions the capacitor according to the range to be searched.
     this->minPos();

     
     int maxValue = 0;
     int minValue = 9999;
     int positionMaxValue;

     int pwrValue;
     int swrValue;
     int firstReading;
     
     this->switchToSWR();
     // Register the lowest SWR 
     for ( i = _min; i <= _max; i+=resolution ) {
       this->move(i);
       // delay(10);

       swrValue = analogRead(analogPin);    
    
       if ( swrValue < minValue ) {
           minValue = swrValue;
           positionMaxValue = i;
       }       

     }


     // Try to correct to right posiction (backlash). 
     // Must be calibrated according to the component parts features
     positionMaxValue += adjust;

     blink(pinLED, 3);
     blink(pinLED, 3);

     this->move(positionMaxValue);
     
     this->switchToAntenna();
}


int Capacitor::autoTune(int resolution, int adjust, int pinLED, int analogPin) {

     int i,n = 0;
     int x;               // Event
     int sX;              // Sum event value
     double sX2 =  0.0;   // Sum event value ˆ 2
     double std;          // stdev 
     double std_old;      // stdev old reading (save the last stdev   
     double p;            // percent of stdev (1 - std/std_old)
    
    
    

     this->switchToSWR();
 
     delay(15);
     
 
     // Process the first reading
     this->move(_min);
     x = analogRead(analogPin); 
     sX += x;
     sX2 +=  pow( (double) x, 2);
     n++;
    
     delay(15);
     // Process the secound reading
     this->move(_min);
     x = analogRead(analogPin); 
     sX += x;
     sX2 +=  pow( (double) x, 2);
     n++;
     
     std_old = std = ( sX2 - ( pow(sX,2) / (double) n) ) / (double(n) - 1.0);
    
     // Look for the lowest SWR
     for ( i = _min; i <= _max; i+=resolution ) {
         this->move(i);
         x = analogRead(analogPin);    
         sX += x;
         sX2 +=  pow( (double) x, 2);
         std = ( sX2 - ( pow(sX,2) / (double) n) ) / (double(n) - 1.0);
         
         n++;

  
     }
  
  
  this->switchToAntenna();
  return 0;
}


void Capacitor::blink(int pinLED, int times, int timeslice) {
      	
      int i;
      for ( i = 0; i < times; i++ ) {
		digitalWrite(pinLED, HIGH);
		delay(timeslice);
		digitalWrite(pinLED, LOW);		
      }
     
      	
}


int Capacitor::cancel() {
    char c;
    if (Serial.available())  {
      c = Serial.read();
      if ( c == 'C' || c == 'c' ) return 1;   
    }
   return 0;
}


void Capacitor::switchToSWR() {
  digitalWrite(_relay_pin, HIGH); 
}


void Capacitor::switchToAntenna() {
  digitalWrite(_relay_pin, LOW); 
}


void Capacitor::setRelayPin(int pin) {
  _relay_pin = pin;
  this->switchToSWR();
  delay(500);
  this->switchToAntenna();
}


// Begin

// Define Arduino Pin usage and some constants.

#define CAP_NORMAL_TUNE      9    // Arduino pin 9 to capacitor for regular tune
#define CAP_FINE_TUNE        8    // Arduino pin 8 to capacitor for fine tune

#define YELLOW_LED           7    
#define GREEN_LED            6
#define BLUE_LED             5
#define RED_LED             13
#define ENCODER_A_PIN       12  
#define ENCODER_B_PIN       11
#define SWR_RELAY            3    // Switch the relay to SWR Meter
#define SWITCH_ATU_FINE      4
#define FINE_TUNE_LED       10


#define ANALOG_PIN            3   // Arduino Analog Input 

#define MIN_PULSE          600    // This value depends of the servo feature (Min Position 0 degree) 
#define MAX_PULSE         2500    // This value depends of the servo feature (Max Position tends to 180 degree)


#define FINE_TUNE            5    // Fine-tune step (resolution) when using encoder
#define NORMAL_TUNE         15    // Regular setp (resolution) when using encoder
#define LARGE_TUNE          50    // Fast step



// Some global variables to control the encoder

unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;
unsigned long currentTime;
unsigned long loopTime;

int fineTune = 0;


// Create Capacitors instances

Capacitor capLarge(CAP_NORMAL_TUNE);     
Capacitor capFine(CAP_FINE_TUNE);      


// Just blink a LED
// pin    => Arduino pin
// times  => number of blinks
// ms     => delay in milliseconds.
void blink(int pin, int times, int ms = 15) {
  int i;
  for (i = 0; i < times; i++ ) {
     digitalWrite(pin,HIGH);
     delay(ms);
     digitalWrite(pin,LOW);
     delay(ms);
  }
  digitalWrite(pin,LOW);  
}


// t is executed once at the beginning
  void setup() {
  
    
    // Define Input and Output pins
     pinMode(SWITCH_ATU_FINE,INPUT); 
     pinMode(ENCODER_A_PIN, INPUT);
     pinMode(ENCODER_B_PIN, INPUT);   
     
     pinMode(FINE_TUNE_LED,OUTPUT);     
     pinMode(YELLOW_LED ,OUTPUT);
     pinMode(GREEN_LED ,OUTPUT);
     pinMode(BLUE_LED ,OUTPUT);    
     pinMode(RED_LED ,OUTPUT);  
     pinMode(SWR_RELAY, OUTPUT);
   
     // SWR Meter relay switch check
     capLarge.setRelayPin(SWR_RELAY);
     capFine.setRelayPin(SWR_RELAY);
    
     // Setup the serial communication (bluetooth)
     Serial.begin(9600);  
    
     // Move the capacitors to minimum position (0 degree)
     capLarge.attach(MIN_PULSE, MAX_PULSE);     
     capFine.attach(MIN_PULSE, MAX_PULSE);   
  
     // Check LEDs
     blink(YELLOW_LED,10,50);
     delay(500);
     blink(GREEN_LED,10,50);
     delay(500);
     blink(BLUE_LED,10,50);
     delay(500);
     blink(RED_LED,10,50);
     delay(500);
     blink(FINE_TUNE_LED,10,50);
     
     // Check the Capacitors 
     capLarge.maxPos();
     delay(200);
     capLarge.minPos();
    
     capFine.maxPos();
     delay(200);
     capFine.minPos();
    
     delay(200);
     
     // Move Capacitors to the center
     capLarge.center();
     delay(200);
     capFine.center();
       
     // Turn off the fine-tune LED
     digitalWrite(FINE_TUNE_LED,LOW);
   
  }


void switchTune() 
{
  fineTune = !fineTune;

  if (fineTune )  {
      digitalWrite(FINE_TUNE_LED, HIGH);
  }
  else {
     digitalWrite(FINE_TUNE_LED, LOW);
  } 

  delay(500);  
} 


// Translate message sent from external device (Bluetooth)
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



// The main program
void loop() {
  
   currentTime = millis();
  
  // Begin serial read process 
  if (Serial.available()) {
    switch ( Serial.read() ) {
      case '+':
      case '=':
           capFine.clockwise(FINE_TUNE,GREEN_LED); 
           break;
      case '-':
           capFine.counterClockwise(FINE_TUNE,GREEN_LED);
           break;     
      case 'r':
           capLarge.clockwise(NORMAL_TUNE, YELLOW_LED);
           break;
      case 'l':
           capLarge.counterClockwise(NORMAL_TUNE,YELLOW_LED);     
           break;
      case 'R':
           capLarge.clockwise(LARGE_TUNE,BLUE_LED); 
           break;
      case 'L':
           capLarge.counterClockwise(LARGE_TUNE,BLUE_LED);        
           break;  
      case 'M':
           capLarge.maxPos();
           delay(200);
           capFine.maxPos();
           break;  
      case 'm':
           capLarge.minPos();
           delay(200);
           capFine.minPos();
           break;  
      case 'C': 
      case 'c': 
           capLarge.center();
           delay(200);
           capFine.center();
           break;    
      case 'S':
      case 's':
           // Try to tune           
           capLarge.autoTune(6, -30, 13, ANALOG_PIN, 0);   // Main tune
           delay(250);
           capFine.autoTune(18, -30, 13, ANALOG_PIN, 0);   // Fine tune
           break;  
      case 'T':
           capLarge.move(translatePosition());
           break;
      case 'A':
           capLarge.move(translatePosition());
           break;
      case 'F': 
           capFine.move(translatePosition());
           break;
       default:
           Serial.flush();
           break;
    }

  }   // End serial read process
  else {
    // Check encoder activity  
    if(currentTime >= (loopTime + 5)) {
       // 5ms since last check of encoder = 200Hz  
       encoder_A = digitalRead(ENCODER_A_PIN);    // Read encoder pins
       encoder_B = digitalRead(ENCODER_B_PIN);   
       if((!encoder_A) && (encoder_A_prev)){
         // A has gone from high to low 
         if(encoder_B) {  
           // B is high so clockwise
           // increase the capacitorPosition, dont go over 255
           // increment = tuneStep; 
           if ( fineTune )
              capFine.clockwise(FINE_TUNE, GREEN_LED);
           else
              capLarge.clockwise(FINE_TUNE, BLUE_LED);   
         }   
       else {
          // B is low so counter-clockwise      
          // decrease the capacitorPosition, dont go below 0
           // increment = -tuneStep;  
           if ( fineTune ) 
              capFine.counterClockwise(FINE_TUNE, GREEN_LED);
           else
              capLarge.counterClockwise(FINE_TUNE, BLUE_LED);    
        }   
      }   
       encoder_A_prev = encoder_A;     // Store value of A for next time    
      loopTime = currentTime;  // Updates loopTime
    }  
  }
  
   if ( digitalRead(SWITCH_ATU_FINE) == LOW) { 
     switchTune();
   }
     
  
}
// End file (PU2CLR) - V1.3 - For two Capacitors






