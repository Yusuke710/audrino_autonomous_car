

// Final Round

// LED light ------

const int LED = 7;

int redCounter = 0;

 

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

const int motor_l1 = A2;

const int motor_l2 = A3;

const int motor_r1 = A4;

const int motor_r2 = A5;

 

// Detecting colour range (Margin range)

  

 

// Initalising variables for readAndPrintFrequency

int r;

int b;

int g;

 

// Calibrate here ----------------

int turn_time_delay = 500; // rotation time

// int maxWall = 8;  // wall sensor max distance

int maxWall_f = 20;

int maxWall_r = 20;

int maxWall_l = 20;

 

int adj_distance = 3; // adjusting distance range margin

int adj_time_delay_R = 2; // time to reposition bot to centre right

int adj_time_delay_L= 2; // time to reposition bot to centre left

 

// Wall following algorithm states

enum WallFollowingState {

  AWAY_FROM_WALL,

  HEADED_TOWARDS_WALL,

  FOLLOWING_WALL,

  AT_CORNER

};

 

 

 

WallFollowingState wallState = AWAY_FROM_WALL;

 

 

 

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

  pinMode(motor_l1, OUTPUT);

  pinMode(motor_l2, OUTPUT);

  pinMode(motor_r1, OUTPUT);

  pinMode(motor_r2, OUTPUT);

 

  // LED

  pinMode(LED, OUTPUT);

 

 

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

 

void goLeft(){

  digitalWrite(motor_r1,LOW);

  digitalWrite(motor_r2,HIGH);

 

  digitalWrite(motor_l1,HIGH);

  digitalWrite(motor_l2,LOW);

 

  // need to have half turn only (90')

  delay(turn_time_delay);

  stop_motor();

};

 

void goRight(){

  digitalWrite(motor_r1,HIGH);

  digitalWrite(motor_r2,LOW);

 

  digitalWrite(motor_l1,LOW);

  digitalWrite(motor_l2,HIGH);

 

  // need to have half turn only (90')

  delay(turn_time_delay);

  stop_motor();

};

 

void goStraight(){

  digitalWrite(motor_r1,LOW);

  digitalWrite(motor_r2,HIGH);

 

  digitalWrite(motor_l1,LOW);

  digitalWrite(motor_l2,HIGH);

};

 

void reverse(){

  digitalWrite(motor_r1,HIGH);

  digitalWrite(motor_r2,LOW);

 

  digitalWrite(motor_l1,HIGH);

  digitalWrite(motor_l2,LOW);

};

 

void stop_motor()

{

  digitalWrite(motor_r1,LOW);

  digitalWrite(motor_r2,LOW);

 

  digitalWrite(motor_l1,LOW);

  digitalWrite(motor_l2,LOW);

};

 

// Readjusting the position for direction

// void readjust_position(int adjust_pos){

 

      // KEY:

  // read_distance = 0  -->  straight

  // read_distance = 1 -->  left

  // read_distance = 2  -->  right

 

  // readjust_position = 1 --> adjusting left

  // readjust_position = 2 --> adjust right

 

// if (adjust_pos == 1) {

//     // too much on the right, adjust left

//     if (read_distance(2) > read_distance(1)) {

//         goRight(adj_time_delay_R);

//         printf("ADJUSTING ROTATION - LEFT\n");

//     }

// }

 

// else if (adjust_pos == 2) {

//     // too much on the left, adjust right

//     if (read_distance(1) > read_distance(2)) {

//         goLeft(adj_time_delay_L);

//         printf("ADJUSTING ROTATION - RIGHT\n");

//     }

//   }

// }

 

 

 

void loop() {

 

  // reads RGB colour

  r = readAndPrintFrequency(LOW, LOW, "R");

  g = readAndPrintFrequency(HIGH, HIGH, "G");

  b = readAndPrintFrequency(LOW, HIGH, "B");

//  Serial.print("R: ");
//  Serial.print(r);
//  
//
//
//  Serial.print(",    G: ");
//  Serial.print(g);
//
//
//  Serial.print(",    B: ");
//  Serial.print(b);
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


 
}

 

 
