  // QUALIFICATION


// Colour sensor ------------------
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

int frequency = 0;

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
int maxWall_f = 20;
int maxWall_r = 20;
int maxWall_l = 20;


void setup() {
  // colour sensor setup -----------------

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


  // delay(1000);
  // turnright();
  // delay(turnTimeDelay);
  // stop_motor();

  // delay(1000);
  // turnleft();
  // delay(turnTimeDelay);
  // stop_motor();

  // delay(1000);
  // speed_control(255,255);
  // delay(1000);
  // stop_motor();


  // digitalWrite(LED,HIGH);

  // delay(1000);
  // speed_control(100,-100);
  // delay(1000);
  // stop_motor();


  // digitalWrite(LED,LOW);
  
}

// Wall following algorithm states
enum WallFollowingState {
  AWAY_FROM_WALL,
  HEADED_TOWARDS_WALL,
  FOLLOWING_WALL,
  AT_CORNER
};

WallFollowingState wallState = AWAY_FROM_WALL;


void loop() {

 readAndPrintFrequency(LOW, LOW, "R");
 readAndPrintFrequency(HIGH, HIGH, "G");
 readAndPrintFrequency(LOW, HIGH, "B");
 Serial.println();

  distance_f = read_distance(0);
  distance_l = read_distance(1);
  distance_r = read_distance(2);

// add logic to stop when see red colour 
// FOLLOW RIGHT WALL
  // Determine the wall following state based on sensor readings
  if (distance_f > maxWall_f && distance_r > maxWall_r) {
    wallState = AWAY_FROM_WALL;
  } else if (distance_f <= maxWall_f && distance_r > maxWall_r) {
    wallState = HEADED_TOWARDS_WALL;
  } else if (distance_f >= maxWall_f && distance_r <= maxWall_r) {
    wallState = FOLLOWING_WALL;
  }
  else{
    wallState = AT_CORNER;
  }

  // Wall following behavior based on state
  switch (wallState) {
    case AWAY_FROM_WALL:
      // Come back to wall, turn right
      Serial.println("turn right");
      turnright();
      break;
    case HEADED_TOWARDS_WALL:
      // Turn hard left to get back parallel with the wall
      turnleft();
            Serial.println("turn left");
      break;
    case FOLLOWING_WALL:
      // Drive forward
      straight();
      Serial.println("go straight");
      break;
    case AT_CORNER:
      // Turn hard left
      turnleft();
      Serial.println("TURN HARD LEFT AT CORNER");
      break;
  }

//   // FOLLOW LEFT WALL
//   if (distance_f > maxWall_f && distance_l > maxWall_l) {
//     wallState = AWAY_FROM_WALL;
// } else if (distance_f <= maxWall_f && distance_l > maxWall_l) {
//     wallState = HEADED_TOWARDS_WALL;
// } else if (distance_f >= maxWall_f && distance_l <= maxWall_l) {
//     wallState = FOLLOWING_WALL;
// } else {
//     wallState = AT_CORNER;
// }

// // Wall following behavior based on state
// switch (wallState) {
//     case AWAY_FROM_WALL:
//         // Come back to wall, turn left
//         Serial.println("Turn left to get back to the wall");
//         turnleft();
//         break;
//     case HEADED_TOWARDS_WALL:
//         // Turn hard right to get back parallel with the wall
//         Serial.println("Turn hard right to align with the wall");
//         turnright();
//         break;
//     case FOLLOWING_WALL:
//         // Drive forward
//         Serial.println("Go straight while following the wall");
//         straight();
//         break;
//     case AT_CORNER:
//         // Turn hard right
//         Serial.println("Turn hard right at a corner");
//         turnright();
//         break;
// }

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

void readAndPrintFrequency(int s2State, int s3State, const char *colorName) {


  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);

 

  frequency = pulseIn(sensorOut, LOW);

 

  Serial.print(colorName);
  Serial.print("= ");
  Serial.print(frequency);
  Serial.print("  ");


  delay(100);
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

 

 

void speed_control(int left_speed, int right_speed)
{

 

  if (left_speed > 0)
  {
    digitalWrite(motor_l1, LOW);
    analogWrite(motor_l2,left_speed);
  }
  else
  {
    digitalWrite(motor_l2, LOW);
    analogWrite(motor_l1,left_speed);
  }

  if (right_speed > 0)
  {
    digitalWrite(motor_r1,LOW);
    analogWrite(motor_r2,right_speed);
  }
  else
  {
    digitalWrite(motor_r2,LOW);
    analogWrite(motor_r1,right_speed);
  }
}