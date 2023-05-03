#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif


//myVariable
MPU6050 mpu;
int dt=10; //mpu data processing delay utk mulusin jalannya mesin
float aThreshold=0.25; //percepatan ke atas minimal agar langkah dihitung
int dThreshold=2; //lama minimal a>aThreshold agar langkah kehitung. lama=(dThreshold * dt)ms
int bpm=120; //default bpm
#define songCount 3 //kalau jumlahnya diubh, ubh jg fungsi chooseSong(int choosed) dan array songLength[]
#define defaultSong song2 //ubh jg variable *song dan choosed
#define dStopRun 3000 //brp ms sampe dihitung berhenti lari
#define chooseAlarm 3 //alarm itu song brp?


//note
#define nB0  31
#define nC1  33
#define nCS1 35
#define nD1  37
#define nDS1 39
#define nE1  41
#define nF1  44
#define nFS1 46
#define nG1  49
#define nGS1 52
#define nA1  55
#define nAS1 58
#define nB1  62
#define nC2  65
#define nCS2 69
#define nD2  73
#define nDS2 78
#define nE2  82
#define nF2  87
#define nFS2 93
#define nG2  98
#define nGS2 104
#define nA2  110
#define nAS2 117
#define nB2  123
#define nC3  131
#define nCS3 139
#define nD3  147
#define nDS3 156
#define nE3  165
#define nF3  175
#define nFS3 185
#define nG3  196
#define nGS3 208
#define nA3  220
#define nAS3 233
#define nB3  247
#define nC4  262
#define nCS4 277
#define nD4  294
#define nDS4 311
#define nE4  330
#define nF4  349
#define nFS4 370
#define nG4  392
#define nGS4 415
#define nA4  440
#define nAS4 466
#define nB4  494
#define nC5  523
#define nCS5 554
#define nD5  587
#define nDS5 622
#define nE5  659
#define nF5  698
#define nFS5 740
#define nG5  784
#define nGS5 831
#define nA5  880
#define nAS5 932
#define nB5  988
#define nC6  1047
#define nCS6 1109
#define nD6  1175
#define nDS6 1245
#define nE6  1319
#define nF6  1397
#define nFS6 1480
#define nG6  1568
#define nGS6 1661
#define nA6  1760
#define nAS6 1865
#define nB6  1976
#define nC7  2093
#define nCS7 2217
#define nD7  2349
#define nDS7 2489
#define nE7  2637
#define nF7  2794
#define nFS7 2960
#define nG7  3136
#define nGS7 3322
#define nA7  3520
#define nAS7 3729
#define nB7  3951
#define nC8  4186
#define nCS8 4435
#define nD8  4699
#define nDS8 4978
#define rest 0


//earphone variable
int songBpm[]={104,168,119,120};
#define earpin 5

const PROGMEM int song0[]={0,4,
  //twinkle twinkle little star
  nC4,4, nC4,4, nG4,4, nG4,4, nA4,4, nA4,4, nG4,2,  nF4,4, nF4,4, nE4,4, nE4,4, nD4,4, nD4,4, nC4,2,
  nG4,4, nG4,4, nF4,4, nF4,4, nE4,4, nE4,4, nD4,2,  nG4,4, nG4,4, nF4,4, nF4,4, nE4,4, nE4,4, nD4,2,
  nC4,4, nC4,4, nG4,4, nG4,4, nA4,4, nA4,4, nG4,2,  nF4,4, nF4,4, nE4,4, nE4,4, nD4,4, nD4,4, nC4,2,
0,4};

