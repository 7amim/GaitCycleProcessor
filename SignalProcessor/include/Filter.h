#ifndef FILTER_H
#define FILTER_H

class Filter
{
    public:
        Filter();
        int acquire(int yAccelValue, int zAccelValue, int yGyroValue, int index);
        void average();
        void deltaSlope();
        void returnValues(double& accelY, double& accelZ,
        double& gyroAvgY, double& gyroSlopeY);
        void clearAccelBuffer();
        void clearGyroBuffer();
        void clearContents();
        
        const int SIZE = 10;
        double ZAvg;
        double YAvg;
        double gYroAvg;
        double gyroSlope;

    private:
        double ZAccel[10] = {0};
        double YAccel[10] = {0};
        double YGyroscope[10] = {0};
};
#endif // FILTER_H
