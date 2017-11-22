// coxa - 27mm
// femore - 82mm
// tibia - 122mm
// z-offset - 112mm

#include <SoftwareSerial.h>
float rootX = 0;
float rootY = 0;
float rootZ = 0;
float groundX = 0; 
float groundY = 131;
float groundZ = -112;
float coxa = 27;
float femore = 84;
float tibia = 122;

SoftwareSerial usc(10,11);
void setup() {
  Serial.begin(9600);
  usc.begin(115200);

 float zero = 1500;
 float error = -200;
 float servoMin = 900;
 float servoMax = 1900;
 float maxAngle = 90; //cox maximum angle range - means from -45 -90 to 90 45;
 float gama = 0;
 float beta = 0;
 float alpha = 0;
 float coxaPos = 0; 
 float femorePos = 0;
 float tibiaPos = 0;
 float L, L1;
 float zoffset = 0;
 
 for(int i = -131; i <= 131; i +=3 ) {
    groundX = i;
    Serial.print("x: ");
    Serial.print(i);

    Serial.print("  x/y = ");
    Serial.print(groundY / groundX);
    
    gama = degrees(atan2(groundX, groundY));
    Serial.print("  gama: ");
    Serial.print(gama);

// protection
//    if (gama < 0 and gama <= -45) {
//      gama = gama + 90;
//    } else if (gama > 0 and gama >= 45) {
//      gama = gama - 90;
//    } else {
//      gama = 0;
//    }
    coxaPos = (zero + error) + (gama/maxAngle * (servoMax - servoMin));

    Serial.print("  coxa: ");
    Serial.print(coxaPos);
    usc.print("#20P");
    usc.println(int(coxaPos));

    zoffset = abs(rootZ - groundZ);
    L1 = sqrt(sq(groundY) + sq(groundX) );
    L = sqrt( sq(zoffset) + sq(L1 - coxa));

    alpha =  degrees(acos(zoffset/L) + acos( (sq(tibia) - sq(femore) - sq(L)) / (-2 * femore * L) ));
    beta = degrees(acos( (sq(L) - sq(tibia) - sq(femore)) / ( -2 * tibia * femore) ));

    femorePos = zero - (((90-alpha)/ maxAngle) * (900));
    tibiaPos = zero - (((beta-90)/ maxAngle) * (900));

    Serial.print(" ||  L1: ");
    Serial.print(L1);
    Serial.print("  L: ");
    Serial.print(L);
    Serial.print("  alpha: ");
    Serial.print(alpha);
    Serial.print("  femore: ");
    Serial.print(femorePos);
    
    Serial.print("  beta: ");
    Serial.print(beta);
    Serial.print("  tibia: ");
    Serial.println(tibiaPos);

    usc.print("#21P");
    usc.print(femorePos);
    usc.print("#22P");
    usc.println(tibiaPos);
    
    if (i == -131) delay(5000);
    
    
    
    delay(100);
 }
}
void loop() {
}

