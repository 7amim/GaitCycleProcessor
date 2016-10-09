#ifndef STATEMACHINE_H
#define STATEMACHINE_H


class StateMachine
{

    enum gait_state {
        HEEL_STRIKE,
        FOOT_FLAT,
        MID_STANCE,
        HEEL_OFF,
        TOE_OFF,
        MID_SWING,
    };

    struct State{
        gait_state phase;
        double time = 0;
    };

    public:
        StateMachine();
        double yGyroRange;
        const double YTHRESHOLD;
        const double ZTHRESHOLD;
        const double GYROTHRESHOLD;
        State currState
        return classify();

    protected:
    private:
};

#endif // STATEMACHINE_H
