//int powers[][motorCount] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,228,229,0,0},{0,0,0,0,240,229,0,0},{0,0,0,0,238,222,0,0},{0,0,0,0,242,231,0,0},{10,45,39,23,247,215,0,0},{48,41,18,72,234,218,0,0},{68,73,76,75,239,236,0,0},{121,125,125,122,239,227,0,0},{140,163,140,164,240,240,0,0},{174,171,162,168,207,199,0,0},{160,201,199,186,208,201,0,0},{186,189,180,181,199,197,0,0},{189,182,193,194,193,214,0,0},{173,185,180,195,210,205,0,0},{186,170,174,177,222,210,0,0},{193,168,170,152,215,186,0,0},{150,177,153,169,209,176,0,0},{150,151,145,159,209,194,0,0},{156,163,159,155,209,192,0,0},{164,155,163,167,214,202,0,0},{144,153,159,150,203,215,0,0},{151,162,153,164,185,194,0,0},{179,175,175,166,182,192,0,0},{155,146,152,153,187,189,0,0},{161,169,178,165,195,166,0,0},{177,180,177,168,211,188,0,0},{148,130,139,126,186,182,0,0},{147,167,163,154,169,163,0,0},{144,155,154,156,192,191,0,0},{152,143,142,147,193,180,0,0},{165,159,166,130,182,172,0,0},{159,153,159,165,194,207,0,0},{157,51,22,127,209,202,0,0},{57,59,83,21,189,180,0,0},{-61,-59,-60,-58,184,198,0,0},{-142,-150,-151,-145,164,152,0,0},{-205,-219,-206,-214,182,172,0,0},{-239,-258,-251,-263,194,199,0,0},{-275,-267,-276,-268,180,192,0,0},{-274,-285,-291,-272,201,195,0,0},{-280,-285,-283,-276,181,180,0,0},{-289,-289,-298,-254,205,198,2,0},{-371,-297,-365,-220,224,213,0,0},{-345,-123,-352,-136,82,61,0,0},{-177,107,-352,-43,19,14,0,0},{-131,145,-261,50,0,18,0,0},{-78,128,-86,141,-7,-2,0,0},{-44,142,-71,134,-5,-7,0,0},{-39,119,-167,116,-4,-5,0,0},{-41,110,-52,111,0,0,0,0},{-47,121,-60,129,0,0,0,0},{-59,118,-97,113,0,0,0,0},{-81,116,-83,120,0,0,0,0},{-68,128,-81,122,0,0,0,0},{-82,129,-96,117,0,0,0,0},{-94,127,-106,126,0,0,0,0},{42,116,69,71,0,0,0,0},{44,99,61,151,0,0,0,0},{102,124,104,120,0,0,0,0},{137,128,144,110,0,0,0,0},{152,124,168,89,0,0,0,0},{172,121,158,119,0,0,0,0},{144,128,141,172,0,0,0,0},{125,135,132,128,0,0,0,0},{130,123,146,86,0,0,0,0},{136,130,149,99,0,0,0,0},{48,74,40,96,-6,-5,0,0},{17,0,18,99,-7,-6,0,0},{15,51,138,0,0,-4,0,0},{-25,-35,-23,-15,0,0,0,0},{0,-22,-33,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

/*  MachineState FSM[] = 
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
        MachineState(State::DriveForward, StateType::Brake, 40, 1700), //900 1900
        MachineState(State::TowerReset),
 
        //Drive backwards with four(4) #8-9
        MachineState(State::DriveBackward, StateType::Ignore, 85, 1100), //1300
        MachineState(State::DriveBackward, StateType::Brake, 60, 300),
        MachineState(State::IntakeSet, StateType::Ignore, 60),
 
        //Line up for tower lift #10-12
        MachineState(State::TurnTo, StateType::Coast, 40, -1350, 1600),
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
   