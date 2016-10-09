#include "Filter.h"
using namespace std;

Filter::Filter()
{
    ZAccel[size] = {0};
    YAccel[size] = {0};
    YGyroscope[size] = {0};
    YAvg = 0;
    ZAvg = 0;
    gYroAvg = 0;
    gyroSlope = 0;
    size = 10;
}

Filter::~Filter()
{

}

Filter::acquire(int yAccelValue, int zAccelValue, int yGyroValue, int bufferSize)
{
    for (int i = 0; i < bufferSize; i++) {
        YAccel[bufferSize%size] = yAccelValue;
        ZAccel[bufferSize%size] = zAccelValue;
        YGyroscope[bufferSize%size] = yGyroValue;
    }
    average();
}

Filter::average()
{
    for (int i = 0; i < size; i++) {
        if (ZAccel[i] >= 20000)
            ZAccel[i] *= 1.25;
        if (YAccel[i] <= -9000)
            YAccel[i] *= 1.5;
        ZAvg += ZAccel[i];
        YAvg += YAccel[i];
        gYroAvg += Ygyroscope[i];
    }
    ZAvg /= size;
    YAvg /= size;
    gYroAvg /= size;
}

Filter::deltaSlope()
{
    for (int i = 0; i < size; i++) {
        gyroSlope += YGyroscope[size] = 0;
    }
}

Filter::clearAccelBuffer()
{
    for (int i = 0; i < 10; i++) {
        ZAccel[i] = 0;
        YAccel[i] = 0;
    }
}

Filter::clearGyroBuffer()
{
    for (int i = 0; i < 10; i++) {
        YGyroscope[i] = 0;
    }
}

Filter::returnValues(double* accelY, double* accelZ,
        double * gyroAvgY, double * gyroSlopeY)      {

  accelY = YAvg;
  accelZ = ZAvg;
  gyroAvg = gYroAvg;
  gyroSlopeY = gyroSlope;
}
