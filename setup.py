from distutils.core import setup, Extension

mpu6050 = Extension('mpu6050',
                     sources = ['mpu6050/mpu6050_low.c',
                                'mpu6050/mpu6050_high.c',
                                'mpu6050-wrapper.c'],
                     libraries=['wiringPi', 'pthread'])

setup(name = 'mpu6050',
      version = '1.1',
      description = 'Module for MPU6050',
      ext_modules = [mpu6050])
