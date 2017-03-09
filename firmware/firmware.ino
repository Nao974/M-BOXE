#include <EEPROM.h>

#include <Ah_MC33926MotorDriver.h> // Control Motor Library
#include <Wire.h>

#define DEBUG  false  

/*** Configuration ***/
struct mboxeType 
{
  word positionSet, limitBW, limitFW, limitBWPOTA, limitFWPOTA, deadBand;
  char offSet, infoConfig[16], skeletonPosition[5];
  float kp, kd, ki, versionCode;
  byte speedSet, currentMaxSet, protectionGoSet, temperatureMaxSet;
};

mboxeType mBoxe={750, 350, 1150, 20, 1000, 200, 
                  0,"V0.3 2016-08", "LA01",
                  1,2,0,0.25,
                  255, 40, 20,102
                };

#define SLAVE_ADDRESS 0x14
char commandI2C=0xF0, dataByte[16], state = 0x00, mode = 0x00;
/*** ***/

/*** PIN definition ***/
// PIN control motor are defined in the library 
static unsigned char pinAngle = A1; //Potentiometer on the motor shaft
/*** ***/

/*** Variables motor control ***/
Ah_MC33926MotorDriver md;
/*** ***/

/*** Variables PID control ***/
int error=0, resultPID=0;
float errorPrevious= 0;
float errorSum=0;
/*** ***/

// Others Variables/Constants
int time=0; //time graph
word positionCurrent=0, pinA2=123, pinA3=321, speedMotor, temp;
byte speedCurrent=0, currentCurrent=0, protectionCurrent=0, contactBWFW=0, portD=0;
float temperatureCurrent;

void setup() 
{
/*** PIN control motor are initialized in the library ***/

/*** Init Led ***/
// RED LED ON / GREEN LED OFF
/*** ***/

/*** Timer 2 configuration ***/
  TCCR2A=B010; // mode CTC (Clear Timer on Compare)
  OCR2A=156; // Register Comparaison A=156
  TCCR2B=B111; // Prescaler 1024 (clock / 1024)
  TIMSK2=B010;  // IT Timer2 quand TCNT2= OCR2A
// 16/(1024*156) = 100 hz => 1/100 sec
  sei(); // activation interrupts (SREG.7=1)
/*** ***/

/*** Loading Parameters from Eprom ***/
// EEPROM.get(0, mBoxe);
/*** ***/

/** Init Motor ***/
  md.init(); // Init Control Motor
  md.setSpeed(0,0); // Stop Motor
 //stopIfFault();
  delay(300); //0.3 sec pause to allow time for the engine to stop if it is running
/*** ***/


/*** initialize i2c ***/ 
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveDataInit);
  Wire.onRequest(sendDataInit);
/*** ***/


/*** Init Port COM si Debug ***/
#if DEBUG== true
  Serial.begin(9600);  
#endif
/*** ***/

/*** Set PIN as input ***/
DDRD = B00000000; // Set portD all Input (Pin 0 -> 7)
DDRB = DDRB & B00111111; // set  PIN12 & PIN13 as INPUT without changing the value of pins 08 -> 11

/*** ***/

}
 
void loop() 
{
// Debug
#if DEBUG== true
  time += 10;
  Serial.println("time\tpositionCurrent\tpositionSet\tError\tresultPID"); 
  Serial.print(time);
  Serial.print("\t");
  Serial.print(positionCurrent);
  Serial.print("\t");
  Serial.print(mBoxe.positionSet);
  Serial.print("\t");
  Serial.print(error);
  Serial.print("\t");
  Serial.println(resultPID);  
#endif 
 
 currentCurrent = md.getCurrentMilliamps();
 protectionCurrent = md.getFault();
 temperatureCurrent = GetTemperature();
 portD = PIND;
 pinA2 = analogRead(A2);
 pinA3 = analogRead(A3);
 contactBWFW = PINB;  // For PIN13 & PIN12
 delay(500);

}

// This function is called by interruption TIMER2 for calculating the PID controller
ISR(TIMER2_COMPA_vect)
{
  positionCurrent = analogRead(pinAngle);
  error = mBoxe.positionSet - positionCurrent;
  errorSum += error;

  // Calculation of the next speed motor
  resultPID = mBoxe.kp * error + mBoxe.kd * (error - errorPrevious) + mBoxe.ki * (errorSum);
  errorPrevious = error; // Overwrite the previous error by another error

  if ( (resultPID>0 && positionCurrent<mBoxe.limitFWPOTA) || (resultPID<0 && positionCurrent>mBoxe.limitBWPOTA) )
    md.setSpeed(resultPID,mBoxe.deadBand); // Motor control*/
}
 
