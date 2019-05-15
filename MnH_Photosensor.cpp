/***************************************************
  This is a Moles & Halitosis library
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

#include <Arduino.h>
#include <MnH_Photosensor.h>

/** Assuming ten bit analog reads **/
#define _INV(VAL) (_inverted ? (1023 - (VAL)) : (VAL))

MnH_Photosensor::MnH_Photosensor(){
}

/** A photosensor on an analog pin. */
MnH_Photosensor::MnH_Photosensor(byte analogPin){
    pinMode(analogPin, INPUT);
    _analogPin = analogPin;
}

/** The analog pin to read the resistor differential and if the sensor is inverted.
*   An inverted sensor has the sensor on the positive side of the resistor.
*/
MnH_Photosensor::MnH_Photosensor(byte analogPin, bool inverted){
    pinMode(analogPin, INPUT);
    _analogPin = analogPin;

    _inverted = inverted;
}

/**
 * Read the sensor, update the smoothed array and return the *avg* value
 * @return current average based on a new sensor reading
 */
float MnH_Photosensor::readSensor(){
    int sensorValue = analogRead(_analogPin);
    sensorValue = _INV(sensorValue);
    _runningAvg = calculateCurrentAvg(sensorValue);
    _runningRawMax = max(_runningRawMax,(int)(_runningAvg));
    _runningRawMin = min(_runningRawMin,(int)(_runningAvg));
    return _runningAvg;     /// <-returns the running average
}

/**
 * This reads the sensor and gives *that* value. It also updates the array
 *
 * If you want to keep the array clean, just read the pin yourself.
 * @return the current sensor value, not the array average
 */
int MnH_Photosensor::readRawSensor(){
    int sensorValue = analogRead(_analogPin);
    sensorValue = _INV(sensorValue);
    _runningAvg = calculateCurrentAvg(sensorValue);
    _runningRawMax = max(_runningRawMax,sensorValue);
    _runningRawMin = min(_runningRawMin,sensorValue);
    return sensorValue;     /// <-returns the raw reading
}

/**
 * What is the maximum value that the sensor has seen?
 * @return max sensor value seen so far
 */
int MnH_Photosensor::maxRaw(){
    return _runningRawMax;
}

/**
 * What is the minimum value that the sensor has seen?
 * @return min sensor value seen so far
 */
int MnH_Photosensor::minRaw(){
    return _runningRawMin;
}

/**
 * What is the current average sensor reading?
 * @return avg sensor variable value
 */
float MnH_Photosensor::currentAvg(){
    return _runningAvg;
}

/**
 * Just return the geometric mean of the array
 * @return geometric mean of sensor array values
 */
float MnH_Photosensor::currentMean(){
    float f = 0.0;
    int arrayIndex = 0;
    for (arrayIndex = 0; arrayIndex < SMOOTHERSIZE; arrayIndex++){
        if (avgValues[arrayIndex] < 1) break;
        f += log(avgValues[arrayIndex]);
    }
    f = exp(f/(float)arrayIndex);
    return f;
}

/**
 * Calculate and return the average of the array
 * @return average of the sensor array values
 */
float MnH_Photosensor::calculateCurrentAvg(){
    float v = 0.0;
    int arrayIndex = 0;
    for (arrayIndex = 0; arrayIndex < SMOOTHERSIZE; arrayIndex++){
        if (avgValues[arrayIndex] < 1) break;
        v += (float)avgValues[arrayIndex];
    }
    v /= (float)arrayIndex;
    return v;
}

/**
 * Push the new reading into the array and calculate the new average
 * @return avg of the new sensor array values
 */
float MnH_Photosensor::calculateCurrentAvg(int sensorReading){
    static unsigned int avgValuesCurrentIndex;
    avgValues[avgValuesCurrentIndex++ % SMOOTHERSIZE] = sensorReading;

    return calculateCurrentAvg();
}
