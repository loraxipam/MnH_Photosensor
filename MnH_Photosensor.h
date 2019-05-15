/*************************************************** 
  This is a Moles & Halitosis library.   Soli Deo gloria.
  Control your: PHOTOSENSOR
  License: MIT
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
  * and associated documentation files (the "Software"), to deal in the Software without
  * restriction, including without limitation the rights to use, copy, modify, merge, publish,
  * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
  * Software is furnished to do so, subject to the following conditions: The above copyright notice
  * and this permission notice shall be included in all copies or substantial portions of the
  * Software.  
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
  * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  ****************************************************/

#ifndef _MnH_PHOTOSENSOR_H
#define _MnH_PHOTOSENSOR_H

#include <Arduino.h>

#define SMOOTHERSIZE 4
/**
    The basic 10 bit photosensor

    This has some smoothing to the readings to eliminate spikes.
    If you want to measure "brightness" rather than "darkness", use the inverted constructor.

    Your typical cheapo CdS LDR will have a dark resistance on the order of megohms, kilohms in
    room brightness and down to a hundred ohms in direct sun.

    With a pullup resistor, your sensor (@) will be inversely proportional to incident light flux.
    ---- GND --- LDR --- @ --- 10K OHM --- Vcc ---

 */
class MnH_Photosensor {
 public:
  MnH_Photosensor(byte analogPin);                 /// A sensor on pin X
  MnH_Photosensor(byte analogPin, bool inverted);  /// A sensor on pin X but invert reporting

  float  readSensor();                             /// read and report the current [avg] value
  int readRawSensor();                             /// read and report the current raw value

  int maxRaw();                                    /// report the max raw value seen
  int minRaw();                                    /// report the min raw value seen

  float currentAvg();                              /// report the current average. Do not read.
  float currentMean();                             /// report the current geo mean. Do not read.

 private:
  MnH_Photosensor();                               /// A blank sensor should never be used
  byte         _analogPin;                         /// The pin to read
  bool         _inverted = false;                  /// to use inverted values
  int _runningRawMax = 0;                          /// Highest raw read value seen
  int _runningRawMin = 1023;                       /// Lowest  raw read value seen
  float _runningAvg;                               /// The current "value"
  float avgValues[SMOOTHERSIZE];
  float calculateCurrentAvg();                     /// Just calculate avgs from the current array
  float calculateCurrentAvg(int sensorReading);    ///Pushes in a new reading and returns array avg

};


#endif
