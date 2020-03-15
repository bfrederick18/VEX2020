/* RED SKILLZ
MachineState FSM[] = 
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
        MachineState(State::DriveBackward, StateType::Ignore, 75, 1000),
        MachineState(State::DriveBackward, StateType::Brake, 60, 300),
        MachineState(State::IntakeSet, StateType::Ignore, 60),

        MachineState(State::TurnTo, StateType::Coast, 40, -700, 1600),
        MachineState(State::DriveBackward, StateType::Brake, 50, 1350),
        MachineState(State::TurnTo, StateType::Coast, 40, 0, 1600),

        MachineState(State::IntakeSet, StateType::Ignore, 127),
 
        //Drive forwards picking up row of four(4) #4-7
        MachineState(State::DriveForward, StateType::Ignore, 40, 800),
        MachineState(State::DriveForward, StateType::Brake, 40, 1700), //900
        MachineState(State::TowerReset),
 
        //Drive backwards with four(4) #8-9
        MachineState(State::DriveBackward, StateType::Ignore, 75, 1300),
 
        //Line up for tower lift #10-12
        MachineState(State::IntakeSet, StateType::Ignore, 50),
        MachineState(State::TurnTo, StateType::Coast, 20, 1350, 4000),
        MachineState(State::TowerSet, StateType::Ignore, 0), 
        MachineState(State::DriveTime, StateType::Ignore, 40, 2200),
        MachineState(State::DriveBackward, StateType::Brake, 25, 150),
 
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

   /* BLUE SKILLZ
MachineState FSM[] = 
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
        MachineState(State::DriveForward, StateType::Brake, 40, 1800), //900 //1900
        MachineState(State::TowerReset),
 
        //Drive backwards with four(4) #8-9
        MachineState(State::DriveBackward, StateType::Ignore, 75, 1000),
        MachineState(State::DriveBackward, StateType::Brake, 60, 300),
        MachineState(State::IntakeSet, StateType::Ignore, 60),

        MachineState(State::TurnTo, StateType::Coast, 40, 650, 1600),
        MachineState(State::DriveBackward, StateType::Brake, 50, 1700),
        MachineState(State::TurnTo, StateType::Coast, 40, 0, 1600),

        MachineState(State::IntakeSet, StateType::Ignore, 127),
 
        //Drive forwards picking up row of four(4) #4-7
        MachineState(State::DriveForward, StateType::Ignore, 40, 800),
        MachineState(State::DriveForward, StateType::Brake, 40, 2350), //900
        MachineState(State::TowerReset),
 
        //Drive backwards with four(4) #8-9
        MachineState(State::DriveBackward, StateType::Brake, 75, 2250),
 
        //Line up for tower lift #10-12
        MachineState(State::IntakeSet, StateType::Ignore, 20),
        //MachineState(State::TurnTo, StateType::Coast, 20, -1350, 2500),
        MachineState(State::TowerSet, StateType::Ignore, 0),
        MachineState(State::TurnTo, StateType::Coast, 21, -1300, 3000),
        MachineState(State::DriveTime, StateType::Ignore, 70, 1300),
        MachineState(State::DriveBackward, StateType::Brake, 50, 125), 
 
        //Tower lift sequence #13-16
        MachineState(State::IntakeOut, StateType::Coast, 85, 400),
        //MachineState(State::DriveSet, StateType::Ignore, 20),
        MachineState(State::IntakeSet, StateType::Ignore, 30),
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