const PROGMEM int song1[] = {0,4,
  // Super Mario Bros theme
  nE5,8, nE5,8, rest,8, nE5,8, rest,8, nC5,8, nE5,8, //1
  nG5,4, rest,4, nG4,8, rest,4,
  nC5,-4, nG4,8, rest,4, nE4,-4, // 3
  nA4,4, nB4,4, nAS4,8, nA4,4,
  nG4,-8, nE5,-8, nG5,-8, nA5,4, nF5,8, nG5,8,
  rest,8, nE5,4,nC5,8, nD5,8, nB4,-4,
  nC5,-4, nG4,8, rest,4, nE4,-4, // repeats from 3
  nA4,4, nB4,4, nAS4,8, nA4,4,
  nG4,-8, nE5,-8, nG5,-8, nA5,4, nF5,8, nG5,8,
  rest,8, nE5,4,nC5,8, nD5,8, nB4,-4,

  rest,4, nG5,8, nFS5,8, nF5,8, nDS5,4, nE5,8,//7
  rest,8, nGS4,8, nA4,8, nC4,8, rest,8, nA4,8, nC5,8, nD5,8,
  rest,4, nDS5,4, rest,8, nD5,-4,
  nC5,2, rest,2,

  rest,4, nG5,8, nFS5,8, nF5,8, nDS5,4, nE5,8,//repeats from 7
  rest,8, nGS4,8, nA4,8, nC4,8, rest,8, nA4,8, nC5,8, nD5,8,
  rest,4, nDS5,4, rest,8, nD5,-4,
  nC5,2, rest,2,

  nC5,8, nC5,4, nC5,8, rest,8, nC5,8, nD5,4,//11
  nE5,8, nC5,4, nA4,8, nG4,2,

  nC5,8, nC5,4, nC5,8, rest,8, nC5,8, nD5,8, nE5,8,//13
  rest,1,
  nC5,8, nC5,4, nC5,8, rest,8, nC5,8, nD5,4,
  nE5,8, nC5,4, nA4,8, nG4,2,
  nE5,8, nE5,8, rest,8, nE5,8, rest,8, nC5,8, nE5,4,
  nG5,4, rest,4, nG4,4, rest,4,
  nC5,-4, nG4,8, rest,4, nE4,-4, // 19
 
  nA4,4, nB4,4, nAS4,8, nA4,4,
  nG4,-8, nE5,-8, nG5,-8, nA5,4, nF5,8, nG5,8,
  rest,8, nE5,4, nC5,8, nD5,8, nB4,-4,

  nC5,-4, nG4,8, rest,4, nE4,-4, // repeats from 19
  nA4,4, nB4,4, nAS4,8, nA4,4,
  nG4,-8, nE5,-8, nG5,-8, nA5,4, nF5,8, nG5,8,
  rest,8, nE5,4, nC5,8, nD5,8, nB4,-4,

  nE5,8, nC5,4, nG4,8, rest,4, nGS4,4,//23
  nA4,8, nF5,4, nF5,8, nA4,2,
  nD5,-8, nA5,-8, nA5,-8, nA5,-8, nG5,-8, nF5,-8,
 
  nE5,8, nC5,4, nA4,8, nG4,2, //26
  nE5,8, nC5,4, nG4,8, rest,4, nGS4,4,
  nA4,8, nF5,4, nF5,8, nA4,2,
  nB4,8, nF5,4, nF5,8, nF5,-8, nE5,-8, nD5,-8,
  nC5,8, nE4,4, nE4,8, nC4,2,

  nE5,8, nC5,4, nG4,8, rest,4, nGS4,4,//repeats from 23
  nA4,8, nF5,4, nF5,8, nA4,2,
  nD5,-8, nA5,-8, nA5,-8, nA5,-8, nG5,-8, nF5,-8,
 
  nE5,8, nC5,4, nA4,8, nG4,2, //26
  nE5,8, nC5,4, nG4,8, rest,4, nGS4,4,
  nA4,8, nF5,4, nF5,8, nA4,2,
  nB4,8, nF5,4, nF5,8, nF5,-8, nE5,-8, nD5,-8,
  nC5,8, nE4,4, nE4,8, nC4,2,
  nC5,8, nC5,4, nC5,8, rest,8, nC5,8, nD5,8, nE5,8,
  rest,1,

  nC5,8, nC5,4, nC5,8, rest,8, nC5,8, nD5,4, //33
  nE5,8, nC5,4, nA4,8, nG4,2,
  nE5,8, nE5,8, rest,8, nE5,8, rest,8, nC5,8, nE5,4,
  nG5,4, rest,4, nG4,4, rest,4,
  nE5,8, nC5,4, nG4,8, rest,4, nGS4,4,
  nA4,8, nF5,4, nF5,8, nA4,2,
  nD5,-8, nA5,-8, nA5,-8, nA5,-8, nG5,-8, nF5,-8,
 
  nE5,8, nC5,4, nA4,8, nG4,2, //40
  nE5,8, nC5,4, nG4,8, rest,4, nGS4,4,
  nA4,8, nF5,4, nF5,8, nA4,2,
  nB4,8, nF5,4, nF5,8, nF5,-8, nE5,-8, nD5,-8,
  nC5,8, nE4,4, nE4,8, nC4,2,
 
  //game over sound
  nC5,-4, nG4,-4, nE4,4, //45
  nA4,-8, nB4,-8, nA4,-8, nGS4,-8, nAS4,-8, nGS4,-8,
  nG4,8, nD4,8, nE4,-2,  
0,4};

