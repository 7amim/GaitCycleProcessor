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

/* Place the sensor reading in this function to clean space
void signalProcess() {

}
*/

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
  int numSteps = 0;

  while (sensorValues.good()) {
    movingAverage.wipeContents(semaphore);
    sensorValues >> a >> b >> time>> c >> accelY >> accelZ >> c >> gyroY >> ignoreLine;
    movingAverage.acquire(accelY, accelZ, gyroY, index);
    movingAverage.returnValues(accelY, accelZ, gyroY, slope);
    classifier.classify(accelY, accelZ, gyroY, slope, semaphore);
    if (classifier.previousState != classifier.currState) {
      classifier.previousState = classifier.currState;
      cout << classifier.currState << " at line " << index << endl;
    } // else, do nothing because the current state has not changed yet
  }
  cout << "Number of lines read is: " << index << endl;
	cout << "Number of steps is: " << numSteps;
}
