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
        MachineState(State::IntakeSet, StateType::Gentle, 120),
        MachineState(State::DriveForward, StateType::Gentle, 70, 1500),
        MachineState(State::IntakeSet, StateType::Gentle, 0),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, 40, 500),
        MachineState(State::IntakeSet, StateType::Gentle, -127),
        MachineState(State::DriveTime, StateType::Coast, 0, 300),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, 5, 800),
        MachineState(State::IntakeSet, StateType::Gentle, 127),
        MachineState(State::DriveForward, StateType::Gentle, 127, 1400),
        MachineState(State::DriveTime, StateType::Coast, 0, 200),
        MachineState(State::NewGyroTurnTo, StateType::Brake, 300, 0, 500),
        MachineState(State::DriveBackwardV, StateType::Ramp, 300, 800),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -90, 1500),

        MachineState(State::DriveForward, StateType::Brake, 60, 1200),
        MachineState(State::TowerSet, StateType::Ignore, 20),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -135, 1000),

        MachineState(State::DriveTime, StateType::Ignore, 50, 1200),
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
        MachineState(State::IntakeSet, StateType::Gentle, 120),
        MachineState(State::DriveForward, StateType::Gentle, 90, 1300),
        MachineState(State::IntakeSet, StateType::Gentle, 0),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, 50, 500),
        MachineState(State::DriveForwardV, StateType::Coast, 200, 100),

        MachineState(State::IntakeSet, StateType::Gentle, -127),
        MachineState(State::DriveTime, StateType::Coast, 0, 300),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, 0, 800),
        MachineState(State::IntakeSet, StateType::Gentle, 127),
        MachineState(State::DriveForward, StateType::Gentle, 127, 1600),
        MachineState(State::DriveTime, StateType::Coast, 0, 200),
        MachineState(State::NewGyroTurnTo, StateType::Brake, 300, 0, 500),
        MachineState(State::DriveBackwardV, StateType::Ramp, 300, 1000),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -90, 1500),

        MachineState(State::DriveForward, StateType::Brake, 90, 1900),
        MachineState(State::TowerSet, StateType::Ignore, 20),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -135, 1200),

        MachineState(State::DriveTime, StateType::Ignore, 50, 1200),
        MachineState(State::DriveBackward, StateType::Brake, 30, 40),

        MachineState(State::IntakeOut, StateType::Coast, 127, 150),
        MachineState(State::IntakeSet, StateType::Ignore, -10),
        MachineState(State::TowerTo, StateType::Coast, 16, 1690, 1800),
        MachineState(State::TowerSet, StateType::Ignore, -70),
        MachineState(State::IntakeSet, StateType::Ignore, -90),
        //MachineState(State::DriveTime, StateType::Ignore, 0, 500), 
        MachineState(State::DriveBackward, StateType::Coast, 50, 400),
        MachineState(State::TowerSet, StateType::Brake, 0),

        MachineState(State::Idle)
    };
*/