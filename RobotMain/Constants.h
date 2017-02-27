// Pin numbers
#define LEFT_MOTOR_PIN          2
#define RIGHT_MOTOR_PIN         5
#define MIDDLE_MOTOR_PIN        3
#define GYRO_PIN                53
#define SHIFTER_PIN             13
                    
#define RELEASER_ARM_PIN        11
#define FOAM_BALL_ARM_PIN       12
#define FOAM_BALL_SERVO_PIN     10

#define DISPENSER_MOTOR_PIN     8
#define GOLF_BALL_SERVO_PIN     7
#define SORTER_SERVO_PIN        9
#define SWING_DOOR_PIN          6

// Default drive mode
#define DRIVE_MODE              Drive::robotCentric

// Controls
#define CTRL_TRANS_X            DS_TO_DB(ctrl.driver1.LSX)
#define CTRL_TRANS_Y            DS_TO_DB(ctrl.driver1.LSY)
#define CTRL_ROT                DS_TO_DB(ctrl.driver1.RSX)
#define CTRL_SHIFT              (ctrl.driver1.RTG > 20)

#define CTRL_GYRO_RESET         (ctrl.driver1.a)
#define CTRL_GYRO_ROT_CCW       (ctrl.driver1.leftBumper)
#define CTRL_GYRO_ROT_CW        (ctrl.driver1.rightBumper)

#define CTRL_RELEASE_ARM        DS_TO_DB(ctrl.driver2.LSY)
#define CTRL_FOAM_BALL_ARM      (ctrl.driver2.leftBumper)
#define CTRL_FOAM_BALL_SCORE    (ctrl.driver2.back)

#define CTRL_ROBOT_RED          (ctrl.driver2.dRight)
#define CTRL_ROBOT_GREEN        (ctrl.driver2.dDown)
#define CTRL_ROBOT_WHITE        (ctrl.driver2.dLeft)
#define CTRL_ROBOT_YELLOW       (ctrl.driver2.dUp)

#define CTRL_DISPENSER_MOTOR    (ctrl.driver2.x)
#define CTRL_GOLF_BALL_SCORE    (ctrl.driver2.start)

#define CTRL_SWING_DOOR_UP      (ctrl.driver2.y)
#define CTRL_SWING_DOOR_DOWN    (ctrl.driver2.b)

// Servo Posistions
#define SORTER_NEUTRAL_POSN     90
#define SORTER_ACCEPT_POSN      167
#define SORTER_REJECT_POSN      55

#define GOLF_SCORE_POSN         10
#define GOLF_HOLD_POSN          170

#define FOAM_SCORE_POSN         70
#define FOAM_HOLD_POSN          160

#define DISPENSE_SPEED          95

#define SWING_DOOR_UP_SPEED     120
#define SWING_DOOR_DOWN_SPEED   60

// Times
#define GOLF_HOLD_TIME          5000
#define FOAM_HOLD_TIME          4000
#define SORTER_DWELL_TIME       2000
#define SORTER_ACCEPT_TIME      2000
#define SORTER_REJECT_TIME      2000

// Control macros
// Convert driver station data to [-1.0, 1.0]
#define DS_TO_DB(X)             ((X/100.0) - 1.0)

//Sorter Thresholds
#define PROX_CLOSE              20000

//RGB values for red, green, white, yellow reference colors
#define RED_R                   4800
#define RED_G                   1400
#define RED_B                   1400

#define GREEN_R                 1300
#define GREEN_G                 1850
#define GREEN_B                 1450

#define WHITE_R                 15000
#define WHITE_G                 15300
#define WHITE_B                 15000

#define YELLOW_R                15000
#define YELLOW_G                12000
#define YELLOW_B                5000


//enum Color { red, green, white, yellow };


// Deadband macro to be written (driver station might do it)

