//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ЖДЁМ КОГДА ДЕНИС СДЕЛАЕТ СХЕМУ С ДАТЧИКАМИ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Define pin
int Left_forward = 1;        // AIN1
int Left_back = 2;      // AIN2

int Right_forward = 3;       //BIN1
int Right_back = 4;     // BIN2

int Left_pwm = 5;       //Left motor speed control PWMA
int Right_pwm = 6;      //Right motor speed control PWMB


void setup()
{
  //Initialize the motor PIN
  pinMode(Left_forward, OUTPUT);
  pinMode(Left_back, OUTPUT);
  pinMode(Right_forward, OUTPUT);
  pinMode(Right_back, OUTPUT);
}

//Move forward
void run(int time)
{

  //left motor go
  digitalWrite(Left_forward, HIGH);   
  digitalWrite(Left_back, LOW);  
  analogWrite(Left_pwm, 200);

  //right motor go
  digitalWrite(Right_forward, HIGH);  
  digitalWrite(Right_back, LOW); 
  analogWrite(Right_pwm, 200);

  delay(time * 100);
}

//Brake
void brake(int time)
{
  digitalWrite(Left_forward, LOW);
  digitalWrite(Left_back, LOW);
  digitalWrite(Right_forward, LOW);
  digitalWrite(Right_back, LOW);


  delay(time * 100);
}

//Block left wheels, enable right => moving forward-left
void forward_left(int time)
{
  digitalWrite(Left_forward, LOW);
  digitalWrite(Left_back, LOW);
  analogWrite(Left_pwm, 0);

  digitalWrite(Right_forward, HIGH);
  digitalWrite(Right_back, LOW);
  analogWrite(Right_pwm, 100);


  delay(time * 100);
}

//Block right wheels, enable left => moving forward-right
void forward_right(int time)
{
  digitalWrite(Left_forward, HIGH);   
  digitalWrite(Left_back, LOW);  
  analogWrite(Left_pwm, 100);

  digitalWrite(Right_forward, LOW);   
  digitalWrite(Right_back, LOW); 
  analogWrite(Right_pwm, 0);

  delay(time * 100);
}

//Block left wheels, reverse right => moving back-left
void back_left(int time)
{
  digitalWrite(Left_forward, LOW);
  digitalWrite(Left_back, LOW);
  analogWrite(Left_pwm, 0);

  digitalWrite(Right_forward, LOW);
  digitalWrite(Right_back, HIGH);
  analogWrite(Right_pwm, 100);


  delay(time * 100);
}

//Block right wheels, enable left => moving back-right
void back_right(int time)
{
  digitalWrite(Left_forward, LOW);
  digitalWrite(Left_back, HIGH);
  analogWrite(Left_pwm, 100);

  digitalWrite(Right_forward, LOW);
  digitalWrite(Right_back, LOW);
  analogWrite(Right_pwm, 0);

  delay(time * 100);
}

//Rotating left, without moving forward
void spin_left(int time)
{
  //left motor back
  digitalWrite(Left_forward, LOW);     
  digitalWrite(Left_back, HIGH); 
  analogWrite(Left_pwm, 200);

  //right motor go
  digitalWrite(Right_forward, HIGH); 
  digitalWrite(Right_back, LOW); 
  analogWrite(Right_pwm, 200);

  delay(time * 100);
}

//Rotating right, without moving forward
void spin_right(int time)
{
  //left motor go
  digitalWrite(Left_forward, HIGH);    
  digitalWrite(Left_back, LOW);   
  analogWrite(Left_pwm, 200);

  //right motor back
  digitalWrite(Right_forward, LOW);   
  digitalWrite(Right_back, HIGH); 
  analogWrite(Right_pwm, 200);


  delay(time * 100);
}

//moving back
void back(int time)
{
  //left motor back
  digitalWrite(Left_forward, LOW);     
  digitalWrite(Left_back, HIGH);  
  analogWrite(Left_pwm, 200);

  //right motor back
  digitalWrite(Right_forward, LOW);   
  digitalWrite(Right_back, HIGH); 
  analogWrite(Right_pwm, 200);


  delay(time * 100);
}


void loop()
{
  //code
}
