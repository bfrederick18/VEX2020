/*
MachineState FSM[] = 
    {
        MachineState(State::DriveForwardV, StateType::Coast, 400, 400), 
        MachineState(State::DriveForwardV, StateType::Gentle, 100, 250),
        MachineState(State::DriveTime, StateType::Ignore, -20, 300),
        MachineState(State::DriveSet, StateType::Ignore, -10),
        MachineState(State::OpenSeq, true),
        MachineState(State::DriveTime, StateType::Coast, -20, 1200),
        MachineState(State::DriveTime, StateType::Coast, -40, 500),
        MachineState(State::IntakeSet, StateType::Gentle, 127),
        MachineState(State::DriveForward, StateType::Gentle, 33, 2600),
        MachineState(State::DriveBackwardV, StateType::Coast, 50, 50),
        MachineState(State::DriveBackwardV, StateType::Coast, 350, 750),
        MachineState(State::IntakeSet, StateType::Gentle, 50),
        MachineState(State::DriveBackwardV, StateType::Gentle, 200, 300),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -135, 1600),
        MachineState(State::DriveTime, StateType::Ignore, 50, 1500),
        MachineState(State::DriveBackward, StateType::Brake, 30, 40),

        MachineState(State::IntakeOut, StateType::Coast, 127, 160),
        MachineState(State::IntakeSet, StateType::Ignore, -10),
        MachineState(State::TowerTo, StateType::Coast, 16, 1690, 2000),
        MachineState(State::TowerSet, StateType::Ignore, -70),
        MachineState(State::IntakeSet, StateType::Ignore, -90),
        //MachineState(State::DriveTime, StateType::Ignore, 0, 500), 
        MachineState(State::DriveBackward, StateType::Coast, 50, 400),
        MachineState(State::TowerSet, StateType::Brake, 0),

        MachineState(State::Idle)
    };
*/