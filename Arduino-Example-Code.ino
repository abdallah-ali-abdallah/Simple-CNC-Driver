// Arduino Example Code to operate 1 Stepper Motor connected to B0 - B1 - B2 - B3 
// declaration of PINS that connected the wire to motor

int B0 = 13;
int B1 = 12;
int B2 = 11;
int B3 = 10;

//this is the time to wait in every single step, which control the speed 
int delayTime = 100;

//set the pin for OUTPUT
void setup() 
{
  pinMode(B0, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(B2, OUTPUT);
}

void loop() 
{
  forward(13);
  delay(500);
  backward(13);
}

void forward(int steps)
{
  for(int i=0;i<steps;i++)
  {
// in every phase 2 wires is up and 2 is down
    digitalWrite(B0, LOW);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, LOW);
    delay(delayTime);
 
    digitalWrite(B0, LOW);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
    digitalWrite(B3, HIGH);
    delay(delayTime);
 
    digitalWrite(B0, HIGH);
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
    digitalWrite(B3, HIGH);
    delay(delayTime);
 
    digitalWrite(B0, HIGH);
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, LOW);
    delay(delayTime);}
}

void backward (int steps)
{
  for(int i=0;i<steps;i++)
  {
    digitalWrite(B0, HIGH);
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, LOW);
    delay(delayTime);
 
    digitalWrite(B0, HIGH);
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
    digitalWrite(B3, HIGH);
    delay(delayTime);
 
     digitalWrite(B0, LOW);
     digitalWrite(B1, HIGH);
     digitalWrite(B2, LOW);
     digitalWrite(B3, HIGH);
     delay(delayTime);
 
     digitalWrite(B0, LOW);
     digitalWrite(B1, HIGH);
     digitalWrite(B2, HIGH);
     digitalWrite(B3, LOW);
     delay(delayTime);
  }

}