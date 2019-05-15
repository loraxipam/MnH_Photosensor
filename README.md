# _Moles and Halitosis_ Photosensor library

  This library provides an easy-to-use interface for an analog photosensor. It gives a simple interface for collecting the sensor readings and smoothing the data. You can read the value directly or report back the average or geometric mean of the latest N readings. There are functions to return the minimum and maximum values that the sensor has reported which are helpful for determining the photosensor's response curve.

# Functions

  The following functions are provided by this library. Most are used simply for retrieving and reporting the sensor values.

## Constructors

  ```c++
  MnH_Photosensor(byte analogPin)
  MnH_Photosensor(byte analogPin, bool inverted)
  ```

## Sensor functions
  ```c++
  float  readSensor()        // read the sensor and return the running average
  int readRawSensor()        // read and return the sensor, calculate running average
  int        maxRaw()        // maximum senor value seen. See notes.
  int        minRaw()        // minimum senor value seen. See notes.
  float  currentAvg()        // current average sensor values
  float currentMean()        // current geometric mean sensor values
  ```

# Discussion

  Two constructors provide a simple way to create photosensor objects on a given analog pin. An "inverter" exists in case your wiring or your device require an inversion of the reported light dependent resistor (LDR) values.

  The object provides a smoothing array which can be resized by adjusting the SMOOTHERSIZE directive. If you read the sensor using the `readSensor()` function, then the array will be updated and you'll get the smoothed average back from the function. In contrast, if you read the sensor using the `readRawSensor()` function, the behavior is the same in terms of updating the smoothing array, but the return value is the actual sensor value, not the array value. Notice, too, that the results returned from `maxRaw()` and `minRaw()` are impacted by this. If you use only `readSensor()` then the min/max functions will return only the min/max as seen by the average.
