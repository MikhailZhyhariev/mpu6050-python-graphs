/* Name: mpu6050_low.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wiringSerial.h>
#include "mpu6050.h"
#include "mpu6050_constants.h"


/**
 * Initialise and set the settings MPU6050
 * @param device - device name
 * @param baud   - baud rate
 */
int MPU6050_Init(char* device, int baud) {
    // Getting file descriptor of the device
    return serialOpen(device, baud);
}

/**
 * Getting a value of "whoAmI" register MPU6050
 * @return  "whoAmI" register value
 */
unsigned char MPU6050_whoAmI(int fd) {
    // Reading data from the "whoAmI" register
    return serialGetchar(fd);
}

/**
 * Getting a value of temperature registers MPU6050
 * @return  temperature register value
 */
int MPU6050_getTemp(int fd) {
    // Getting value of temperature register
    int* temp_reg = MPU6050_dataRecovery(fd);
    if (temp_reg[0] != TEMP) return -33000;
    return temp_reg[1];
}

/**
 * Getting a value of accelerometer registers MPU6050
 * @return  the array of accelerometer registers values
 */
int* MPU6050_getAccel(int fd) {
    // Getting values of accelerometer registers for X, Y and Z axises
    // return _MPU6050_getArrValues(ACCEL_XOUT_H, 3);
    int* accel = MPU6050_dataRecovery(fd);
    if (accel[0] != ACCEL) return NULL;

    int* ret = (int *)malloc(sizeof(int) * 3);
    for (unsigned char i = 0; i < 3; i++) {
        ret[i] = accel[i+1];
    }

    free(accel);
    return ret;
}

/**
 * Getting a value of gyroscope registers MPU6050
 * @return  the array of gyroscope registers values
 */
int* MPU6050_getGyro(int fd) {
    // Getting values of gyroscope registers for X, Y and Z axises
    int* gyro = MPU6050_dataRecovery(fd);
    if (gyro[0] != GYRO) return NULL;

    int* ret = (int *)malloc(sizeof(int) * 3);
    for (unsigned char i = 0; i < 3; i++) {
        ret[i] = gyro[i+1];
    }

    free(gyro);
    return ret;
}