// callback for received data IniT
void receiveDataInit(int howMany)
{ 
 int byteCounter=0;

 while( byteCounter < howMany ) 
  {
    byte b = Wire.read();     
    if( byteCounter == 0) 
      commandI2C = b;
    else
      dataByte[byteCounter-1]=b;
    byteCounter += 1;    
  }  

  switch (commandI2C)
    {         
     case 0x50: mBoxe.positionSet= map(Receive_Word(dataByte),350, 1150, mBoxe.limitBWPOTA, mBoxe.limitFWPOTA)+mBoxe.offSet; break;
     case 0x51: mBoxe.speedSet= dataByte[0]; break;
     case 0x00: 
     case 0x01: 
     case 0x02: 
     case 0x03: mode=commandI2C; break;
     case 0x10: EEPROM.get(0, mBoxe); break;
     case 0x11: EEPROM.put(0, mBoxe); break;    
     case 0x30: mBoxe.limitBW= Receive_Word(dataByte); break; //map(Receive_Word(dataByte),350, 1150, mBoxe.limitBWPOTA, mBoxe.limitFWPOTA); break;
     case 0x31: mBoxe.limitFW= Receive_Word(dataByte); break; //map(Receive_Word(dataByte),350, 1150, mBoxe.limitBWPOTA, mBoxe.limitFWPOTA); break;
     case 0x32: mBoxe.offSet= dataByte[0]; break;
     case 0x33: mBoxe.deadBand= Receive_Word(dataByte); break;
     case 0x34: mBoxe.kp= Receive_Float(dataByte); break;
     case 0x35: mBoxe.kd= Receive_Float(dataByte); break;
     case 0x36: mBoxe.ki= Receive_Float(dataByte); break;
     case 0x37: 
     case 0x38: mBoxe.currentMaxSet= dataByte[0]; break;
     case 0x39: mBoxe.protectionGoSet= dataByte[0]; break;
     case 0x3A: mBoxe.temperatureMaxSet= dataByte[0]; break;
     case 0x3B: mBoxe.versionCode= Receive_Float(dataByte); break;
     case 0x3C: strncpy(mBoxe.infoConfig,dataByte,sizeof(dataByte)); break;
     case 0x3D: strncpy(mBoxe.skeletonPosition,dataByte,sizeof(dataByte)); break;
     default: break;
    }
}
 
// callback for sending data
void sendDataInit()
{
 switch (commandI2C)
  {
   case 0x20: Wire_SendWord(&mBoxe.limitBW); break; //temp=map(mBoxe.limitBW, mBoxe.limitBWPOTA, mBoxe.limitFWPOTA, 350, 1150); Wire_SendWord(&temp); break;
   case 0x21: Wire_SendWord(&mBoxe.limitFW); break; //temp=map(mBoxe.limitFW, mBoxe.limitBWPOTA, mBoxe.limitFWPOTA, 350, 1150); Wire_SendWord(&temp); break;
   case 0x22: Wire.write(mBoxe.offSet); break;     
   case 0x23: Wire_SendWord(&mBoxe.deadBand); break;     
   case 0x24: Wire_SendFloat(&mBoxe.kp); break;     
   case 0x25: Wire_SendFloat(&mBoxe.kd); break;    
   case 0x26: Wire_SendFloat(&mBoxe.ki); break;    
   case 0x27: Wire.write(mBoxe.speedSet); break;     
   case 0x28: Wire.write(mBoxe.currentMaxSet); break;     
   case 0x29: Wire.write(mBoxe.protectionGoSet); break;     
   case 0x2A: Wire.write(mBoxe.temperatureMaxSet); break;     
     case 0x2B: Wire_SendFloat(&mBoxe.versionCode); break;       
   case 0x2C: Wire.write(mBoxe.infoConfig,16); break;
   case 0x2D: Wire.write(mBoxe.skeletonPosition,4); break;
   case 0x2E: Wire.write(mode); break;     
   case 0x2F: Wire.write(state); break;     
   case 0x40: temp=map(positionCurrent, mBoxe.limitBWPOTA, mBoxe.limitFWPOTA, 350, 1150); Wire_SendWord(&temp); break;
   case 0x41: Wire.write(speedCurrent); break;     
   case 0x42: Wire.write(currentCurrent); break;     
   case 0x43: Wire_SendFloat(&temperatureCurrent); break;     
   case 0x44: Wire.write(protectionCurrent); break;    
   case 0x45: Wire.write(portD); break;     
   case 0x46: Wire_SendWord(&pinA2); break;
   case 0x47: Wire_SendWord(&pinA3); break;
   case 0x48: Wire.write(contactBWFW); break;
  }
}

// callback for received data
void receiveData(int byteCount)
{ 
}

// callback for sending data
void sendData()
{
}

void Wire_SendWord( word* w)
{
 union Sharedblock
  {
   byte part[2];
   word data;
  } mon_blockW;

  mon_blockW.data = *w;
  Wire.write( mon_blockW.part, 2 );
}

word Receive_Word( char* b)
{
 union Sharedblock
  {
   char part[2];
   word data;
  } mon_blockW;

  mon_blockW.part[0]=(byte) b[0];
  mon_blockW.part[1]=(byte) b[1];
  return mon_blockW.data;
}

void Wire_SendFloat( float* f)
{
 union Sharedblock
  {
   byte part[4];
   float data;
  } mon_blockF;

  mon_blockF.data = *f;
  Wire.write( mon_blockF.part, 4 );
}

float Receive_Float( char* b)
{
 union Sharedblock
  {
   byte part[4];
   float data;
  } mon_blockF;

  mon_blockF.part[0]=(byte) b[0];
  mon_blockF.part[1]=(byte) b[1];
  mon_blockF.part[2]=(byte) b[2];
  mon_blockF.part[3]=(byte) b[3];
  return mon_blockF.data;
}

// Get the internal temperature of the Arduino
float GetTemperature(void)
{
  return (20.5);
  /*ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC
  delay(20);            // wait for voltages to become stable.
  ADCSRA |= _BV(ADSC);  // Start the ADC
  while (bit_is_set(ADCSRA,ADSC)); // Detect end-of-conversion
  return( 5+(ADCW - 324.31 ) / 1.22); // 5 = diff avec temperature ambiante*/
}

