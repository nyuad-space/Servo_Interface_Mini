#include "config.h"

Servo myServoA;
Servo myServoB;

unsigned long startTime = 0;
unsigned long endTime = 0;

int servoPinA = 9;
int servoPinB = 10;

int pos = 0;
bool armed = false;
bool servoTriggered = false;

void resetServo();
void triggerServo();
void ledBlink(int led, unsigned long delayTime);
void buzzerBeep(unsigned long beepInterval);

void setup()
{
  Serial.begin(9600);
  Serial.println("System initializing...");

  pinMode(pyroSignalA, INPUT);
  pinMode(pyroSignalB, INPUT);
  pinMode(pyroSignalC, INPUT);
  pinMode(pyroSignalD, INPUT);

  pinMode(ledLit, OUTPUT);
  pinMode(ledArmed, OUTPUT);
  pinMode(ledDeployed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  myServoA.attach(servoPinA);
  myServoB.attach(servoPinB);

  myServoA.write(90);
  myServoB.write(90);
  
  delay(20);

  armed = true;
  Serial.println("System armed. Servos set to default positions.");
}

void loop()
{
  int pyroSignalOne = digitalRead(pyroSignalA);
  int pyroSignalTwo = digitalRead(pyroSignalB);
  int pyroSignalThree = digitalRead(pyroSignalC);
  int pyroSignalFour = digitalRead(pyroSignalD);

  Serial.print("Signals -> A: ");
  Serial.print(pyroSignalOne);
  Serial.print(" B: ");
  Serial.print(pyroSignalTwo);
  Serial.print(" C: ");
  Serial.print(pyroSignalThree);
  Serial.print(" D: ");
  Serial.println(pyroSignalFour);

  if (pyroSignalOne == 0 || pyroSignalTwo == 0 || pyroSignalThree == 0 || pyroSignalFour == 0)
  {
    Serial.println("Trigger condition met. Activating servos...");
    triggerServo();
  }

  if (armed)
  {
    ledBlink(ledArmed, 200);
  }
  else
  {
    ledBlink(ledDeployed, 500);
  }
}

void triggerServo()
{
  // for (pos = 0; pos <= 90; pos++)
  // {
  //   myServoA.write(pos);         // A moves 0 → 90
  //   myServoB.write(180 - pos);   // B moves 180 → 90
  //   delay(10);
  // }
  myServoA.write(160);
  myServoB.write(20);

  Serial.println("Servos triggered. System disarmed.");
  armed = false;
}

void resetServo()
{
  // for (pos = 90; pos >= 0; pos--)
  // {
  //   myServoA.write(pos);         // A moves 90 → 0
  //   myServoB.write(180 - pos);   // B moves 90 → 180
  //   delay(20);
  // }

  myServoA.write(2);
  myServoB.write(170);


  Serial.println("Servos reset. System rearmed.");
  armed = true;
}

void ledBlink(int led, unsigned long delayTime)
{
  if (millis() - endTime >= delayTime)
  {
    endTime = millis();
    digitalWrite(led, !digitalRead(led));
  }
}

void buzzerBeep(unsigned long beepInterval)
{
  unsigned long previousMillis = 0;
  bool buzzerState = false;

  pinMode(buzzer, OUTPUT);
  unsigned long currentMillis = millis();

  while (true)
  {
    if (currentMillis - previousMillis >= beepInterval)
    {
      previousMillis = currentMillis;
      buzzerState = !buzzerState;
      analogWrite(buzzer, buzzerState ? 2 : 0);
    }
    currentMillis = millis();
  }
}
