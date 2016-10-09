#include "StateMachine.h"

StateMachine::StateMachine()
{
    YTHRESHOLD = -5000;
    ZTHRESHOLD = 10000;
    GYROTHRESHOLD = -8000;
    currentState = NULL;
}

StateMachine::~StateMachine()
{
    //dtor
}

/*
enum gait_state {
        HEEL_STRIKE,
        FOOT_FLAT,
        MID_STANCE,
        HEEL_OFF,
        TOE_OFF,
        MID_SWING,
    };
*/

StateMachine::classify(int time, double YAvg, double ZAvg, double gYroAvg, double gyroSlope) {
    switch (currState.phase){
        case gait_state[5]:
        if (YAvg < YTHRESHOLD && ZAvg > ZTHRESHOLD) {
            currState.phase = gait_state[0];
            currState.time = time;
        }
        break;
    case gait_state[4]:
        if (gYroAvg <= GYROTHRESHOLD) {
            currState.phase = gait_state[5];
            currState.time = time;
        }
        break;
    case gait_state[3]:
        if (ZAvg > ZTHRESHOLD){
            currState.phase = gait_state[4];
            currState.time = time;
        }
        break;
    case gait_state[2]):
        if (gyroSlope >= 100 && gyroSlope <= 300) {
            currState.phase = gait_state[3];
            currState.time = time;
        }
        break;
    case gait_state[1]:
        if (gyroSlope >= 300) {
            currState.phase = gait_state[2];
            currState.time = time;
        }
        break;
    case gait_state[0]:
        if (gYroAvg >= -1000 && gYroAvg <= 1000) {
            currState.phase = gait_state[1];
            currState.time = time;
        }
        break;
    }
}
