#define LIGHT_SENSOR_LEFT_1 A3
#define LIGHT_SENSOR_LEFT_2 A4

#define LIGHT_SENSOR_RIGHT_1 A5
#define LIGHT_SENSOR_RIGHT_2 A6

#define SDA 12
#define SCL 13

#define DIST_SENSOR_LEFT A2
#define DIST_SENSOR_RIGHT A1

#define DIST_CONST 58
#define NUM_MEASURE 5
#define LONG_DIST 50.0
#define NORMAL_DIST 25.0
#define COMMON_SPEED (uint8_t) 300
#define LOW_SPEED (uint8_t) 150
#define SPIN_COUNT_360 (uint8_t) 10

#define DELAY 5

#define MOTOR_AIN1 1     //AIN1
#define MOTOR_AIN2 2     //AIN2

#define MOTOR_BIN1 4     //BIN1
#define MOTOR_BIN2 5     //BIN2

#define MOTOR_CIN1 7     //CIN1
#define MOTOR_CIN2 8     //CIN2

#define MOTOR_DIN1 10    //DIN1
#define MOTOR_DIN2 11    //DIN2

#define MOTOR_PWMA 2     //Left-front motor speed control PWMA
#define MOTOR_PWMB 6     //Right-front motor speed control PWMB
#define MOTOR_PWMC 9     //Left-back motor speed control PWMC     
#define MOTOR_PWMD 12    //Right-back motor speed control PWMD

uint8_t LIGHT_DATA[4];
float distance = 0;
uint8_t spin_count = 0;
bool spin_switch = 0;

void check_light();
float distance_measure();
float check_distance();
void run(uint8_t speed);
void brake();
void forward_left(uint8_t speed);
void forward_right(uint8_t speed);
void back_left(uint8_t speed);
void back_right(uint8_t speed);
void spin_left(uint8_t speed);
void spin_right(uint8_t speed);
void back(uint8_t speed);
void go(uint8_t speed);

void setup() {
  pinMode(MOTOR_AIN1, OUTPUT);
  pinMode(MOTOR_BIN1, OUTPUT);
  pinMode(MOTOR_CIN1, OUTPUT);
  pinMode(MOTOR_DIN1, OUTPUT);
  pinMode(MOTOR_AIN2, OUTPUT);
  pinMode(MOTOR_BIN2, OUTPUT);
  pinMode(MOTOR_CIN2, OUTPUT);
  pinMode(MOTOR_DIN2, OUTPUT);

  pinMode (LIGHT_SENSOR_LEFT_1, INPUT);
  pinMode (LIGHT_SENSOR_LEFT_2, INPUT);
  pinMode (LIGHT_SENSOR_RIGHT_1, INPUT);
  pinMode (LIGHT_SENSOR_RIGHT_2, INPUT);

  pinMode (SDA, INPUT);
  pinMode (SCL, OUTPUT);

  pinMode (DIST_SENSOR_LEFT, INPUT);
  pinMode (DIST_SENSOR_RIGHT, INPUT);

  digitalWrite (LIGHT_SENSOR_LEFT_1, HIGH);
  digitalWrite (LIGHT_SENSOR_LEFT_2, HIGH);
  digitalWrite (LIGHT_SENSOR_RIGHT_1, HIGH);

  digitalWrite (DIST_SENSOR_LEFT, HIGH);
  digitalWrite (DIST_SENSOR_RIGHT, HIGH);
}

void loop() {
  distance = check_distance();
  check_light();
  
  if (distance > LONG_DIST)
    go(COMMON_SPEED);
  else if (distance > NORMAL_DIST)
    go(LOW_SPEED);
  else {
    
    back(LOW_SPEED);
    if (spin_count < SPIN_COUNT_360) {
      
      if (spin_switch)
        spin_right(LOW_SPEED);
      else
        spin_left(LOW_SPEED);
      
      brake();
      spin_count++;
      
    } else {
      
      spin_switch = !spin_switch;
      spin_count = 0;
      
    }
    
  }
    
}

