// Tamim Faruk, October 1, 2016

#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;

/* template variable used to read in and
ignore lines/parts of lines
that are unnecessary */
template <class charT, class traits>
inline
basic_istream<charT,traits>&
ignoreLine (basic_istream<charT,traits>& stream) {
    // skip until end-of-line
    stream.ignore(numeric_limits<int>::max(),stream.widen('\n'));
    // return stream for concatenation
    return stream;
}

int main() {
  /* For the purposes of the main task, I thought the Z
  accelerometer and Y accelerometer were the best indicators
  for when the heel struck */
  double accelZ = 0;
  double accelY = 0;

  /* Arrays used for a moving average to interpret data*/
  double zArray[10]= {0};
  double yArray[10] = {0};

  int numSteps = 0;
  int lines = 0;

  // After analyzing the data, I thought these were appropiate thresholds for reference
  const double Z_THRESHHOLD = 10000;
  const double Y_THRESHHOLD = -5000;

  double gyroY;

  // Placeholders to handle reading unnecessary values
  string a, b;
  int c, d;
  int time = 0;

  /* For simplification, I read all the values from a text file rather than the
  excel files. Just quicker and simpler. And to simplify the graphing process
  I exported to multiple files as well */

  /* Initialize the file streams. Add 2 to the end of
  file names to switch between datasets */
  ifstream sensorValues("./DataSet1/sensorValues.txt");

  // Writes all the plot values here for line graph
  ofstream plotValues("./DataSet1/plotValues.txt");

  //Writes the heel strike coordinates here for Z and Y acceloremeters
  ofstream heelStrikes("./DataSet1/heelStrikes.txt");

  //Writes the foot flat coordinates here for the Y-Gyroscope
  ofstream footflat("./DataSet1/footflat.txt");

  //Writes the midswing coordinates
  ofstream midSwing("./DataSet1/midSwing.txt");

  //Writes the toeUp coordinates
  ofstream toeUp("./DataSet1/toeUp.txt");

  //Writes the midStance coordinates
  ofstream midStance("./DataSet1/midStance.txt");
  /* Used to give the algorithm some buffer time.
  IF a heel strike is found, this will skip the immediate
  consecutive values where there the rate of change is
  mainted, and the heel strike is still going*/
  bool flag = false;
  bool flag2 = false;

  /* The threshold for the length of a heelstrike I used
  was the value 10 of ten lines. Found via trial and error.
  Also resets the array values during this period */

  while (sensorValues.good()) {
    if (flag == true) {
      for (int i = 0; i < 10; i++) {
        yArray[i] = 0;
        zArray[i] = 0;
        sensorValues >> a >> b >> time>> c >> accelY >> accelZ >> c >> gyroY >> ignoreLine;
        if (gyroY >= 0 && gyroY <= 1000) {
          footflat << lines << " " << gyroY << endl;
      }
        plotValues << gyroY << " " << accelY << " " << accelZ << endl;
        lines++;
    }
    flag = false;
    } else { // flag =/= true, need to find next heel strike
      sensorValues >> a >> b >> time>> c >> accelY >> accelZ >> c >> gyroY >> ignoreLine;
      zArray[lines%10] = accelZ;
      yArray[lines%10] = accelY;
      double zAvg = 0;
      double yAvg = 0;
      /* Considered a weighted average.
      The thresholds were concluded through
      eye-balled data analysis and trial/error*/
      for (int i = 0; i < 10; i++) {
        if (zArray[i] >= 20000)
          zArray[i] *= 1.25;
          zAvg += zArray[i];
          if (yArray[i] <= -9000)
            yArray[i] *= 1.5;
          yAvg += yArray[i];
      }
      if (yAvg/10 < Y_THRESHHOLD && zAvg/10 > Z_THRESHHOLD)  {
        cout << "Y_AVG IS " << yAvg/10 << " Heel Strike at " << time  << " line " << lines << endl;
        numSteps++;
        heelStrikes << lines << " " << yAvg/10 << " " << zAvg/10 << endl;
        flag = true;
        flag2 = true;
      }
    else {
      //Flag2 is used to buffer when the next toe up phase will be
      if (zAvg/10 > Z_THRESHHOLD && flag2==true) {
        toeUp << lines << " " << zAvg/10 << endl;
        flag2=false;
      } else if (accelZ >= 0 && gyroY >= -1000 && gyroY <=1000) {
        midStance << lines << " " << gyroY << endl;
        footflat << lines << " " << gyroY << endl;
      } else if (gyroY >= -1000 && gyroY <=1000) {
          footflat << lines << " " << gyroY << endl;
      } else if (gyroY <= -8000) {
        midSwing << lines << " " << gyroY << endl;
      }
      plotValues << gyroY << " " << accelY << " " << accelZ << endl;
    }
    lines++;
  }
  }
  cout << "Number of lines read is: " << lines << endl;
  cout << "Number of steps is: " << numSteps;
}
