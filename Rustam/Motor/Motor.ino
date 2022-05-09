//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ЖДЁМ КОГДА ДЕНИС СДЕЛАЕТ СХЕМУ С ДАТЧИКАМИ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Define pin
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

void setup()
{
  //Initialize the motor PIN
  pinMode(MOTOR_AIN1, OUTPUT);
  pinMode(MOTOR_BIN1, OUTPUT);
  pinMode(MOTOR_CIN1, OUTPUT);
  pinMode(MOTOR_DIN1, OUTPUT);
  pinMode(MOTOR_AIN2, OUTPUT);
  pinMode(MOTOR_BIN2, OUTPUT);
  pinMode(MOTOR_CIN2, OUTPUT);
  pinMode(MOTOR_DIN2, OUTPUT);

}


//Move forward
void run(int speed)
{

  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);

  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);

  digitalWrite(MOTOR_CIN1, HIGH);
  digitalWrite(MOTOR_CIN2, LOW);

  digitalWrite(MOTOR_DIN1, HIGH);
  digitalWrite(MOTOR_DIN2, LOW);

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//Brake
void brake()
{
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
void forward_left(int speed)
{
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

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }


}

//Block right wheels, enable left => moving forward-right
void forward_right(int speed)
{
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

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    delay(DELAY);
  }
}

//Block left wheels, reverse right => moving back-left
void back_left(int speed)
{
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

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//Block right wheels, enable left => moving back-right
void back_right(int speed)
{
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

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    delay(DELAY);
  }
}

//Rotating left, without moving forward
void spin_left(int speed)
{
  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);

  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, HIGH);

  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_AIN2, LOW);

  digitalWrite(MOTOR_CIN1, HIGH);
  digitalWrite(MOTOR_CIN2, LOW);

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//Rotating right, without moving forward
void spin_right(int speed)
{
  digitalWrite(MOTOR_BIN1, HIGH);
  digitalWrite(MOTOR_BIN2, LOW);

  digitalWrite(MOTOR_DIN1, HIGH);
  digitalWrite(MOTOR_DIN2, LOW);

  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);

  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, HIGH);

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}

//moving back
void back(int speed)
{
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_AIN2, HIGH);

  digitalWrite(MOTOR_BIN1, LOW);
  digitalWrite(MOTOR_BIN2, HIGH);

  digitalWrite(MOTOR_CIN1, LOW);
  digitalWrite(MOTOR_CIN2, HIGH);

  digitalWrite(MOTOR_DIN1, LOW);
  digitalWrite(MOTOR_DIN2, HIGH);

  for (int i = 0; i < 50; i++)
  {
    analogWrite(MOTOR_PWMA, i * speed / 50);
    analogWrite(MOTOR_PWMB, i * speed / 50);
    analogWrite(MOTOR_PWMC, i * speed / 50);
    analogWrite(MOTOR_PWMD, i * speed / 50);
    delay(DELAY);
  }
}



void loop()
{
  //code
}
