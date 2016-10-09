#ifndef FILTER_H
#define FILTER_H


class Filter
{
    public:
        Filter(int bufferSize);
        void acquire();
        void average();
        void deltaSlope();
        void returnValues((double * accelY, double * accelZ,
                double * gyroAvgY, double * gyroSlopeY);

        int size;
        double ZAvg;
        double YAvg;
        double gYroAvg;
        double gyroSlope;

    private:
        double ZAccel[size];
        double YAccel[size];
        double YGyroscope[size];


#endif // FILTER_H