const PROGMEM int song2[]{0,4,
  // FIFTY FIFTY — Cupid Twin Ver.
  nFS4,-4, nE4,-4, nA4,2,                          
  rest,8, nE4,8, nD4,4, nA3,4,                                
  nE4,-4, nD4,8, nCS4,8, nD4,4, nFS4,2,                  
  nD4,8, nCS4,4, nB3,4,
 
  //bait 1
  rest,-4, nB3,8, nG4,8, nFS4,8, nE4,8, nCS4,4,            
  nA3,4, nCS4,4, nE4,4, nFS4,2,                      
  nA3,8, nFS4,8, nE4,8, nD4,8, nCS4,4,                  
  nA3,4, nB3,4, nA3,8, nG3,8, nG3,2,
         
  nB3,8, nG4,8, nFS4,8, nE4,8, nCS4,4,              
  nA3,4, nCS4,8, nCS4,8, nA4,4, nFS4,2,                    
  rest,8, nFS4,16, nE4,16, nD4,8, nFS4,-4,          
  nD4,8, nFS4,8, nD4,8, nFS4,8, nFS4,8, nFS4,8, nG4,8,

  //reff
  nA4,8, nFS4,8, nFS4,4, nA4,8, nFS4,8, nFS4,8, nG4,8,  
  nA4,8, nA4,8, nG4,8, nG4,8, nFS4,8, nFS4,8, nFS4,8, nB4,8,    
  nA4,8, nFS4,8, nFS4,4, nA4,8, nFS4,8, nFS4,8, nG4,8,    
  nA4,8, nA4,8, nFS4,8, nFS4,8, nE4,2,

  nFS4,6, nE4,6, nA4,6, nFS4,4, nE4,4,                
  nE4,-4, nA3,8, nB3,8, nD4,8, nE4,8, nFS4,8,                  
  nFS4,-4, nE4,-4, nFS4,4,                              
  rest,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,
 
  nB4,4, nFS4,2, rest,4,                            
  rest,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,    
  nB4,4, nFS4,4, nE4,4, rest,4,                        
  rest,2, nFS4,8, nE4,8, nD4,8, nCS4,8,
 
  nB3,4, nD4,4, nE4,4, nFS4,8, nA4,4,                        
  nA4,8, nFS4,8, nE4,8, nE4,8, nA3,8, rest,8, nCS5,-4,        
  nD5,8, nA4,-4, nB4,8, nFS4,2,                      
  rest,8, rest,2,
 
  //bait 2 (sounds weird)
  rest,-4, nB3,8, nG4,8, nFS4,8, nE4,8, nCS4,4,            
  nA3,4, nCS4,4, nE4,4, nFS4,2,                      
  nA3,8, nFS4,8, nE4,8, nD4,8, nCS4,4,                  
  nD4,8, nCS4,4, nB3,4,

  nE4,12, nFS4,12, nD4,12, nE4,12, nFS4,12, nD4,12, nFS4,4, nFS5,8, nA3,8,
  nE4,12, nFS4,12, nD4,12, nE4,12, nFS4,12, nD4,12, nE4,8, nA3,4, nA3,8,
  nE4,12, nFS4,12, nD4,12, nE4,12, nFS4,12, nD4,12, nFS4,8, nA4,8, nFS4,8, nE4,8,
  nFS4,8, nD4,4, nA4,4, nFS4,8, nFS4,8, nG4,8,

  //reff
  nA4,8, nFS4,8, nFS4,4, nA4,8, nFS4,8, nFS4,8, nG4,8,  
  nA4,8, nA4,8, nG4,8, nG4,8, nFS4,8, nFS4,8, nFS4,8, nB4,8,    
  nA4,8, nFS4,8, nFS4,4, nA4,8, nFS4,8, nFS4,8, nG4,8,    
  nA4,8, nA4,8, nFS4,8, nFS4,8, nE4,2,

  nFS4,6, nE4,6, nA4,6, nFS4,4, nE4,4,                
  nE4,-4, nA3,8, nB3,8, nD4,8, nE4,8, nFS4,8,                  
  nFS4,-4, nE4,-4, nFS4,4,                              
  rest,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,
 
  nB4,4, nFS4,2, rest,4,                            
  rest,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,    
  nB4,4, nFS4,4, nE4,4, rest,4,                        
  rest,2, nFS4,8, nE4,8, nD4,8, nCS4,8,
 
  nB3,4, nD4,4, nE4,4, nFS4,8, nA4,4,                        
  nA4,8, nFS4,8, nE4,8, nE4,8, nA3,8, rest,8, nCS5,-4,        
  nD5,8, nA4,-4, nB4,8, nFS4,2,                      
  rest,8, rest,2,

  //bridge? (sounds weird)
  nD5,2, rest,8, nFS5,4, nE5,4,
  nD5,8, rest,-2,
  nFS5,4, nFS5,4, nE5,4, nFS5,8, nA5,-4,
  nFS5,8, nE5,4, nD5,4, nB4,2,

  rest,8, rest,2,
  nE5,2, rest,-4, nCS5,-4,
  nD5,8, nA4,-4, nB4,8, nFS4,4,
  nFS4,4, nFS4,2, rest,8,

  //bait 3
  nFS4,-4, nE4,-4, nA4,2,                          
  rest,8, nFS4,8, nE4,8, nA3,8, nA3,4,
  nE4,-4, nD4,8, nCS4,8, nD4,4, nE4,2,
  nD4,8, nCS4,8, nB3,8, nB3,4,

  nFS4,-4, nE4,-4, nA4,2,                          
  rest,8, nFS4,8, nE4,4, nA3,8, nD4,2,
  nFS4,8, nE4,8, nA3,4, nE4,2,
  nD4,2, rest,8,

  //reff
  rest,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,    
  nB4,4, nFS4,-4, nB4,4, nFS4,4,        
  nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,                
  nB4,4, nFS4,4, nE4,4, nFS4,8, nB4,-4,                      
 
  nFS4,8, nE4,8, nFS4,8, nE4,8, nD4,8, nCS4,8,
  nB3,4, nD4,4, nE4,4, nFS4,8, nA4,4,                        
  nA4,8, nFS4,8, nE4,8, nE4,8, nA3,8, rest,8, nCS5,-4,        
  nD5,8, nA4,-4, nB4,8, nFS4,4,                      
 
  //reff repetition
  nA4,8, nFS4,8, nA4,8, nFS4,8, nA4,8, nFS4,8, nA4,8,
  nB4,4, nFS4,-4, nB4,4, nFS4,4,        
  nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8, nA4,8,                
  nB4,4, nFS4,4, nE4,4, nFS4,8, nB4,-4,                      
 
  nFS4,8, nE4,8, nFS4,8, nE4,8, nD4,8, nCS4,8,
  nB3,4, nD4,4, nE4,4, nFS4,8, nA4,4,                        
  nA4,8, nFS4,8, nE4,8, nE4,8, nA3,8, rest,8, nCS5,-4,        
  nD5,8, nA4,-4, nB4,8, nFS4,4,            

  nFS4,4, nFS4,2, rest,8,
0,4};

