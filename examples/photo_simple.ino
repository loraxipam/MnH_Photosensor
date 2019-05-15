/* Moles n Halitosis photosensor example. This shows the min/max functions.
   Notice that using the raw reader will show higher min/max than using the
   readSensor, which reports the min/max of the average */

#include <MnH_Photosensor.h>

MnH_Photosensor sensor(A0);

void setup(){
  Serial.begin(115200);
}

void loop(){

  Serial.print(sensor.readSensor());
  Serial.print(" ");

  Serial.print(sensor.minRaw());
  Serial.print(" ");

  Serial.println(sensor.maxRaw());

  delay(3000);
}
