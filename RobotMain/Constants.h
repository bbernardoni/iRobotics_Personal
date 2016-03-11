// Communication Info
#define BAUD_RATE               57600

// Pin numbers
#define LEFT_MOTOR_PIN          10
#define RIGHT_MOTOR_PIN         2
#define MIDDLE_MOTOR_PIN        3
#define GYRO_PIN                4
#define SHIFTER_PIN             9
                    
#define RELEASER_ARM_PIN        6
#define FOAM_BALL_ARM_PIN       5
#define FOAM_BALL_SERVO_PIN     8

#define DISPENSER_MOTOR_PIN     11
#define GOLF_BALL_SERVO_PIN     7
#define SORTER_SERVO_PIN        13
#define SWING_DOOR_PIN          14

// Default drive mode
#define DRIVE_MODE              Drive::fieldCentric

// Controls
#define CTRL_TRANS_X            DS_TO_DB(ctrl.driver1.LSX)
#define CTRL_TRANS_Y            DS_TO_DB(ctrl.driver1.LSY)
#define CTRL_ROT                DS_TO_DB(ctrl.driver1.RSX)
#define CTRL_SHIFT              (ctrl.driver1.RTG > 20)

#define CTRL_RELEASE_ARM        (ctrl.driver2.rightBumper)
#define CTRL_FOAM_BALL_ARM      (ctrl.driver2.leftBumper)

#define CTRL_DISPENSER_MOTOR    (ctrl.driver2.x)
#define CTRL_FOAM_BALL_SERVO    (ctrl.driver2.back)

#define CTRL_SWING_DOOR         (ctrl.driver2.b)


//colors 
#define YELLOW                  (ctrl.driver1.dUP)
#define RED                     (ctrl.driver1.dRIGHT)
#define GREEN                   (ctrl.driver1.dDOWN)
#define WHITE                   (ctrl.driver1.dLEFT)


// Servo Posistions
#define SORTER_NEUTRAL_POSN     60
#define SORTER_ACCEPT_POSN      30
#define SORTER_REJECT_POSN      130
#define GOLF_SCORE_POSN         180
#define GOLF_HOLD_POSN          0
#define FOAM_SCORE_POSN         180
#define FOAM_HOLD_POSN          0

// Control macros
// Convert driver station data to [-1.0, 1.0]
#define DS_TO_DB(X)             ((X/100.0) - 1.0)

// Deadband macro to be written (driver station might do it)

