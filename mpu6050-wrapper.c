/* Name: mpu6050-wrapper.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <python3.5/Python.h>
#include <wiringPi.h>
#include "mpu6050/mpu6050.h"


int fd;

/**
 * Making list from array
 * @param  arr    - array
 * @param  length - array length
 * @return        python list that containing an array values
 */
static PyObject* _makeList(int *arr, unsigned char length) {
    // Create new Python list
    PyObject* list = PyList_New(0);

    // Iterate on array and adding array items in list
    for (unsigned char i = 0; i < length; i++) {
        // Transforming array item value to Python object
        PyObject* value = PyLong_FromLong(arr[i]);
        // Adding new value to list
        PyList_Append(list, value);
    }

    return list;
}

/**
 * Initialise and set the settings MPU6050
 * @param device_name - device name
 * @param baud_rate   - baud rate
 * @return            file descriptor
 */
static PyObject* init(PyObject* self, PyObject* args) {
    fd = MPU6050_Init("/dev/ttyS0", 9600);
    Py_RETURN_NONE;
}

/**
 * Getting a value of temperature registers MPU6050
 * @param fd - file descriptor
 * @return   temperature register value
 */
static PyObject* whoAmI(PyObject* self, PyObject* args) {
    int who = MPU6050_whoAmI(fd);
    return Py_BuildValue("i", who);
}

/**
 * Getting a value of temperature registers MPU6050
 * @param  self - instance
 * @param  args - function arguments
 * @return      combined (high and low) value of temperature register
 */
static PyObject* getTemp(PyObject* self, PyObject* args) {
    int temp_reg = MPU6050_getTemp(fd);
    return Py_BuildValue("i", temp_reg);
}

/**
 * Getting a value of accelerometer registers MPU6050
 * @param  self - instance
 * @param  args - function arguments
 * @return      list that containing values of accelerometer registers for X, Y and Z axises
 */
static PyObject* getAccel(PyObject* self, PyObject* args) {
    int* accel = MPU6050_getAccel(fd);
    PyObject* list = _makeList(accel, 3);
    return list;
}

/**
 * Getting a values of gyroscope registers MPU6050
 * @param  self - instance
 * @param  args - function arguments
 * @return      list that containing values of gyroscope registers for X, Y and Z axises
 */
static PyObject* getGyro(PyObject* self, PyObject* args) {
    int* gyro = MPU6050_getGyro(fd);
    PyObject* list = _makeList(gyro, 3);
    return list;
}

/**
 * Computing the temperature in degrees Celsius
 * @param  self - instance
 * @param  args - function arguments
 * @return      temperature in degrees Celsius
 */
static PyObject* countTemp(PyObject* self, PyObject* args) {
    float temp = MPU6050_countTemp(fd);
    return Py_BuildValue("f", temp);
}

static PyMethodDef mpu6050Methods[] = {
    {"init", (PyCFunction)init, METH_VARARGS, "Initialise and set the settings MPU6050"},
    {"whoAmI", (PyCFunction)whoAmI, METH_VARARGS, "Returning a value of \"whoAmI\" register MPU6050"},
    {"getTemp", (PyCFunction)getTemp, METH_VARARGS, "Getting a value of temperature registers MPU6050"},
    {"getAccel", (PyCFunction)getAccel, METH_VARARGS, "Getting a value of accelerometer registers MPU6050"},
    {"getGyro", (PyCFunction)getGyro, METH_VARARGS, "Getting a values of gyroscope registers MPU6050"},
    {"countTemp", (PyCFunction)countTemp, METH_VARARGS, "Computing the temperature in degrees Celsius"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mpu6050Module = {
    PyModuleDef_HEAD_INIT,
    "mpu6050",
    "",
    -1,
    mpu6050Methods
};

PyMODINIT_FUNC PyInit_mpu6050(void) {
    return PyModule_Create(&mpu6050Module);
}
