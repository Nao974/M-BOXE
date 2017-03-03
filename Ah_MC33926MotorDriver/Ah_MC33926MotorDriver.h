#ifndef Ah_MC33926MotorDriver_h
#define Ah_MC33926MotorDriver_h

#include <Arduino.h>

class Ah_MC33926MotorDriver
{
  public:  
    // CONSTRUCTORS
    Ah_MC33926MotorDriver(); // Default pin selection.
    Ah_MC33926MotorDriver(unsigned char DIR, unsigned char PWM, unsigned char FB,
                           unsigned char nSF); // User-defined pin selection. 
    
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
    void setSpeed(int speed, int index); // Set speed for M1.
    unsigned int getCurrentMilliamps(); // Get current reading for M1. 
    unsigned char getFault(); // Get fault reading.
    
  private:
    unsigned char _DIR; //_INV
//    static const unsigned char _PWM = 9;
	unsigned char _PWM;
    unsigned char _FB;
    unsigned char _nSF;
};

#endif