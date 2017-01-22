#ifndef FILTER_H
#define FILTER_H

class Filter
{
    public:
        Filter();
        void acquire(int yAccelValue, int zAccelValue, int yGyroValue, int* index);
        void average();
        void deltaSlope();
        void returnValues(double * accelY, double * accelZ,
                double * gyroAvgY, double * gyroSlopeY);
        void clearContents();
        
		int size;
        double ZAvg;
        double YAvg;
        double gYroAvg;
        double gyroSlope;

    private:
        double* ZAccel = new double[size];
        double* YAccel = new double[size];
        double* YGyroscope = new double[size];
};
#endif // FILTER_H
