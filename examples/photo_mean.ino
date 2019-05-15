/* Moles n Halitosis photosensor example. This shows the running geometric mean */

#include <MnH_Photosensor.h>

MnH_Photosensor sensor(A0);

void setup(){
  Serial.begin(115200);
}

void loop(){

  Serial.print(sensor.readRawSensor());
  Serial.print(" ");

  Serial.print(sensor.currentAvg());
  Serial.print(" ");

  Serial.println(sensor.currentMean());

  delay(3000);
}
