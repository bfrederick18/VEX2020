/*
    MachineState FSM[] = 
    {
        //Initial sequence #0-4
        MachineState(State::DriveForward, StateType::Brake, 90, 200),
        MachineState(State::DriveBackward, StateType::Brake, 90, 50),
        MachineState(State::OpenSeq, true),
        MachineState(State::DriveReset),
        MachineState(State::IntakeSet, StateType::Ignore, 127),
 
        //Drive forwards 
        MachineState(State::TowerSet, StateType::Ignore, -40),
        MachineState(State::DriveForward, StateType::Ignore, 30, 800),
        MachineState(State::TowerSet, StateType::Ignore, 0),
        MachineState(State::DriveForward, StateType::Brake, 55, 1900), //900
        MachineState(State::TowerReset),
 
        //Drive backwards
        MachineState(State::DriveBackward, StateType::Brake, 85, 1100),
        MachineState(State::IntakeSet, StateType::Ignore, 60),
 
        MachineState(State::TurnTo, StateType::Coast, 50, 900, 1200),
        MachineState(State::IntakeSet, StateType::Ignore, 127),
        MachineState(State::DriveForward, StateType::Brake, 50, 1200),
        MachineState(State::TowerSet, StateType::Ignore, 20),
 
        MachineState(State::TurnTo, StateType::Coast, 40, 1350, 1000),
        MachineState(State::DriveTime, StateType::Ignore, 40, 1500),
        MachineState(State::DriveBackward, StateType::Brake, 40, 250),
 
        //Tower lift sequence #13-16
        MachineState(State::IntakeOut, StateType::Coast, 80, 400),
        //MachineState(State::DriveSet, StateType::Ignore, 20),
        MachineState(State::IntakeSet, StateType::Ignore, 20),
        MachineState(State::TowerTo, StateType::Ignore, 20, 1600, 2000),
 
        //Back up from goal #17-21
        MachineState(State::DriveTime, StateType::Coast, 30, 500),
        MachineState(State::TowerSet, StateType::Ignore, -40),
        MachineState(State::IntakeTime, StateType::Ignore, -40, 400),
        MachineState(State::DriveBackward, StateType::Coast, 70, 400),
        MachineState(State::TowerSet, StateType::Ignore, 0),
 
        MachineState(State::Idle)
    };
    */