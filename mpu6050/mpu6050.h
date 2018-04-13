/* Name: mpu6050.h
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#ifndef MPU_6050
#define MPU_6050

// File descriptor
int fd;

/**
 * LOW LEVEL FUNCTION
 */

/**
 * Initialise and set the settings MPU6050
 * @param device - device name
 * @param baud   - baud rate
 * @return       file descriptor
 */
int MPU6050_Init(char* device, int baud);

/**
 * Getting a value of "whoAmI" register MPU6050
 * @param fd - file descriptor
 * @return   "whoAmI" register value
 */
unsigned char MPU6050_whoAmI(int fd);

/**
 * Getting a value of temperature registers MPU6050
 * @param fd - file descriptor
 * @return   temperature register value
 */
int MPU6050_getTemp(int fd);

/**
 * Getting a value of accelerometer registers MPU6050
 * @param fd - file descriptor
 * @return   the array of accelerometer registers values
 */
int* MPU6050_getAccel(int fd);

/**
 * Getting a value of gyroscope registers MPU6050
 * @param fd - file descriptor
 * @return   the array of gyroscope registers values
 */
int* MPU6050_getGyro(int fd);


/**
 * HIGH LEVEL FUNCTION
 */

/**
 * Computing the temperature in degrees Celsius
 * @return      temperature in degrees Celsius
 */
float MPU6050_countTemp(int fd);


/**
 * UART FUNCTION
 */

// Identifiers
#define START 33000

#define MINUS 33001
#define PLUS  33002

#define ACCEL 33003
#define GYRO  33004
#define TEMP  33005

/**
 * Receiving two bytes using UART interface
 * @param  fd - file descriptor
 * @return    received two-bytes data
 */
int MPU6050_twoBytesReceive(int fd);

/**
 * Receiving an array of two-byte digits using UART interface
 * @param  fd  - file descriptor
 * @param  len - length of array
 * @return     an array of two-byte digits
 */
int* MPU6050_receiveArray(int fd, unsigned char len);

/**
 * Receiving MPU6050 data
 * @param  fd - file descriptor
 * @return    an array of two-byte digits
 */
int* MPU6050_dataRecovery(int fd);


#endif
