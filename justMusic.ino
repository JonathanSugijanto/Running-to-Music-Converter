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

//blink variable
#define LED_PIN 13
bool blinkState=false;
int dt=1000;

//earphone variable
int bpm=120;
int songBpm[]={104,168,119};
#define earpin 5
#define songCount 3 //kalau jumlahnya diubh, ubh jg fungsi chooseSong(int choosed) dan array songLength[]

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

int songLength[]={sizeof(song0)/sizeof(int)/2, sizeof(song1)/sizeof(int)/2, sizeof(song2)/sizeof(int)/2};
const int *song=song2;
int choosed=2;

//general variable
int x;
int x0=0;
unsigned long dtick;
unsigned long dtickAVG=60000/bpm;
unsigned long tRef=0;
unsigned long t0=0;

//other variable
int tick=1;

//new variable
unsigned long duration;


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  //earphone output
  pinMode(earpin,OUTPUT);
  
  //baru
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  dtick=dtickAVG;
  
  if(tick>0){ //earphone output
    dtickAVG=(9*dtickAVG+dtick)/10; //AVG over 10
  }
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
  
//  blinkState = !blinkState;
//  digitalWrite(LED_PIN, blinkState);
//  //Serial.println(blinkState);
//  delay(dt);
}

const int* chooseSong(int choosed){
    if(choosed==0){
        return song0;
    } else if(choosed==1){
        return song1;
    } else{
        return song2;
    }
}
