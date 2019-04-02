
/*
** Antenna Tuner for Magnetic Loop 
**
** V1.2 - Ajuste no auto-tune - 3/10/2013
**
** Ricardo Lima Caratti - 3/11/2013
*/

#include "Servo.h"
#include "math.h"

#define DSSS -18
#define Dsss -13
#define ACC1 0.66
#define ACC2 0.35

int switchSWR(); 

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
  	    int cancel();
  		
	public:  
    	    Capacitor(int );
    	    int attach(int, int);
	    int move(int);
            int clockwise(int, int);
            int counterClockwise(int, int);
    	    void maxPos(void);
    	    void minPos(void);
            void center(void);
    	    int autoTune(int resolution = 1,  int adjust = 0, int led = 13, int analogPin = 3, int checkCancel = 0);
            int autoTune(double ref = 0.85, int adjust = 0, int led = 13, int analogPin = 3);
            void setAlertLed(int led = 13);
            int getPos();
            
}; 


Capacitor::Capacitor(int pin) {
      _pin = pin;
      _alert_led = 13;	
}

int Capacitor::attach(int min, int max) {
    _min = min;
    _max = max;
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
     
     switchSWR();
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
}


int Capacitor::autoTune(double ref, int adjust, int pinLED, int analogPin) {

     int i,n = 0;
     int x;               // Event
     double xbar = 0;
     double s = 0;
   
     delay(15);
     
 
     // Process the first reading
     this->move(_min);
     x = analogRead(analogPin); 
     s += x;
     n++;
    
     delay(15);
     // Process the secound reading
     this->move(_min);
     x = analogRead(analogPin); 
     s += x;
     n++;
     
     xbar = s / double(n);
    
     // Look for the lowest SWR
     for ( i = _min; i <= _max; i+=1 ) {
         this->move(i);
         x = analogRead(analogPin);   
         s += x; 
         n++;
         
         if ( abs(1 - (x/xbar)) >= ref )   break;
         
         xbar = s / double(n);
  
     }
  
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



#define CAP_NORMAL_TUNE      9    // Arduino pin 9 to capacitor for normal tune
#define CAP_FINE_TUNE        8    // Arduino pin 8 to capacitor for fine tune

#define MIN_PULSE          600
#define MAX_PULSE         2500


#define FINE_TUNE              5
#define NORMAL_TUNE           15
#define LARGE_TUNE            50

#define ENCODER_A_PIN         12  
#define ENCODER_B_PIN         11

#define SWITCH_TO_SWR          3      // Switch the relay to SWR Meter
#define SWITCH_TO_ANTENNA      4      // Switch the relay to Antenna


#define FINE_TUNE_LED        10

#define YELLOW_LED            7
#define GREEN_LED             6
#define BLUE_LED              5
#define RED_LED              13

#define ANALOG_PIN            3


unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;
unsigned long currentTime;
unsigned long loopTime;

int fineTune = 0;


Capacitor capLarge(CAP_NORMAL_TUNE);     
Capacitor capFine(CAP_FINE_TUNE);      


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

void setup() {

   pinMode(ENCODER_A_PIN, INPUT);
   pinMode(ENCODER_B_PIN, INPUT);   
   
   pinMode(FINE_TUNE_LED,OUTPUT);     
   pinMode(YELLOW_LED ,OUTPUT);
   pinMode(GREEN_LED ,OUTPUT);
   pinMode(BLUE_LED ,OUTPUT);    
   pinMode(RED_LED ,OUTPUT);    


   pinMode(SWITCH_TO_SWR, OUTPUT);
   pinMode(SWITCH_TO_ANTENNA, OUTPUT);   
 
 
   // SWR Meter switch check
   digitalWrite(SWITCH_TO_SWR, HIGH);
   delay(100);
   digitalWrite(SWITCH_TO_SWR, LOW);
  
   delay(1000);
  
   // Antenna switch check
   digitalWrite(SWITCH_TO_ANTENNA, HIGH);
   delay(100);
   digitalWrite(SWITCH_TO_ANTENNA, LOW);     
 
  
   Serial.begin(9600);  
  
   capLarge.attach(MIN_PULSE, MAX_PULSE);     
   capFine.attach(MIN_PULSE, MAX_PULSE);   



   blink(YELLOW_LED,10,50);
   delay(500);
   blink(GREEN_LED,10,50);
   delay(500);
   blink(BLUE_LED,10,50);
   delay(500);
   blink(RED_LED,10,50);
   delay(500);
   blink(FINE_TUNE_LED,10,50);
   
  capLarge.maxPos();
  delay(200);
  capLarge.minPos();
  
  capFine.maxPos();
  delay(200);
  capFine.minPos();
  
  delay(200);
   
  capLarge.center();
  delay(200);
  capFine.center();
   
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

int switchAntenna() {
    // digitalWrite(SWITCH_TO_ANTENNA, HIGH);
    // delay(500);
    // digitalWrite(SWITCH_TO_ANTENNA, LOW);
    digitalWrite(SWITCH_TO_SWR, LOW);
}

int switchSWR() {
    // digitalWrite(SWITCH_TO_SWR, HIGH);
    // delay(500);
    // digitalWrite(SWITCH_TO_SWR, LOW);  
    digitalWrite(SWITCH_TO_SWR, HIGH);
}



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
           // Switch relay to SWR meter (Radio->SWR Meter-> Antenna)
           switchSWR();        
           // Try to tune           
           // capLarge.autoTune(1, DSSS, 13, ANALOG_PIN, 0);   
           capLarge.autoTune(ACC1, 0, 13, ANALOG_PIN);
           // Go back to orininal position (Radio->Antenna)
           switchAntenna();                           
           break;  
      case 's': 
           // Switch relay to SWR meter (Radio->SWR Meter-> Antenna)
           switchSWR();        
           // Try to tune           
           // capLarge.autoTune(1, Dsss ,13, ANALOG_PIN, 0);   
           capLarge.autoTune(ACC2, 0, 13, ANALOG_PIN);
           // Go back to orininal position (Radio->Antenna)
           switchAntenna();                           
           break;  
      case 'F': 
           // capFine.move(translatePosition());
           capLarge.move(translatePosition());
           break;
       case 'T':
           capLarge.move(translatePosition());
           break;
       default:
           Serial.flush();
          break;
    }
    /*
    Serial.print("Tune: ");
    Serial.println(capLarge.getPos());
    Serial.print("Fine: ");
    Serial.println(capFine.getPos());    
    */
     

  }   // End serial read process
  else {
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
  
  
}
// End file (PU2CLR). 
