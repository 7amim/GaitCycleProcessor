#include "src\Filter.cpp"
#include "src\StateMachine.cpp"

#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <limits>

using namespace std;

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
  Filter movingAverage;
  StateMachine classifier;
  ifstream sensorValues("../DataSet1/sensorValues.txt");
  if (!sensorValues) {
  	cout << "Could not open dataset";
  } else {
  	cout << "File opened correctly" << endl;
  }

  // Defining placeholders to read inputs
  string a, b;
  int c, d;
  double accelZ = 0;
  double accelY = 0;
  double slope = 0;
  double gyroY;
  int time;
  bool semaphore;
  int index = 0;
  int numSteps = 0;

  while (sensorValues.good()) {
    sensorValues >> a >> b >> time >> c >> accelY >> accelZ >> c >> gyroY >> ignoreLine;
	index = movingAverage.acquire(accelY, accelZ, gyroY, index);
	movingAverage.average();
    movingAverage.returnValues(accelY, accelZ, gyroY, slope);
    // cout << accelY << endl;
    classifier.classify(accelY, accelZ, gyroY, slope);
    if (classifier.previousState.phase != classifier.currState.phase) {
    	if (classifier.toString() == "Heel Strike")
			numSteps++;
        cout << classifier.toString();
		cout << " at line " << index << endl;
    } // else, do nothing because the current state has not changed yet
  }
  cout << "Number of lines read is: " << index << endl;
  cout << "Number of steps is: " << numSteps;
}
