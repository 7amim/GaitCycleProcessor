#include <iostream>
#include <cmath>

#include 'Filter.h'
#include 'StateMachine.h'

using namespacee std;

template <class charT, class traits>
inline
basic_istream<charT,traits>&
ignoreLine (basic_istream<charT,traits>& stream) {
    // skip until end-of-line
    stream.ignore(numeric_limits<int>::max(),stream.widen('\n'));
    // return stream for concatenation
    return stream;
}

int main () {
  Filter movingAverage = new Filter();
  StateMachine classifier = new StateMachine();
  ifstream sensorValues("./DataSet1/sensorValues.txt");

  string a, b;
  int c, d;
  double accelZ = 0;
  double accelY = 0;
  double slope = 0;
  bool semaphore;
  int index = 0;

  while (sensorValues.good()) {
    sensorValues >> a >> b >> time>> c >> accelY >> accelZ >> c >> gyroY >> ignoreLine;
    movingAverage.acquire(accelY, accelZ, gyroY, index);
    movingAverage.returnValues(accelY, accelZ, gyroY, slope);
    // If a state has already been detected, then this will skip some of the contents
    // until the state is exited
    if (semaphore == true) {
      movingAverage.wipeContents(semaphore); // important: I need a way to reset the semaphore. 
    } else {
      cout << classifier.classify(accelY, accelZ, gyroY, slope, semaphore);
    }
  }
}
