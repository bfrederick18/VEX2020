#include "main.h"
#include "motorconfigs.h"

#include <iostream>
#include <string>
#include <time.h>

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(LEFT_FRONT_MOTOR_PORT, MOTOR_GEARSET_06, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(RIGHT_FRONT_MOTOR_PORT, MOTOR_GEARSET_06, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(LEFT_BACK_MOTOR_PORT, MOTOR_GEARSET_06, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(RIGHT_BACK_MOTOR_PORT, MOTOR_GEARSET_06, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftIntake(LEFT_INTAKE_MOTOR_PORT, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightIntake(RIGHT_INTAKE_MOTOR_PORT, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor arm(ARM_MOTOR_PORT, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor tower(TOWER_MOTOR_PORT, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalIn towerBumper(TOWER_BUMPER_PORT);
pros::ADIGyro yawGyro(YAW_GYRO_PORT);
pros::Vision vision(VISION_PORT);
pros::Imu imu(IMU_PORT);

#pragma region ~ENUMS
enum class State 
{
    Idle,               //Does nothing... (Normally at the end of auton)
    OpenSeq,            //Initial expand against a wall(bool) (ONLY at the beginning of auton; 'true' will stall against the wall, while 'false' will not)
    DriveForward,       //Drives forward 'degrees'(+) degrees at 'power'(+) power
    DriveBackward,      //Drives backward 'degrees'(+) degrees at 'power'(+) power
    DriveTo,            //Drives to 'degrees'(+/-) degrees at 'percent'(+) percent power using PID for 'time'(+) milliseconds
    DriveTime,          //Drives for 'time'(+) milliseconds at 'power'(+/-) power
    DriveSet,           //Sets drivetrain to 'power'(+/-) power
    DriveReset,         //Resets drivetrain encoders
    DriveForwardV,      //Drives forwrds 'degrees'(+) degrees at 'velocity'(+) velocity
    DriveBackwardV,     //Drives backward 'degrees'(+) degrees at 'velocity'(+) velocity
    RightTurn,          //Turns right to 'degrees'(-) 1/10-degrees at 'power'(+) power
    LeftTurn,           //Turns left to 'degrees'(+) 1/10-degrees at 'power'(+) power
    TurnTo,             //Turns to 'degrees'(+/-) 1/10 degrees at 'percent'(+) percent power using PID for 'time'(+) milliseconds
    GyroReset,          //Resets gyro value
    NewGyroTurnTo,
    SwerveForwardL,     //Drives forwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(+) degrees based on leftFront
    SwerveForwardR,     //Drives forwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(+) degrees based on rightFront
    SwerveBackwardL,    //Drives backwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(-) degrees based on leftFront
    SwerveBackwardR,    //Drives backwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(-) degrees based on rightFront
    SwerveForwardGyroL, //Drives forwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(+) 1/10-degrees based on the gyro
    SwerveForwardGyroR, //Drives forwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(-) 1/10-degrees based on the gyro
    SwerveBackwardGyroL,//Drives backwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(+) 1/10-degrees based on the gyro
    SwerveBackwardGyroR,//Drives backwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(-) 1/10-degrees based on the gyro
    SwerveBackwardGyroLV,//Drives backwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(+) 1/10-degrees based on the gyro VELOCITY
    SwerveBackwardGyroRV,//Drives backwards with 'lpower'(+) and 'rpower'(+) for 'degrees'(-) 1/10-degrees based on the gyro VELOCITY
    TowerUp,            //Moves the tray 'degrees'(+) degress at 'power'(+) power
    TowerDown,          //Moves the tray 'degrees'(-) degrees at 'power'(+) power
    TowerTo,            //Moves the tray to 'degrees'(+/-) degrees at 'percent'(+) percent power using PID for 'time'(+) milliseconds
    TowerSet,           //Sets the tray to 'power'(+/-) power
    TowerReset,         //Resets the tray encoder
    ArmUp,              //Moves the arm 'degrees'(+) degrees at 'power'(+) power
    ArmDown,            //Moves the arm 'degrees'(-) degrees at 'power'(-) power
    ArmTo,              //Moves the arm to 'degrees'(+/-) degrees at 'percent'(+) percent power using PID for 'time'(+) milliseconds
    ArmSet,             //Sets arm to 'power'(+/-) power
    IntakeIn,           //Spins intake inwards 'degrees'(+) degrees at 'power'(+) power
    IntakeOut,          //Spins intake outwards 'degrees'(-) degrees at 'power'(+) power
    IntakeTo,           //Spins intake to 'degrees'(+/-) degrees at 'percent'(+) percent power using PID for 'time'(+) milliseconds
    IntakeTime,         //Spins intake at 'power'(+/-) power for 'time'(+) milliseconds
    IntakeSet           //Sets intake to 'power'(+/-) power
};
 
enum class StateType
{
    Ignore,             //Does not stop the motor at the end of the function
    Coast,              //Sets motor power to 0
    Brake,              //Sets the motor power to a negative power with a small magnitude in comparison to 'power' (ex. if 'power' was 100, then brake power will be -10), effectively halting the drivetrain   
    Gentle,             //FOR VELOCITY ONLY! Ramps down the power of a short time to zero
    Ramp                //Ramps up power and ramps down
};
#pragma endregion
 
class MachineState
{
    public:
    State state;
    StateType type;
    bool val0;
    int val1, val2, val3;
 
    MachineState()
    {
        state = State::Idle;
    }
 
    MachineState(State pstate, bool pval0 = false)
    {
        state = pstate;
        val0 = pval0;
    }
 
    MachineState(State pstate, StateType ptype, int pval1 = 0, int pval2 = 0, int pval3 = 0)
    {
        state = pstate;
        type = ptype;
        val1 = pval1;
        val2 = pval2;
        val3 = pval3;
    }
};
 
#pragma region ~BASE FUNCTIONS~
void drivetrain(int lPower, int rPower)         //INTS
{
    leftFront = lPower;
    leftBack = lPower;
    rightFront = rPower;
    rightBack = rPower;
}
void drivetraind(double lPower, double rPower)    //DOUBLES
{
    leftFront = lPower;
    leftBack = lPower;
    rightFront = rPower;
    rightBack = rPower;
}
void drivetrainV(int lVelocity, int rVelocity)
{
    leftFront.move_velocity(lVelocity);
    leftBack.move_velocity(lVelocity);
    rightFront.move_velocity(rVelocity);
    rightBack.move_velocity(rVelocity);
}
void brake(int power, StateType type)
{
    if (type == StateType::Brake)
    {
        drivetrain(-power / 8, -power / 8);
 
        pros::delay(100);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}
void brakeV(int velocity, StateType type)
{
    if (type == StateType::Brake)
    {
        drivetrainV(0, 0);
    }
    else if(type == StateType::Gentle)
    {
        for (int i = velocity; i >= 0; i -= 2)
        {
            drivetrainV(i, i);
            pros::delay(1);
        }
        drivetrainV(0, 0);
    }
    else if (type == StateType::Coast || type == StateType::Ignore)
    {
        //Nothing
    }

}
void intake(int power)
{
    leftIntake = power;
    rightIntake = power;
}
#pragma endregion

#pragma region ~STATE FUNCTIONS~
void openingSequence(bool driveForwards)
{
    while (arm.get_position() <= 200)
    {
        arm = 127;

        pros::delay(1);
    }
    arm = 0;

    //pros::delay(1200);
}
 
void driveForward(int power, int degrees, StateType type)
{
    int initD = leftBack.get_position();
 
    drivetrain(power, power);
 
    while (leftBack.get_position() - initD < degrees) {}
 
    if (type != StateType::Gentle)
    {
        brake(power, type);
    }
    else
    {
        drivetrainV(0, 0);
    }
}
void driveBackward(int power, int degrees, StateType type)
{
    int initD = leftBack.get_position();
 
    drivetrain(-power, -power);
 
    while (leftBack.get_position() - initD > -degrees) {}
 
    brake(power, type);
}
void driveTime(int power, int time, StateType type)
{
    drivetrain(power, power);
 
    pros::delay(time);
    
    if (type != StateType::Gentle)
    {
        brake(power, type);
    }
    else
    {
        drivetrainV(0, 0);
    }
    
}
void driveSet(int power)
{
    drivetrain(power, power);
}
void driveReset()
{
    leftFront.set_zero_position(0);
    rightFront.set_zero_position(0);
    leftBack.set_zero_position(0);
    rightBack.set_zero_position(0);
}
void driveForwardV(int velocity, int degrees, StateType type) //UNTESTED
{
    int initD = leftBack.get_position();
 
    if (type == StateType::Ramp)
    {
        for (int i = 0; i < velocity; i += 2)
        {
            drivetrainV(i, i);
            pros::delay(1);
        }
    }

    drivetrainV(velocity, velocity);
 
    while (leftBack.get_position() - initD < degrees) {}
 
    if (type != StateType::Ramp)
    {
        brakeV(velocity, type);
    }
    else
    {
        for (int i = velocity; i >= 0; i -= 2)
        {
            drivetrainV(i, i);
            pros::delay(1);
        }
    }
    
}
void driveBackwardV(int velocity, int degrees, StateType type) //UNTESTED
{
    int initD = leftBack.get_position();
 
    drivetrainV(-velocity, -velocity);
 
    while (leftBack.get_position() - initD > -degrees) {}
 
    brakeV(-velocity, type);
}

void leftTurn(int power, int degrees, StateType type)
{
    while (yawGyro.get_value() <= degrees)
    {
        drivetrain(-power, power);
    }
 
    if (type == StateType::Brake)
    {
        drivetrain(power / 8, -power / 8);
 
        pros::delay(100);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}
void turnTo(int percent, int degrees, int time, StateType type)
{
    int ti = 0;
    while (ti < time)
    {
        drivetraind((double)((degrees - yawGyro.get_value()) * percent / 100), (double)(-(degrees - yawGyro.get_value()) * percent / 100));
 
        ti++;
        pros::delay(1);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}
void gyroReset()
{
    yawGyro.reset();
}
void newGyroTurnTo(int factor, int degrees, int time, StateType type)//(int target, StateType type)
{
    int ti = 0;
    while (ti < time)
    {
        drivetraind((double)((degrees - imu.get_rotation()) * factor / 100), (double)(-(degrees - imu.get_rotation()) * factor / 100));
 
        ti++;
        pros::delay(1);
    }
 
    if (type == StateType::Brake)
    {
        drivetrainV(0, 0);
    }
    else if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }

    /*int error = 100;
    int previousError = 0;
    int totalError = 0;

    while (abs(error - previousError) >= 1)
    {
        double kP = 5.5; //5.5 7.5
        double kI = 0.05;
        double kD = 4.0; //3.5 8.5

        error = imu.get_rotation() - target;
        totalError += error;
        int derivative = error - previousError;

        int motorPower = (error * kP + totalError * kI + derivative * kD); //Add values up
        leftFront = -motorPower;
        leftBack = -motorPower;
        rightFront = motorPower;
        rightBack = motorPower;

        previousError = error; 
        pros::delay(20);
        pros::lcd::print(0, "%f", imu.get_rotation());
    }*/
}

void swerveBackwardR(int lpower, int rpower, int degrees, StateType type)
{
    int initD = leftBack.get_position();
 
    drivetrain(-lpower, -rpower);
 
    while (leftBack.get_position() - initD > -degrees) {}
 
    if (type == StateType::Brake)
    {
        drivetrain(lpower / 8, rpower / 8);
 
        pros::delay(100);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}
void swerveBackwardGyroL(int lpower, int rpower, int degrees, StateType type)
{
    drivetrain(-lpower, -rpower);
 
    while (yawGyro.get_value() <= degrees) {}
 
    if (type == StateType::Brake)
    {
        drivetrain(lpower / 8, rpower / 8);
 
        pros::delay(100);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}
void swerveBackwardGyroR(int lpower, int rpower, int degrees, StateType type)
{
    drivetrain(-lpower, -rpower);
 
    while (yawGyro.get_value() >= degrees) {}
 
    if (type == StateType::Brake)
    {
        drivetrain(lpower / 8, rpower / 8);
 
        pros::delay(100);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}

void swerveBackwardGyroLV(int lpower, int rpower, int degrees, StateType type)
{
    drivetrainV(-lpower, -rpower);
 
    while (yawGyro.get_value() >= degrees) 
    {
        pros::lcd::print(5, "Gyro: %f\n", yawGyro.get_value());
        pros::delay(1);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrain(0, 0);
    }
}
void swerveBackwardGyroRV(int lpower, int rpower, int degrees, StateType type)
{
    drivetrainV(-lpower, -rpower);
 
    while (yawGyro.get_value() <= degrees) 
    {
        pros::lcd::print(5, "Gyro: %f\n", yawGyro.get_value());
        pros::delay(1);
    }
 
    if (type != StateType::Ignore)
    {
        drivetrainV(0, 0);
    }
}

void towerUp(int percent, int degrees, int stopDeg, StateType type)
{
    int ti = 0;
    while (tower.get_position() < stopDeg)
    {
        tower = (degrees - tower.get_position()) * percent / 100;
 
        ti++;
        pros::delay(1);
    }
 
    if (type != StateType::Ignore)
    {
        tower = 0;
    }
    pros::lcd::print(3, "DONE");
}
void towerTo(int percent, int degrees, int time, StateType type)
{
    int ti = 0;
    while (ti < time)
    {
        tower = (degrees - tower.get_position()) * percent / 100;
 
        ti++;
        pros::delay(1);
    }
 
    if (type != StateType::Ignore)
    {
        tower = 0;
    }
}
void towerSet(int power)
{
    tower = power;
}
void towerReset()
{
    tower.set_zero_position(0);
}

void armUp(int degrees, int time, int c, StateType type)
{
    int t = 0;
    while (t < time)
    {
        arm = (degrees - arm.get_position()) * c;
        
        pros::lcd::print(4, "Arm Power: %f\n", (degrees - arm.get_position()) * c);

        t++;
        pros::delay(1);
    }
}
void armSet(int power, int divisor)
{
    arm = power * 1.0f / divisor;
}

void intakeOut(int power, int degrees, StateType type)
{
    int initD = leftIntake.get_position();
 
    intake(-power);
 
    while (leftIntake.get_position() - initD > -degrees) {}
 
    if (type != StateType::Ignore)
    {
        intake(0);
    }
}
void intakeTime(int power, int time, StateType type)
{
    intake(power);
    
    pros::delay(time);
 
    if (type != StateType::Ignore)
    {
        intake(0);
    }
}
void intakeSet(int power)
{
    intake(power);
}
#pragma endregion


void initialize() 
{
    pros::lcd::initialize();
}

void disabled() 
{

}

void competition_initialize() 
{
	pros::lcd::initialize();
}

void autonomous()
{   
    std::uint32_t now = pros::millis();
 
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
        MachineState(State::DriveTime, StateType::Coast, 0, 200),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, 0, 1000),
        MachineState(State::IntakeSet, StateType::Gentle, 127),
        MachineState(State::DriveForward, StateType::Gentle, 127, 1520),
        //MachineState(State::DriveTime, StateType::Coast, 0, 200),
        
        MachineState(State::NewGyroTurnTo, StateType::Brake, 300, 0, 500),
        MachineState(State::DriveBackwardV, StateType::Ramp, 300, 950),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -90, 1500),
        MachineState(State::IntakeSet, StateType::Gentle, -127),
        MachineState(State::DriveTime, StateType::Coast, 0, 300),
        MachineState(State::IntakeSet, StateType::Gentle, 127),

        MachineState(State::DriveForward, StateType::Brake, 90, 1900),
        MachineState(State::TowerSet, StateType::Ignore, 20),
        MachineState(State::NewGyroTurnTo, StateType::Coast, 300, -135, 1000),

        MachineState(State::DriveTime, StateType::Ignore, 50, 1200),
        MachineState(State::DriveBackward, StateType::Brake, 30, 40),

        MachineState(State::IntakeOut, StateType::Coast, 127, 140),
        MachineState(State::IntakeSet, StateType::Ignore, -10),
        MachineState(State::TowerTo, StateType::Coast, 16, 1690, 1800),
        MachineState(State::TowerSet, StateType::Ignore, -70),
        MachineState(State::IntakeSet, StateType::Ignore, -90),
        //MachineState(State::DriveTime, StateType::Ignore, 0, 500), 
        MachineState(State::DriveBackward, StateType::Coast, 50, 400),
        MachineState(State::TowerSet, StateType::Brake, 0),

        MachineState(State::Idle)
    };
 
    int index = 0; 
    MachineState currState;
 
    while (FROMSD == 0)
    {
        currState = FSM[index];
        switch(currState.state)
        {
            case(State::Idle):
            pros::delay(3000);
            index--;
            break;
            case(State::OpenSeq):
            openingSequence(currState.val0);
            break;
 
            case(State::DriveForward):
            driveForward(currState.val1, currState.val2, currState.type);
            break;
            case(State::DriveBackward):
            driveBackward(currState.val1, currState.val2, currState.type);
            break;
            case(State::DriveTime):
            driveTime(currState.val1, currState.val2, currState.type);
            break;
            case(State::DriveSet):
            driveSet(currState.val1);
            break;
            case(State::DriveReset):
            driveReset();
            break;
            case(State::DriveForwardV):
            driveForwardV(currState.val1, currState.val2, currState.type);
            break;
            case(State::DriveBackwardV):
            driveBackwardV(currState.val1, currState.val2, currState.type);
            break;
 
            case(State::LeftTurn):
            leftTurn(currState.val1, currState.val2, currState.type);
            break;
            case(State::TurnTo):
            turnTo(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::GyroReset):
            gyroReset();
            break;
            case(State::NewGyroTurnTo):
            newGyroTurnTo(currState.val1, currState.val2, currState.val3, currState.type);//(currState.val1, currState.type);
            break;
 
            case(State::SwerveBackwardR):
            swerveBackwardR(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::SwerveBackwardGyroL):
            swerveBackwardGyroL(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::SwerveBackwardGyroR):
            swerveBackwardGyroR(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::SwerveBackwardGyroLV):
            swerveBackwardGyroLV(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::SwerveBackwardGyroRV):
            swerveBackwardGyroRV(currState.val1, currState.val2, currState.val3, currState.type);
            break;
 
            case(State::TowerUp):
            towerUp(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::TowerTo):
            towerTo(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::TowerSet):
            towerSet(currState.val1);
            break;
            case(State::TowerReset):
            towerReset();
            break;
 
            case(State::ArmUp):
            armUp(currState.val1, currState.val2, currState.val3, currState.type);
            break;
            case(State::ArmSet):
            armSet(currState.val1, currState.val2);
            break;
 
            case(State::IntakeOut):
            intakeOut(currState.val1, currState.val2, currState.type);
            break;
            case(State::IntakeTime):
            intakeTime(currState.val1, currState.val2, currState.type);
            break;
            case(State::IntakeSet):
            intakeSet(currState.val1);
            break;
            default:;
        }
 
        pros::delay(10);
        index++;
    }
}

void opcontrol() 
{
    bool record = false;
 
    int motorCount = 8;  //************ MANUAL ***********
    int dataSize = motorCount * (1000 / SDUPDATEMS) * 60;
    char data[dataSize];
    
    int arraySize = (1000 / SDUPDATEMS) * 60; //*********** MANUAL ***********
    int powers[arraySize][motorCount] = {0};
 
    std::uint32_t now = pros::millis();

    bool afterAuton = false;
    int restPos = 0;
    bool hasReset = false;

    FILE* sd_file;
    //FILE* sd_file_read;
    bool fileOpen = false;
 
    std::string path = "/usd/temp.txt";
    sd_file = fopen(path.c_str(), "w");
 
    pros::Motor motors[] = {leftFront, rightFront, leftBack, rightBack, leftIntake, rightIntake, arm, tower};
 
    pros::vision_object_s_t vObject;

    //INIT VISION HERE **********************************************************
    pros::vision_signature_s_t green_c = pros::Vision::signature_from_utility(GREEN_SIG, 0, 0, 0, 0, 0, 0, 0, 0);

    int target = 0;
    int previousError = 0;
    int totalError = 0;

    while (true)
    {
        double pitch = master.get_analog(ANALOG_LEFT_Y) * 1.27f;
        double yaw = master.get_analog(ANALOG_RIGHT_X);
    
        leftFront = pitch + yaw;
        leftBack = pitch + yaw;
        rightFront = pitch - yaw;
        rightBack = pitch - yaw;

        leftIntake = (master.get_digital(DIGITAL_L1) * 127) + (master.get_digital(DIGITAL_L2) * -60) + (master.get_digital(DIGITAL_RIGHT) * -187);
        rightIntake = (master.get_digital(DIGITAL_L1) * 127) + (master.get_digital(DIGITAL_L2) * -60) + (master.get_digital(DIGITAL_RIGHT) * -187);        
 
        if (master.get_digital(DIGITAL_LEFT))
        {
            vObject = vision.get_by_sig(0, GREEN_SIG);
            if (master.get_digital(DIGITAL_B))
            {
                //vObject = vision.get_by_sig(0, GREEN_SIG);
                double yScale = 0.5f;
                double pScale = 0.5f;
                int tHeight = 100;
                double offSet = 0;

                double vYaw = (VISION_FOV_WIDTH / 2 - vObject.x_middle_coord + offSet) * yScale;
                double vPitch = (tHeight - vObject.height) * pScale;

                leftFront = vPitch - vYaw;
                leftBack = vPitch - vYaw;
                rightFront = vPitch + vYaw;
                rightBack = vPitch + vYaw;
            }
            else if (master.get_digital(DIGITAL_A))
            {
                arm.set_brake_mode(MOTOR_BRAKE_HOLD);
                for (int i = 0; i < arraySize; i++)
                {
                    for (int j = 0; j < motorCount; j++)
                    {
                        motors[j].move_velocity(powers[i][j]);
                    }
                    pros::Task::delay_until(&now, SDUPDATEMS);
                }
            }
            else if (master.get_digital(DIGITAL_X) && !fileOpen)
            {
                fputs("s ", sd_file);
                fileOpen = true;
            }
            else if (master.get_digital(DIGITAL_Y) && fileOpen)
            {
                fputs("e ", sd_file);
                fclose(sd_file);
                fileOpen = false;
 
                sd_file = fopen(path.c_str(), "r");
                fgets(data, dataSize, (FILE*)sd_file);
                fclose(sd_file);
 
                int powerRow = 0;
                int powerCol = 0;
                for (int i = 0; i < dataSize; i++)
                {
                    if (data[i] == 'e')
                        break;
                    else if (data[i] == 's')
                        continue;
    
                    else if (data[i] == ' ')
                    {
                        i++;
                        int tempPower = 0;
                        int negative = 1;
                        while (true)
                        {
                            if (data[i] != ' ' && data[i] != ';')
                            {
                                if (data[i] == '-')
                                {
                                    negative = -1;
                                }
                                else
                                {
                                    tempPower *= 10;
                                    tempPower += data[i] - 48;
                                }
                                i++;
                            }
                            else
                            {
                                tempPower *= negative;
                                powers[powerRow][powerCol] = tempPower;
                                i--;
                                powerCol++;
                                break;
                            }
                        }
                    }
                    else if (data[i] == ';')
                    {
                        powerRow++;
                        powerCol = 0;
                    }
                }
            }
        }
        else
        {
            //Tune here
            double kP = 5.5; //5.5 7.5
            double kI = 0.05;
            double kD = 4.0; //3.5 8.5
            if (master.get_digital(DIGITAL_B))
            {
                if(master.get_digital(DIGITAL_UP))
                {
                    target = 90;
                }
                else
                {
                    target = 0;
                }

                int error = imu.get_rotation() - target;
                totalError += error;
                int derivative = error - previousError;

                int motorPower = (error * kP + totalError * kI + derivative * kD); //Add values up
                leftFront = -motorPower;
                leftBack = -motorPower;
                rightFront = motorPower;
                rightBack = motorPower;

                //Since code is read from top to bottom, this will be read, 
                //then 20 miliseconds will pass before the next loop causing this value
                //To become a value 20 miliseconds ago
                previousError = error; 
                pros::delay(20);
            }
            else if (master.get_digital(DIGITAL_UP))
            {
                int desiredDeg = 1650;
                tower = (desiredDeg - tower.get_position()) * 0.16;
                hasReset = false;
            }
            else if (master.get_digital(DIGITAL_DOWN) && !towerBumper.get_value())
            {
                tower = -127;
                hasReset = false;
            }
            else
            {
                if (towerBumper.get_value() && hasReset)
                {
                    tower = (restPos - tower.get_position()) * 0.4;
                }
                else if (towerBumper.get_value())
                {
                    tower = 0;
                    tower.set_zero_position(0);
                    hasReset = true;
                }
                else
                {
                    tower = (restPos - tower.get_position()) * 0.25;
                }
            }
        
            
            if (master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2))
            {
                arm = (50 - arm.get_position()) * 0.3;
            }
            else if (master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_DOWN))
            {
                arm = (500 - arm.get_position()) * 2;
            }
            else if (master.get_digital(DIGITAL_R2) && master.get_digital(DIGITAL_DOWN))
            {
                arm = (400 - arm.get_position()) * 2;
            }
            else if (master.get_digital(DIGITAL_R1))
            {
                arm = (460 - arm.get_position()) * 2;
            }
            else if (master.get_digital(DIGITAL_R2))
            {
                arm = (370 - arm.get_position()) * 2;
            }
            else
            {
                arm = 0;
            }

            if (master.get_digital(DIGITAL_A)) //NEW
            {
                driveForwardV(100, 250, StateType::Brake);//StateType::Brake, 100, 250

                //EXPAND
                while (arm.get_position() <= 100)
                {
                    arm = 127;

                    pros::delay(1);
                }
                arm = 30;

                driveTime(-60, 300, StateType::Brake);
                while (arm.get_position() <= 200)
                {
                    arm = 127;

                    pros::delay(1);
                }
                arm = 0;
            }

            if (fileOpen)
            {
                for (int i = 0; i < motorCount - 1; i++)
                {
                    fputs((std::to_string((int)motors[i].get_actual_velocity()) + " ").c_str(), sd_file);
                }
                fputs((std::to_string((int)motors[motorCount - 1].get_actual_velocity()) + "; ").c_str(), sd_file);
            }

            pros::c::imu_gyro_s_t gyro = imu.get_gyro_rate();
            pros::c::imu_accel_s_t accel = imu.get_accel();
            pros::c::euler_s_t eu = imu.get_euler();
            pros::lcd::clear();
            pros::lcd::print(1, "Old Gyro: %f\nIMU Rotaion: %f\nIMU Gyro: {x: %f, y: %f, z: %f}\nIMU Accel: {x: %f, y: %f, z: %f}\nIMU Euler: {pitch: %f, roll: %f, yaw: %f}\n", yawGyro.get_value(), imu.get_rotation(), gyro.x, gyro.y, gyro.z, accel.x, accel.y, accel.z, eu.pitch, eu.roll, eu.yaw);

            pros::Task::delay_until(&now, SDUPDATEMS);
        }
    }
}
