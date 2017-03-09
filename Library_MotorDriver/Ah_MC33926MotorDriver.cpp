#include "Ah_MC33926MotorDriver.h"

// Constructors ////////////////////////////////////////////////////////////////

Ah_MC33926MotorDriver::Ah_MC33926MotorDriver()
{
  //Pin map
  _DIR = 8; //_INV
  _PWM= 9;
  _nSF = 10;
  _FB = A0; 
}

Ah_MC33926MotorDriver::Ah_MC33926MotorDriver(unsigned char DIR, unsigned char PWM, unsigned char FB,
                           unsigned char nSF)
{
  //Pin map
  //PWM cannot be remapped because the library assumes PWM is on timer1
  _DIR = DIR; // _INV
  _PWM = PWM;
  _FB = FB; 
  _nSF = nSF;
}

// Public Methods //////////////////////////////////////////////////////////////
void Ah_MC33926MotorDriver::init()
{
// Define pinMode for the pins and set the frequency for timer1.
  pinMode(_DIR,OUTPUT);
  pinMode(_PWM,OUTPUT);
  pinMode(_FB,INPUT);
  pinMode(_nSF,INPUT);

  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__)
  // Timer 1 configuration ==> For PIN 9
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  // 
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
  #endif
}

// Set speed for motor, speed is a number betwenn -400 and 400
void Ah_MC33926MotorDriver::setSpeed(int speed, int index)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;
	
  speed +=index;
  
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__)
	OCR1A = speed;
  #else
	analogWrite(_PWM,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
  if (reverse)
    digitalWrite(_DIR,HIGH);
  else
    digitalWrite(_DIR,LOW);
}

// Return motor current value in milliamps.
unsigned int Ah_MC33926MotorDriver::getCurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_FB) * 9;
}

// Return error status
unsigned char Ah_MC33926MotorDriver::getFault()
{
  return !digitalRead(_nSF);
}