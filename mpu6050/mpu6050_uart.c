/* Name: mpu6050_uart.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <stdlib.h>
#include <wiringSerial.h>
#include <stdio.h>
#include "mpu6050.h"

/**
 * Receiving two bytes using UART interface
 * @param  fd - file descriptor
 * @return    received two-bytes data
 */
int MPU6050_twoBytesReceive(int fd) {
    int data = serialGetchar(fd) << 8;
    data |= serialGetchar(fd);

    return data;
}

/**
 * Receiving an array of two-byte digits using UART interface
 * @param  fd  - file descriptor
 * @param  len - length of array
 * @return     an array of two-byte digits
 */
int* MPU6050_receiveArray(int fd, unsigned char len) {
    int *arr = (int *)malloc(len * sizeof(int));

    for (unsigned char i = 0; i < len; i++) {
        int sign = MPU6050_twoBytesReceive(fd);
        arr[i] = MPU6050_twoBytesReceive(fd);
        if (sign == MINUS) arr[i] *= -1;
    }
    return arr;
}

/**
 * Receiving MPU6050 data
 * @param  fd - file descriptor
 * @return    an array of two-byte digits
 */
int* MPU6050_dataRecovery(int fd) {
    // Data array length
    unsigned char len = 3;
    // Array that contains identifier and data
    int* data = (int *)malloc((len + 1) * sizeof(int));

    // Receiving "start" identifier
    if (MPU6050_twoBytesReceive(fd) != START) return NULL;

    // Receiving data identifier
    int id = MPU6050_twoBytesReceive(fd);
    switch (id) {
        // If it data from accelerometer receiving "accel" identifier
        case ACCEL:
            data[0] = ACCEL;
            break;

        // If it data from accelerometer receiving "gyro" identifier
        case GYRO:
            data[0] = GYRO;
            break;

        // If it data from accelerometer receiving "temp" identifier
        case TEMP:
            // Set length is one because the temperature is one two-bytes digit
            len = 1;
            data[0] = TEMP;
            break;
    }

    // Receiving data in temp array and adding to main data array without corrupting identifier
    int* temp = MPU6050_receiveArray(fd, len);
    for (unsigned char i = 0; i < len; i++) {
        data[i+1] = temp[i];
    }
    free(temp);

    return data;
}
