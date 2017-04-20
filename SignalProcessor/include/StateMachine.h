#ifndef STATEMACHINE_H
#define STATEMACHINE_H
using namespace std;
#include <string>

class StateMachine
{
    enum gait_state {
        HEEL_STRIKE,
        FOOT_FLAT,
        MID_STANCE,
        HEEL_OFF,
        TOE_OFF,
        MID_SWING,
        NOSTATE,
    };

    public:
    	struct State{
		    gait_state phase;
		   	double time = 0;
		};
    	
        StateMachine();
        double yGyroRange;
        double YTHRESHOLD = -5000;
	    double ZTHRESHOLD = 10000;
	    double GYROTHRESHOLD = -8000;
	    std::string toString();
	    
        State currState;
        State previousState;
        State classify(double YAvg, double ZAvg, double gYroAvg, double gyroSlope);
        

    protected:
    private:
};

#endif // STATEMACHINE_H
