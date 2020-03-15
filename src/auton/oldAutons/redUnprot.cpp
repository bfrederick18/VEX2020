/* MachineState FSM[] = 
    {
        //Initial sequence #0-3
        MachineState(State::OpenSeq, true),
        MachineState(State::DriveReset),
        MachineState(State::GyroReset),
        MachineState(State::IntakeSet, StateType::Ignore, 127),
 
        //Drive forwards picking up row of four(4) #4-7
        MachineState(State::TowerSet, StateType::Ignore, -40),
        MachineState(State::DriveForward, StateType::Ignore, 40, 800),
        MachineState(State::TowerSet, StateType::Ignore, 0),
        MachineState(State::DriveForward, StateType::Brake, 40, 1900), //900
        MachineState(State::TowerReset),
 
        //Drive backwards with four(4) #8-9
        MachineState(State::DriveBackward, StateType::Ignore, 75, 1100),
        MachineState(State::DriveBackward, StateType::Brake, 60, 300),
        MachineState(State::IntakeSet, StateType::Ignore, 60),
 
        //Line up for tower lift #10-12
        MachineState(State::TurnTo, StateType::Coast, 40, 1300, 1600),
        MachineState(State::TowerSet, StateType::Ignore, 0), 
        MachineState(State::DriveTime, StateType::Ignore, 60, 1500),
        MachineState(State::DriveBackward, StateType::Brake, 30, 150),
 
        //Tower lift sequence #13-16
        MachineState(State::IntakeOut, StateType::Coast, 85, 400),
        //MachineState(State::DriveSet, StateType::Ignore, 20),
        MachineState(State::IntakeSet, StateType::Ignore, 20),
        MachineState(State::TowerTo, StateType::Ignore, 20, 1600, 2000),
 
        //Back up from goal #17-21
        MachineState(State::DriveTime, StateType::Coast, 30, 500),
        MachineState(State::TowerSet, StateType::Ignore, -40),
        MachineState(State::IntakeTime, StateType::Ignore, -40, 400),
        MachineState(State::DriveBackward, StateType::Coast, 30, 400),
        MachineState(State::TowerSet, StateType::Ignore, 0),
        
        MachineState(State::Idle)
    };
    */