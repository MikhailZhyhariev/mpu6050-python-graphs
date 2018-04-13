/* Name: mpu6050_high.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <stdlib.h>
#include "mpu6050.h"

/**
 * Computing the temperature in degrees Celsius
 * @return      temperature in degrees Celsius
 */
float MPU6050_countTemp(int fd) {
    // Getting the values of the temperature register
    int temp_reg = MPU6050_getTemp(fd);
    if (temp_reg == -33000) return -273;

    // Return the temperature in degrees Celsius
    return temp_reg / 340 + 36.53;
}
