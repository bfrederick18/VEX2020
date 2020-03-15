#define LEFT_FRONT_MOTOR_PORT 11
#define RIGHT_FRONT_MOTOR_PORT 19
#define LEFT_BACK_MOTOR_PORT 12
#define RIGHT_BACK_MOTOR_PORT 20
#define LEFT_INTAKE_MOTOR_PORT 8
#define RIGHT_INTAKE_MOTOR_PORT 9
#define ARM_MOTOR_PORT 2
#define TOWER_MOTOR_PORT 10
#define VISION_PORT 18
#define TOWER_BUMPER_PORT 1 //ADI
#define YAW_GYRO_PORT 2 //ADI
#define TILT_ENCODER_TOP_PORT 7 //ADI
#define TILT_ENCODER_BOTTOM_PORT 8 //ADI
#define IMU_PORT 14 
//3 4 5 6 7
//13 15 16 17 18

#define autonNumm 0
#define maxCount 4

#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

#define PID_INTEGRAL_LIMIT  50
#define PID_SENSOR_SCALE    0.25f
#define PID_MOTOR_SCALE     -1

#define FROMSD 0
#define SDUPDATEMS 100

#define GREEN_SIG 1
#define ORANGE_SIG 2
#define PURPLE_SIG 3