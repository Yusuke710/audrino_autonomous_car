// COMBINED CODE 

// Colour sensor ------------------
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

int frequency = 0;

// Ultrasonic sensor ------------------
const int trigPin_f = 12;
const int echoPin_f = 13;

const int trigPin_l = 10;
const int echoPin_l = 11;

const int trigPin_r = 8;
const int echoPin_r = 9;

long duration;

// ultrasonic sensors distances
int distance_f;
int distance_r;
int distance_l;

// Motor 
int ena1 = 7;
int input1 = 14;
int input2 = 15;

int ena2 = 16;
int input3 = 17;
int input4 = 18;

// Detecting colour range (Margin range)
double SD_r = 1.51;
double SD_g = 1.60;
double SD_b = 1.98;

double mean_r = 27.02;
double mean_g = 67.01;
double mean_b = 63.89;

double coefficient_r = 20;
double coefficient_g = 20;
double coefficient_b = 20;

// Initalising variables for readAndPrintFrequency
int r;
int b;
int g;

// Calibrate here ----------------
int turn_time_delay = 5; // rotation time
int maxWall = 8;  // wall sensor max distance 
int adj_distance = 3; // adjusting distance range margin 
int adj_time_delay_R = 2; // time to reposition bot to centre right
int adj_time_delay_L= 2; // time to reposition bot to centre left


void setup() {
  // colour sensor setup ------------------
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
// Ultrasonic sensor setup ------------------
  pinMode(trigPin_f, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_f, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_l, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_l, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_r, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_r, INPUT); // Sets the echoPin as an Input

// Motor setup ---------------
  // pinMode(input1, OUTPUT); 
  // pinMode(input2, OUTPUT);
  // pinMode(input3, OUTPUT);
  // pinMode(input4, OUTPUT);
  // pinMode(ena1, OUTPUT);
  // pinMode(ena2, OUTPUT);

  Serial.begin(9600); 
}

 
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

// Reading sensor distance --------------------
int read_distance(int direction){
  // Front Sensor 
  if (direction == 0){
    digitalWrite(trigPin_f, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_f, HIGH);
    delayMicroseconds(10);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    digitalWrite(trigPin_f, LOW);
    duration = pulseIn(echoPin_f, HIGH);

    // Calculating the distance
    int distance = duration * 0.034 / 2; 

    return distance;
  } 

  // Left Sensor
  else if (direction == 1){
    digitalWrite(trigPin_l, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_l, HIGH);
    delayMicroseconds(10);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    digitalWrite(trigPin_l, LOW);
    duration = pulseIn(echoPin_l, HIGH);

    // Calculating the distance
    int distance = duration * 0.034 / 2; 

    return distance; 
  } 

  // Right Sensor
  else if (direction == 2){
    digitalWrite(trigPin_r, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_r, HIGH);
    delayMicroseconds(10);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    digitalWrite(trigPin_r, LOW);
    duration = pulseIn(echoPin_r, HIGH);

    // Calculating the distance
    int distance = duration * 0.034 / 2; 

    return distance; 
  }
}

// Motor Directions ------------------

void goLeft(int time_delay){
  digitalWrite(ena1, HIGH);
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);

  digitalWrite(ena2, HIGH);
  digitalWrite(input3, LOW);
  digitalWrite(input4, HIGH);
  
  // need to have half turn only (90')
  time_delay = turn_time_delay;
  delay(time_delay);
  digitalWrite(ena1, HIGH);
  digitalWrite(ena2, HIGH);
}

void goRight(int time_delay){
  digitalWrite(ena1, HIGH);
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);

  digitalWrite(ena2, HIGH);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, LOW);

  // need to have half turn only (90')
  time_delay = turn_time_delay;
  delay(turn_time_delay);
  digitalWrite(ena1, HIGH);
  digitalWrite(ena2, HIGH);
}

void goStraight(){
  digitalWrite(ena1, HIGH);
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);

  digitalWrite(ena2, HIGH);
  digitalWrite(input3, HIGH);
  digitalWrite(input4, LOW);
}

void stop(){
  digitalWrite(ena1, LOW);
  digitalWrite(ena2, LOW);
}

// Readjusting the position for direction
void readjust_position(int adjust_pos){
  // adjust_pos 0 = left
  // adjust_post 1 = right 

  if (adjust_pos == 1){
        // adjust left
    if(read_distance(2) > read_distance(1) - adj_distance || read_distance(2) > read_distance(1) + adj_distance){
      goLeft(adj_time_delay_L);
      Serial.println("ADJUSTING ROTATION - LEFT");
    };
  }
  else if (adjust_pos == 2){
    // adjust right
    if(read_distance(1) > read_distance(2) - adj_distance || read_distance(1) > read_distance(2) + adj_distance){
      goRight(adj_time_delay_R);
      Serial.println("ADJUSTING ROTATION - RIGHT");
    };
  }

}


void loop() {

  
  // reads RGB colour
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
    (b < (mean_b + SD_b * coefficient_b))) {
      Serial.println("Detected - Red");
  }

  // go straight 
    if (read_distance(0) > maxWall){
      goStraight();
      Serial.println("STRAIGHT");      
      readjust_position(1);
      readjust_position(2);
    };
    // turn left
     if (read_distance(0) < maxWall && read_distance(2) < maxWall){
      goLeft(turn_time_delay);
      Serial.println("TURNING LEFT");
      readjust_position(1);
      readjust_position(2);
    };
    // turn right
     if (read_distance(0) < maxWall && read_distance(2) > maxWall){
      goRight(turn_time_delay);
      Serial.println("TURING RIGHT");
      readjust_position(1);
      readjust_position(2);
    };

    // KEY:
  // read_distance = 0  --> go straight
  // read_distance = 1 --> go left 
  // read_distance = 2  --> go right

  // readjust_position = 1 --> adjusting left
  // readjust_position = 2 --> adjust right
  

};

 








