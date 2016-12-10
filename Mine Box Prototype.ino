#include <SharpIR.h>
#include <Servo.h>
//#include <Math.h>

int pos=0;
Servo tilt;
Servo boxopener;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  tilt.attach(7);
  boxopener.attach(9);
}
  
void loop ()
{
  SharpIR sharp(A0, 500, 99, 20150);
  //A0 port
  //250 readings before an average is calculated
  //90 % difference between two readings to be considered valid
  //20150 is the model number
  int tilty=0;
  
  Serial.print("Opening... ");
  for(int angle=0;angle<=90;angle++) {
    boxopener.write(angle);
    if(angle % 9 == 0) {
      tilt.write(tilty);
      tilty++;
    }
    delay(20);
  }
  
  //tilty is at 10
  
  Serial.print("open. (2 sec)\n");
  delay(2000);
  Serial.print("Scanning. (2.5 sec)\n");
  int dis=0;
  for(int j=0;j<4;j++) {
    dis=sharp.distance();
    Serial.print(dis);
    Serial.print(",\tand ");
    double opposite = (cos(0.1745329252) * dis);
    Serial.print(opposite);
    Serial.print(" tall\n");
    delay(500);
  }dis=sharp.distance();Serial.print(dis);Serial.print("\nScan complete. (2 sec)\n");
  delay(2000);

  Serial.print("Adjusting angle... ");
  for(tilty=10;tilty>=-10;tilty--) { //subtracts 20
    tilt.write(tilty);
    delay(70);
  }
  
  //tilty is at -10
  
  Serial.print("done. (2 sec)\n");
  delay(2000);
  Serial.print("Scanning. (2.5 sec)\n");
  dis=0;
  for(int j=0;j<4;j++) {
    dis=sharp.distance();
    Serial.print(dis);
    Serial.print("\tand ");
    double opposite = (cos(0.1745329252) * dis);
    Serial.print(opposite);
    Serial.print(" tall\n");
    delay(500);
  }dis=sharp.distance();Serial.print(dis);Serial.print("\nScan complete. (2 sec)\n");
  delay(2000);

  //tilty is at -10, still
  
  Serial.print("Closing... ");
  for(int angle=90;angle>=0;angle--) {
    boxopener.write(angle);
    if(angle % 9 == 0) { //adds 10
      tilt.write(tilty);
      tilty++;
    }
    delay(20);
  }
  
  //tilty is at 0
  
  Serial.print("closed. (2 sec)\n");
  delay(2000);
  Serial.print("\n\n");
}
