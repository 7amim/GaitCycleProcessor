#ifndef FILTER_H
#define FILTER_H


class Filter
{
    public:
        Filter(int bufferSize);
        acquire();
        average();
        deltaSlope();
        int size;

        bool risingSlope = false;

        double ZAvg;
        double YAvg;
        double gYroAvg;
        double gyroSlope;

    private:
        double ZAccel[size];
        double YAccel[size];
        double YGyroscope[size];

#endif // FILTER_H
