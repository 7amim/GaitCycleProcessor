#include "..\include\StateMachine.h"
#include <cstddef>

StateMachine::StateMachine()
{
	currState.phase = gait_state::NOSTATE;
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
StateMachine::State StateMachine::classify(int time, double YAvg, double ZAvg, double gYroAvg, double gyroSlope) {
    switch (currState.phase) {
      case NOSTATE:
      case MID_SWING:
        if (YAvg < YTHRESHOLD && ZAvg > ZTHRESHOLD) {
            currState.phase = HEEL_STRIKE;
            currState.time = time;
        }
        break;
    case TOE_OFF:
        if (gYroAvg <= GYROTHRESHOLD) {
            currState.phase = MID_SWING;
            currState.time = time;
        }
        break;
    case HEEL_OFF:
        if (ZAvg > ZTHRESHOLD){
            currState.phase = TOE_OFF;
            currState.time = time;
        }
        break;
    case MID_STANCE:
        if (gyroSlope >= 100 && gyroSlope <= 300) {
            currState.phase = HEEL_OFF;
            currState.time = time;
        }
        break;
    case FOOT_FLAT:
        if (gyroSlope >= 300) {
            currState.phase = MID_STANCE;
            currState.time = time;
        }
        break;
    case HEEL_STRIKE:
        if (gYroAvg >= -1000 && gYroAvg <= 1000) {
            currState.phase = FOOT_FLAT;
            currState.time = time;
        }
        break;
    }
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
