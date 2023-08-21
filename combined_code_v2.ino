// COMBINED CODE

 

// Colour sensor ------------------
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

 
int frequency = 0;


double SD_r = 1.51;

double SD_g = 1.60;

double SD_b = 1.98;

 

double mean_r = 28 ;//27.02;

double mean_g = 55; //67.01;

double mean_b = 42; //63.89;

 

double coefficient_r = 5;
double coefficient_g = 5;
double coefficient_b = 5;

 

// Initalising variables for readAndPrintFrequency

int r;

int b;

int g;
 

// ultrasonic sensor ------------------
const int trigPin_f = 12;
const int echoPin_f = 13;

const int trigPin_l = 10;
const int echoPin_l = 11;

const int trigPin_r = 8;
const int echoPin_r = 9;
 

long duration;
int distance_f;
int distance_r;
int distance_l;

// MOTOR

const int motor_l1 = A2;
const int motor_l2 = A3;
const int motor_r1 = A4;
const int motor_r2 = A5;


const int LED = 7;



// Calibrate here ----------------
int turnTimeDelay = 500;
int maxWall = 8;

 

void setup() {

  // colour sensor setup ------------------

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

 
  pinMode(motor_l1, OUTPUT);
  pinMode(motor_l2, OUTPUT);
  pinMode(motor_r1, OUTPUT);
  pinMode(motor_r2, OUTPUT);

  pinMode(LED,OUTPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);


  digitalWrite(LED,LOW); 

// Ultrasonic sensor setup------------------

  pinMode(trigPin_f, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_f, INPUT); // Sets the echoPin as an Input
 
  pinMode(trigPin_l, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_l, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_r, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_r, INPUT); // Sets the echoPin as an Input
        

  Serial.begin(9600); // Starts the serial communication  



  digitalWrite(LED,LOW);

  delay(1000);
  
  while (true)
  {
    distance_f = read_distance(0);
    distance_l = read_distance(1);
    distance_r = read_distance(2);


    r = readAndPrintFrequency(LOW, LOW, "R");
  
    g = readAndPrintFrequency(HIGH, HIGH, "G");
  
    b = readAndPrintFrequency(LOW, HIGH, "B");
  
    Serial.println();
  
   
  
    // check if red is detected
  
    if ((r > (mean_r - SD_r * coefficient_r)) &&
  
      (r < (mean_r + SD_r * coefficient_r)) &&
  
      (g > (mean_g - SD_g * coefficient_g)) &&
  
      (g < (mean_g + SD_g * coefficient_g)) &&
  
      (b > (mean_b - SD_b * coefficient_b)) &&
  
      (b < (mean_b + SD_b * coefficient_b))) 
   {
  
       digitalWrite(LED,HIGH);
  
   }
   else
   {
      digitalWrite(LED,LOW);
   }


    if (distance_f < 18)
    {
      if (distance_l< 8 and distance_r > 20)
      {
        reverse();
        delay(200);
        stop_motor();
        delay(100);
        turnright();
        delay(500);
        stop_motor();
        straight();
        delay(800);
        stop_motor();
      }
      else
      {
        reverse();
        delay(200);
        stop_motor();
        delay(100);
        turnleft();
        delay(500);
        stop_motor();
        straight();
        delay(800);
        stop_motor();
      }
    }
    else if (distance_l > 55)
    {
      straight();
      delay(5);
      turnleft();
      delay(450);
      stop_motor();
      straight();
      delay(800);
      stop_motor();
    }
    else if (distance_r > 55)
    {
      straight();
      delay(5);  
      turnright();
      delay(450);
      stop_motor();
      straight();
      delay(800);
      stop_motor();
    }
    else if (distance_l< 12)
    {
      turnright();
      delay(40);
      straight();
      delay(80);
      stop_motor();
    }
    else if (distance_r< 12)
    {
      turnleft();
      delay(40);
      straight();
      delay(80);
      stop_motor();
      
    }
    else
    {
      straight();
      delay(500);
    }
  }
}

 


int read_distance(int direction){

  if (direction == 0)
  {
    digitalWrite(trigPin_f, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_f, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_f, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin_f, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2; 
    return distance;
  } 
  else if (direction == 1)
  {
    digitalWrite(trigPin_l, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_l, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_l, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin_l, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2; 
    return distance; 
  } 
  else if (direction == 2)
  {
    digitalWrite(trigPin_r, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_r, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_r, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin_r, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2; 
    return distance; 
  }

}



// colour sensor ------------------

// Colour sensor ------------------

int readAndPrintFrequency(int s2State, int s3State, const char *colorName) {

  digitalWrite(S2, s2State);

  digitalWrite(S3, s3State);

 

  frequency = pulseIn(sensorOut, LOW);

 

  Serial.print(colorName);

  Serial.print("= ");

  Serial.print(frequency);

  Serial.print("  ");

  delay(100);

 

  return frequency;

}

void turnright()
{
  digitalWrite(motor_r1,HIGH);
  digitalWrite(motor_r2,LOW);
  
  digitalWrite(motor_l1,LOW);
  digitalWrite(motor_l2,HIGH);
}

void turnleft()
{
  digitalWrite(motor_r1,LOW);
  digitalWrite(motor_r2,HIGH);
  
  digitalWrite(motor_l1,HIGH);
  digitalWrite(motor_l2,LOW);
}



void straight()
{
  digitalWrite(motor_r1,LOW);
  digitalWrite(motor_r2,HIGH);
  
  digitalWrite(motor_l1,LOW);
  digitalWrite(motor_l2,HIGH);
}

void reverse()
{
  digitalWrite(motor_r1,HIGH);
  digitalWrite(motor_r2,LOW);
  
  digitalWrite(motor_l1,HIGH);
  digitalWrite(motor_l2,LOW);
}

void stop_motor()
{
  digitalWrite(motor_r1,LOW);
  digitalWrite(motor_r2,LOW);
  
  digitalWrite(motor_l1,LOW);
  digitalWrite(motor_l2,LOW);
}
