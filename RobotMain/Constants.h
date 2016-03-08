// Communication Info
#define BAUD_RATE               57600

// Pin numbers
#define LEFT_MOTOR_PIN          1
#define RIGHT_MOTOR_PIN         2
#define MIDDLE_MOTOR_PIN        3
#define GYRO_PIN                4
#define SHIFTER_PIN             9

#define FOAM_BALL_ARM_PIN       5
#define RELEASER_ARM_PIN        6
#define GOLF_BALL_SERVO_PIN     7
#define FOAM_BALL_SERVO_PIN     8

// Default drive mode
#define DRIVE_MODE              Drive::robotCentric

// Controls
#define CTRL_TRANS_X            DS_TO_DB(ctrl.driver1.LSX)
#define CTRL_TRANS_Y            DS_TO_DB(ctrl.driver1.LSY)
#define CTRL_ROT                DS_TO_DB(ctrl.driver1.RSX)
#define CTRL_SHIFT              (ctrl.driver1.RTG > 20)

// Control macros
// Convert driver station data to [-1.0, 1.0]
#define DS_TO_DB(X)             ((X/100.0) - 1.0)

// Deadband macro to be written (driver station might do it)

