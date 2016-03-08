// Communication Info
#define BAUD_RATE               57600

// Pin numbers
#define LEFT_MOTOR_PIN          1
#define RIGHT_MOTOR_PIN         2
#define MIDDLE_MOTOR_PIN        3
#define FOAM_BALL_ARM_PIN       4
#define RELEASER_ARM_PIN        5
#define GOLF_BALL_SERVO_PIN     6
#define FOAM_BALL_SERVO_PIN     7

// Default drive mode
#define DRIVE_MODE              Drive::robotCentric

// Controls
#define CTRL_TRANS_X            DS_TO_DB(ctrl.LSX)
#define CTRL_TRANS_Y            DS_TO_DB(ctrl.LSY)
#define CTRL_ROT                DS_TO_DB(ctrl.RSX)

// Control macros
// Convert driver station data to [-1.0, 1.0]
#define DS_TO_DB(X)             ((X/255.0) - 1.0)
// Deadband macro to be written
