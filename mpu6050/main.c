#include <stdio.h>
#include <wiringPi.h>
#include "mpu6050.h"
#include "mpu6050_constants.h"

int main() {
    wiringPiSetup();

    mpu6050 mpu;
    mpu.fd = MPU6050_Init();

    long int i = 0;
    while (1) {
        printf("%li\n", i++);

        MPU6050_getAccel(&mpu);
        printf("Accelerometer\n");
        printf("X:%i Y:%i Z:%i\n", mpu.accel_x, mpu.accel_y, mpu.accel_z);

        MPU6050_getGyro(&mpu);
        printf("Gyroscope\n");
        printf("X:%i Y:%i Z:%i\n", mpu.gyro_x, mpu.gyro_y, mpu.gyro_z);

        delay(100);
    }

    return 0;
}
