from time import sleep
import socket
import mpu6050

mpu6050.init()

with socket.create_connection(("192.168.1.101", 10001)) as sock:
    index = 0
    while True:
        accel_x, accel_y, accel_z = mpu6050.getAccel()
        sock.sendall('{0} {1} {2} {3}'.format(accel_x, accel_y, accel_z, index).encode())

        index += 1
        print('Sending data...')

        sleep(0.25)
