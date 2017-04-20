#include "..\include\StateMachine.h"
#include <cstddef>
#include <iostream>
using namespace std;

StateMachine::StateMachine()
{
	currState.phase = NOSTATE;
}

/*
StateMachine::~StateMachine()
{
    //dtor
}
*/

enum gait_state {
        HEEL_STRIKE,
        FOOT_FLAT,
        MID_STANCE,
        HEEL_OFF,
        TOE_OFF,
        MID_SWING,
        NOSTATE,
};


// The NULL case is placed before every case becaus it is unkown which phase the walking will begin in
StateMachine::State StateMachine::classify(double YAvg, double ZAvg, double gYroAvg, double gyroSlope) {
    previousState = currState;
    // cout << ZAvg << endl;
    //  case NOSTATE:
    //  case MID_SWING:
        if (YAvg < YTHRESHOLD && ZAvg > ZTHRESHOLD) {
            currState.phase = HEEL_STRIKE;
           // currState.time = time;
        }
        // case TOE_OFF:
        else if (gYroAvg <= GYROTHRESHOLD) {
            currState.phase = MID_SWING;
           // currState.time = time;
        }
        
    	// case HEEL_OFF:
        else if (ZAvg > ZTHRESHOLD && (currState.phase == HEEL_OFF || currState.phase == NOSTATE)){
            currState.phase = TOE_OFF;
           // currState.time = time;
        }
        // case MID_STANCE:
        else if (gyroSlope >= 100 && gyroSlope <= 300 && currState.phase == MID_STANCE || currState.phase == NOSTATE) {
            currState.phase = HEEL_OFF;
           // currState.time = time;
        }
        
    // case FOOT_FLAT:
        else if (gyroSlope >= 300 && (currState.phase == FOOT_FLAT || currState.phase == NOSTATE)) {
            currState.phase = MID_STANCE;
           // currState.time = time;
        }
        
    // case HEEL_STRIKE:
        else if (gYroAvg >= -1000 && gYroAvg <= 1000) {
            currState.phase = FOOT_FLAT;
        	// currState.time = time;
        }
    	
    // cout << "READ STATE" << endl;
    return currState;
}

string StateMachine::toString() {
	switch (currState.phase) {
		case HEEL_STRIKE: return "Heel Strike";
		case FOOT_FLAT: return "Foot flat";
		case MID_STANCE: return "Midstance";
		case HEEL_OFF: return "Heel off";
		case MID_SWING: return "Midswing";
	}
}
