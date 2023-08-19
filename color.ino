#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600);
}

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

void loop() {
  readAndPrintFrequency(LOW, LOW, "R");
  readAndPrintFrequency(HIGH, HIGH, "G");
  readAndPrintFrequency(LOW, HIGH, "B");
  Serial.println();
}
