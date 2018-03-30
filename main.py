from time import sleep
import mpu6050

def getValues(str, func):
    print(str, end=' ')
    print(*func())

mpu6050.init()

who = mpu6050.whoAmI()
print(who)

while True:
    getValues('GYRO: ', mpu6050.getGyro)
    sleep(0.25)
    getValues('ACCEL:', mpu6050.getAccel)
    sleep(0.25)
