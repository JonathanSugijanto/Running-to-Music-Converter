#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//myVariable
MPU6050 mpu;
int dt=10;
float az;
int tick=0;
bool lastTickCheck=false;
float aThreshold=0.25;

//earphone variable
#define earpin 5
int bpm=120; //default bpm
int n1[]={0,33,37,41,44,49,55,62}; //song 1 length 8
int n2[]={0,66,73,82,87,98,110,123}; //song 2 length 8
int n3[]={0,131,147,165,175,196,220,247}; //song 3 length 8
int n4[]={0,262,294,330,349,392,440,494}; //song 4 length 8
int n5[]={0,523,587,659,698,784,880,988};//song 5 length 8
int songMel[]={n4[5],n4[3],n4[3],n4[4],n4[2],n4[2],n4[1],n4[2],n4[3],n4[4],n4[5],n4[5],n4[5],n4[3],n4[2],n4[4],n4[2],n4[2],n4[1],n4[3],n4[5],n4[5],n4[1]};
int song[]={
  n4[1],n4[1],n4[5],n4[5],n4[6],n4[6],n4[5],0,  n4[4],n4[4],n4[3],n4[3],n4[2],n4[2],n4[1],0,
  n4[5],n4[5],n4[4],n4[4],n4[3],n4[3],n4[2],0,  n4[5],n4[5],n4[4],n4[4],n4[3],n4[3],n4[2],0,
  n4[1],n4[1],n4[5],n4[5],n4[6],n4[6],n4[5],0,  n4[4],n4[4],n4[3],n4[3],n4[2],n4[2],n4[1],0
  }; //twinkle twinkle little star
int songLength=sizeof(song)/sizeof(int);

int x;
int x0=0;
unsigned long dtick;
unsigned long dtickAVG=60000/bpm;
unsigned long tRef=0;
unsigned long t0=0;

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

    // initialize serial communication
    //Serial.begin(115200);
    //while (!Serial); // wait for Leonardo enumeration, others continue immediately. Comment this part if Serial is unnecesarry

    // initialize device
    //Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    //Serial.println(F("Testing device connections..."));
    //Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    
    // load and configure the DMP
    //Serial.println(F("Initializing DMP..."));
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
        //Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        //Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        //Serial.println(F(")..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        //Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        //Serial.print(F("DMP Initialization failed (code "));
        //Serial.print(devStatus);
        //Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);

    //earphone output
    pinMode(earpin,OUTPUT);
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
        
        if(az>aThreshold){ //if vertical acceleration is higher than the threshold
          if(!lastTickCheck){ //if sebelumnya vertical acceleration less than threshold
            tick++; //jml langkah
            dtick=millis()-t0;
            t0=millis();
            //Serial.print("Jml langkah ");
            //Serial.println(tick);
          }
          lastTickCheck=true;
        } else{
          lastTickCheck=false;
        }

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
    delay(dt);//for ease processing

    if(tick>0){ //earphone output
        dtickAVG=(9*dtickAVG+dtick)/10; //AVG over 10
        x=(x0+(millis()-tRef)/dtickAVG)%songLength;
        if(100*(millis()-tRef)/dtickAVG < 95 && song[x]!=0){
          tone(earpin,song[x]);
        } else{
          noTone(earpin);
        }
        if(x!=x0){
            tRef=millis();
        }
      x0=x;
    } else{
      tone(earpin,song[0]);
    }
}
