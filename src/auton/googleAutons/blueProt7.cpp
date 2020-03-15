/*
    MachineState FSM[] = 
    {
        MachineState(State::DriveForwardV, StateType::Brake, 100, 250),
        MachineState(State::OpenSeq, true),
        MachineState(State::DriveTime, StateType::Brake, -20, 600),
        MachineState(State::IntakeSet, StateType::Ignore, 127),
        MachineState(State::DriveForwardV, StateType::Coast, 150, 150),
        MachineState(State::DriveForwardV, StateType::Brake, 250, 600),
        MachineState(State::TurnTo, StateType::Brake, 20, 900, 1300),
        MachineState(State::IntakeTime, StateType::Brake, -127, 2000),
        MachineState(State::TurnTo, StateType::Brake, 20, 0, 1300),
        
        MachineState(State::Idle)
    };
*/