#include "..\include\Filter.h"
using namespace std;

Filter::Filter()
{
    ZAccel = {0};
    YAccel = {0};
    YGyroscope = {0};
    YAvg = 0;
    ZAvg = 0;
    gYroAvg = 0;
    gyroSlope = 0;
    size = 10;
}

//Filter::~Filter()
//{
//
//}

void Filter::acquire(int yAccelValue, int zAccelValue, int yGyroValue, int& index)
{
    YAccel[index%size] = yAccelValue;
    ZAccel[index%size] = zAccelValue;
    YGyroscope[index%size] = yGyroValue;
    index++;
    average();
}

void Filter::average()
{
    for (int i = 0; i < size; i++) {
        if (ZAccel[i] >= 20000)
            ZAccel[i] *= 1.25;
        if (YAccel[i] <= -9000)
            YAccel[i] *= 1.5;
        ZAvg += ZAccel[i];
        YAvg += YAccel[i];
        gYroAvg += YGyroscope[i];
    }
    ZAvg /= size;
    YAvg /= size;
    gYroAvg /= size;
}

void Filter::deltaSlope()
{
    for (int i = 0; i < size; i++) {
        gyroSlope += YGyroscope[size] = 0;
    }
}

void Filter::clearAccelBuffer()
{
    for (int i = 0; i < 10; i++) {
        ZAccel[i] = 0;
        YAccel[i] = 0;
    }
}

void Filter::clearGyroBuffer()
{
    for (int i = 0; i < 10; i++) {
        YGyroscope[i] = 0;
    }
}

/*
Filter::clearContents()
{
  clearGyroBuffer();
  clearAccelBuffer();
}
*/

void Filter::returnValues(double& accelY, double& accelZ,
        double& gyroAvgY, double& gyroSlopeY)      {
  accelY = YAvg;
  accelZ = ZAvg;
  gyroAvgY = gYroAvg;
  gyroSlopeY = gyroSlope;
}
