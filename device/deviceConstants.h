#ifndef DEVICE_CONSTANTS_H
#define DEVICE_CONSTANTS_H

/** Device header .*/
#define BATTERY_DEVICE_HEADER                      'b'

#define ROBOT_CONFIG_DEVICE_HEADER                 'c'

#define ADC_DEVICE_HEADER                          'd'

#define END_MATCH_DETECTOR_DEVICE_HEADER           'e'

// The EEPROM DEVICE HEADER

#define EEPROM_DEVICE_HEADER                       'E'

#define FILE_DEVICE_HEADER                         'f'

#define AIR_CONDITIONING_DEVICE_HEADER             'g'

#define LOG_DEVICE_HEADER                          'G'

// 'h' for Help
#define SYSTEM_DEBUG_DEVICE_HEADER                 'h'

/** Command header for led */
#define LED_DEVICE_HEADER                          'H'

/** Command to debug the I2C Master. */
#define I2C_MASTER_DEBUG_DEVICE_HEADER             'I'

/** Command to debug the I2C Slave. */
#define I2C_SLAVE_DEBUG_DEVICE_HEADER              'i'

/** Command to debug the dispatchers. */
#define DATA_DISPATCHER_DEVICE_HEADER              'j'

/** Command header to handle the Motion Processing Unit "MPU" */
#define MPU_DEVICE_HEADER                          'J'

/** Command to ping */
#define COMMAND_PING_DISPATCHER_INDEX               'p'             

/** Command to manipulate the clock. */
#define CLOCK_DEVICE_HEADER                        'k'

/** Command to handle the Kinematics. */
#define KINEMATICS_HEADER                          'K'

/** Laser Beacon Device Header. */
#define LASER_BEACON_DEVICE_HEADER                 'l'

/**
 * Command header for LCD Device.
 */
#define LCD_DEVICE_HEADER                          'L'

/**
 * Defines the header char used to identify the motion Device (high level).
 */
#define MOTION_DEVICE_HEADER                       'M'

/**
 * Defines the header char used to identify the motor Device (low level).
 */
#define MOTOR_DEVICE_HEADER                        'm'

/**
 * Header char of Trajectory device : 'n' for 'navigation.
 */
#define TRAJECTORY_DEVICE_HEADER                   'n'

/**
 * Header char of Navigation device
 */
#define NAVIGATION_DEVICE_HEADER                   'N'

#define PID_DEVICE_HEADER                          'p'

/** TODO : Collision with I2C PID */
#define PIN_DEVICE_HEADER                          'P'

#define PLL_DEVICE_HEADER                          'q' 

#define PERIOD_METER_HEADER                        'Q'

#define BEACON_RECEIVER_DEVICE_HEADER              'r'

#define RELAY_DEVICE_HEADER                        'R'

/** Header for the servo device .*/
#define SERVO_DEVICE_HEADER                        's'

/** Header for System Device. */
#define SYSTEM_DEVICE_HEADER                       'S'

// The TEMPERATURE SENSOR DEVICE HEADER

/** Header for Temperature Device. */
#define TEMPERATURE_SENSOR_DEVICE_HEADER           'T'

/** Header for Test Device. */
#define TEST_DEVICE_HEADER                         't'

/** Serial debug (U for "Uart"). */
#define SERIAL_DEBUG_DEVICE_HEADER                 'u'

/** Common Beacon device header. */
#define COMMON_BEACON_DEVICE_HEADER                'U'

/** Header for Test2 Device. */
#define TEST2_DEVICE_HEADER                        'u'

#define TIMER_DEVICE_HEADER                        'V'

#define CODERS_DEVICE_HEADER                       'w'

/** Reserved to clear buffer. */
#define NOT_TOO_USE_1                               'z'

/** Reserved to clear deeply the buffer. */
#define NOT_TOO_USE_2                               'Z'

#define STRATEGY_DEVICE_HEADER                     'Y'

#define START_MATCH_DEVICE_HEADER                   '!'

#define SONAR_DEVICE_HEADER                        '<'

#define ROBOT_SONAR_DETECTOR_DEVICE_HEADER         '#'

#define PLIERS_DEVICE_2011_HEADER                  '_'

#define ARM_DEVICE_2012_HEADER                     '|'

#define MOTION_SIMULATION_DEVICE_HEADER            '/' 

#define ROBOT_INFRARED_DETECTOR_DEVICE_HEADER      '>'

#endif
