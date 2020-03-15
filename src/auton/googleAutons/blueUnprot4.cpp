/*
    MachineState FSM[] = 
    {
        MachineState(State::DriveForwardV, StateType::Coast, 500, 300), 
        MachineState(State::DriveForwardV, StateType::Brake, 100, 150),
        MachineState(State::DriveSet, StateType::Ignore, -10),
        MachineState(State::OpenSeq, true),
        MachineState(State::DriveTime, StateType::Brake, -20, 600),
        MachineState(State::IntakeSet, StateType::Ignore, 127),
        MachineState(State::DriveForwardV, StateType::Brake, 150, 2600),
        MachineState(State::DriveBackwardV, StateType::Coast, 50, 50),
        MachineState(State::DriveBackwardV, StateType::Coast, 350, 850),
        MachineState(State::DriveBackwardV, StateType::Brake, 200, 300),
        MachineState(State::DriveTime, StateType::Ignore, 0, 500),
        MachineState(State::TurnTo, StateType::Coast, 40, -1350, 2000),
        MachineState(State::DriveTime, StateType::Ignore, 50, 1500),
        MachineState(State::DriveBackward, StateType::Brake, 30, 75),

        MachineState(State::IntakeOut, StateType::Coast, 85, 185),
        MachineState(State::IntakeSet, StateType::Ignore, 20),
        MachineState(State::TowerTo, StateType::Coast, 16, 1690, 1600), //Ignore
        //MachineState(State::DriveTime, StateType::Coast, 30, 500),
        MachineState(State::TowerSet, StateType::Ignore, -70),
        MachineState(State::IntakeSet, StateType::Ignore, -90),
        MachineState(State::DriveBackward, StateType::Coast, 50, 400),
        MachineState(State::TowerSet, StateType::Brake, 0),

        MachineState(State::Idle)
    };
*/