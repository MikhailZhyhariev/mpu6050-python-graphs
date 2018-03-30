from distutils.core import setup, Extension

mpu6050 = Extension('mpu6050',
                     sources = ['mpu6050/mpu6050_low.c',
                                'mpu6050/mpu6050_high.c',
                                'mpu6050-wrapper.c'],
                     libraries=['wiringPi', 'pthread'])

setup(name = 'mpu6050',
      version = '1.0',
      description = 'This is a demo package',
      ext_modules = [mpu6050])