//Choose the way
void go(uint8_t speed) {
  if ((LIGHT_DATA[0] == LOW || LIGHT_DATA[1] == LOW) &&  LIGHT_DATA[3] == LOW)
    forward_right(speed);
  else if (LIGHT_DATA[0] == LOW && (LIGHT_DATA[2] == LOW ||  LIGHT_DATA[3] == LOW))
    forward_left(speed);
  else if ( LIGHT_DATA[0] == LOW)
    forward_left(speed);
  else if ( LIGHT_DATA[3] == LOW )
    forward_right(speed);
  else if ( LIGHT_DATA[1] == LOW && LIGHT_DATA[2] == HIGH)
    spin_left(speed);
  else if (LIGHT_DATA[1] == HIGH && LIGHT_DATA[2] == LOW)
    spin_right(speed);
  else if (LIGHT_DATA[1] == LOW && LIGHT_DATA[2] == LOW)
    run(speed);
  else {
    
    back(LOW_SPEED);
    if (spin_count < SPIN_COUNT_360) {
      
      if (spin_switch)
        spin_right(LOW_SPEED);
      else
        spin_left(LOW_SPEED);
      
      brake();
      spin_count++;
      
    } else {
      
      spin_switch = !spin_switch;
      spin_count = 0;
      
    }
  }
}

//Check the way
void check_light() {
  LIGHT_DATA[0] = digitalRead (LIGHT_SENSOR_LEFT_1);
  LIGHT_DATA[1] = digitalRead (LIGHT_SENSOR_LEFT_2);
  LIGHT_DATA[2] = digitalRead (LIGHT_SENSOR_RIGHT_1);
  LIGHT_DATA[3] = digitalRead (LIGHT_SENSOR_RIGHT_2);
}

//Geting almost raw distance to obstacle
float distance_measure() {
   float distance;
   
   digitalWrite (SCL, LOW);
   delay(2);
   digitalWrite (SCL, HIGH);
   delay(10);
   digitalWrite (SCL, LOW);

   distance = pulseIn (SDA, HIGH);
   distance /= DIST_CONST;
   
   return distance;
}

//Getting info og distance to obstacle
float check_distance() {
  float distance = 0;
  for (uint8_t i = 0; i < NUM_MEASURE; i++)
    distance += distance_measure();
  
  distance /= NUM_MEASURE;
  return distance;
}

//Move forward
void run(uint8_t speed) {

  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);

  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);

  digitalWrite(MOTOR_CIN1, HIGH);
  digitalWrite(MOTOR_CIN2, LOW);

  digitalWrite(MOTOR_DIN1, HIGH);
  digitalWrite(MOTOR_DIN2, LOW);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//Brake
void brake() {
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, LOW);
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, LOW);
  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, LOW);
  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, LOW);

}

//Block left wheels, enable right => moving forward-left
void forward_left(uint8_t speed) {
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 0); 
  
  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, LOW);
  analogWrite(MOTOR_PWMC, 0);

  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);
  digitalWrite(MOTOR_DIN1, HIGH);
  digitalWrite(MOTOR_DIN2, LOW);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }


}

//Block right wheels, enable left => moving forward-right
void forward_right(uint8_t speed) {
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, LOW);
  analogWrite(MOTOR_PWMB, 0);

  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, LOW);
  analogWrite(MOTOR_PWMD, 0);

  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);
  digitalWrite(MOTOR_CIN1, HIGH);
  digitalWrite(MOTOR_CIN2, LOW);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    delay(DELAY);
  }
}

//Block left wheels, reverse right => moving back-left
void back_left(uint8_t speed) {
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, LOW);
  analogWrite(MOTOR_PWMA, 0);

  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, LOW);
  analogWrite(MOTOR_PWMC, 0);

  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);
  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, HIGH);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//Block right wheels, enable left => moving back-right
void back_right(uint8_t speed) {
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, LOW);
  analogWrite(MOTOR_PWMB, 0);

  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, LOW);
  analogWrite(MOTOR_PWMD, 0);

  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);
  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, HIGH);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    delay(DELAY);
  }
}

//Rotating left, without moving forward
void spin_left(uint8_t speed) {
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);

  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, HIGH);

  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);

  digitalWrite(MOTOR_CIN1, HIGH);
  digitalWrite(MOTOR_CIN2, LOW);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//Rotating right, without moving forward
void spin_right(uint8_t speed) {
  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);

  digitalWrite(MOTOR_DIN1, HIGH);
  digitalWrite(MOTOR_DIN2, LOW);

  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);

  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, HIGH);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//moving back
void back(uint8_t speed) {
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);

  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);

  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, HIGH);

  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, HIGH);

  for (uint8_t i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}