int songLength[]={sizeof(song0)/sizeof(int)/2, sizeof(song1)/sizeof(int)/2, sizeof(song2)/sizeof(int)/2, sizeof(alarm)/sizeof(int)/2};
const int *song=song2;
int choosed=2;
const int* chooseSong(int choosed){
    if(choosed==0){
        return song0;
    } else if(choosed==1){
        return song1;
    } else{
        return song2;
    }
}


//other variable
int x=0;
int x0=0;
int y=0;
int y0=0;
unsigned long dtick;
unsigned long dtickAVG=60000/bpm;
unsigned long tRef=0;
unsigned long t0=0;
int tick=0;
float az;
bool lastTickCheck=false;
unsigned long duration;
int dCount;
bool stopRun=false;


//mpu variable
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

//INTERRUPT DETECTION ROUTINE
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

// INITIAL SETUP
void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    //begin serial
    //Serial.begin(115200);

    // initialize device
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);
    // load and configure the DMP
    devStatus = mpu.dmpInitialize();
    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);
        // enable Arduino interrupt detection
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        dmpReady = true;
        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);

    //earphone output
    pinMode(earpin,OUTPUT);

    //initialise random
    randomSeed(analogRead(0));
}

// MAIN PROGRAM LOOP
void loop() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    // read a packet from FIFO
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packe
        // display initial world-frame acceleration, adjusted to remove gravity
        // and rotated based on known orientation from quaternion
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetAccel(&aa, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
        mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
       
        az=2.*9.8*float(aaWorld.z)/32767.;//output vertical acceleration
        // Serial.print(aThreshold);
        // Serial.print("  ");
        // Serial.print(tick%2);
        // Serial.print("  ");
        // Serial.println(az);
       
        if(az>aThreshold){ //if vertical acceleration is higher than the threshold
          if(!lastTickCheck){ //if sebelumnya vertical acceleration less than threshold
            dCount++;
            if(dCount>=dThreshold){
              tick++; //jml langkah
              if(!stopRun){
                dtick=millis()-t0;
              }
              t0=millis();
              lastTickCheck=true;

              // blink LED to indicate activity
              blinkState = !blinkState;
              digitalWrite(LED_PIN, blinkState);
            }
          }
        } else{
          lastTickCheck=false;
          dCount=0;
        }
    }
    delay(dt);//for ease processing


    if((tick>3 && (millis()-t0)<dStopRun)){ //earphone output
    dtickAVG=(9*dtickAVG+dtick)/10; //AVG over 10
    }
    if(tick<=3 || (tick>3 && (millis-t0)<dStopRun)){
      stopRun=false;
      if((int)pgm_read_word_near(&song[2*x0+1])>0){
        duration=dtickAVG*4/pgm_read_word_near(&song[2*x0+1]);
      } else{
        duration=dtickAVG*6 / abs((int)pgm_read_word_near(&song[2*x0+1]));
      }
      x=(x0+(millis()-tRef)/duration);
      if(x>=songLength[choosed]){
        x-=songLength[choosed];
        choosed=random(songCount);
        song=chooseSong(choosed);
      }
      if(100*(millis()-tRef)/duration < 95 && pgm_read_word_near(&song[2*x])!=rest){
        tone(earpin,pgm_read_word_near(&song[2*x]));
      } else{
        noTone(earpin);
      }
      if(x!=x0){
          tRef=millis();
          x0=x;
      }
      y0=0;
    } else{//kalau berhenti, nyalain alarm
      stopRun=true;
      if((int)pgm_read_word_near(&alarm[2*y0+1])>0){
        duration=(60000/bpm)*4/pgm_read_word_near(&alarm[2*y0+1]);
      } else{
        duration=(60000/bpm)*6 / abs((int)pgm_read_word_near(&alarm[2*y0+1]));
      }
      y=y0+(millis()-tRef)/duration;
      if(y>=songLength[chooseAlarm]){
        x-=songLength[choosedAlarm];
      }
      if(100*(millis()-tRef)/duration < 95 && pgm_read_word_near(&alarm[2*y])!=rest){
        tone(earpin,pgm_read_word_near(&alarm[2*y]));
      } else{
        noTone(earpin);
      }
      if(y!=y0){
          tRef=millis();
          y0=y;
      }
    }
}
