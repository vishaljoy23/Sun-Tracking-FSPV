#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohTopLimit = 160;
int servohBottomLimit = 20;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs

int solar = A5;
int ldrtopl = A3; //top left LDR green
int ldrtopr = A2; //top right LDR yellow
int ldrbotl = A1; // bottom left LDR blue
int ldrbotr = A0; // bottom right LDR orange

 void setup () 
 {
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(0);
  Serial.begin(9600); 
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  int solout = analogRead(solar);

  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohTopLimit)
    {
    servoh = servohTopLimit;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohBottomLimit)
     {
     servoh = servohBottomLimit;
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);

  Serial.println(solout);


}