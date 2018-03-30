/* Name: main.c
 * Author: Zhyhariev Mikhail
 * License: MIT
 */

#include <python3.5/Python.h>
#include <wiringPi.h>
#include "mpu6050/mpu6050.h"

// structure that containing all measured variables
mpu6050 mpu;

/**
 * [Making list from array]
 * @param  arr    [array]
 * @param  length [array length]
 * @return        [python list that containing an array values]
 */
static PyObject* _makeList(unsigned int *arr, unsigned char length) {
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
 * [Initialise and set the settings MPU6050]
 * @param  self [instance]
 * @param  args [function arguments]
 * @return      [NONE]
 */
static PyObject* init(PyObject* self, PyObject* args) {
    // Initialise wiringPi
    wiringPiSetup();

    // Initialise and set the settings MPU6050 module. Get MPU6050 file descriptor
    mpu.fd = MPU6050_Init();

    Py_RETURN_NONE;
}

/**
 * [Returning a value of "whoAmI" register MPU6050]
 * @param  self [instance]
 * @param  args [function arguments]
 * @return      ["whoAmI" register value]
 */
static PyObject* whoAmI(PyObject* self, PyObject* args) {
    MPU6050_whoAmI(&mpu);
    return Py_BuildValue("i", mpu.who);
}

/**
 * [Getting a value of temperature registers MPU6050]
 * @param  self [instance]
 * @param  args [function arguments]
 * @return      [combined (high and low) value of temperature register]
 */
static PyObject* getTemp(PyObject* self, PyObject* args) {
    MPU6050_getTemp(&mpu);
    return Py_BuildValue("i", mpu.temp_reg);
}

/**
 * [Getting a value of accelerometer registers MPU6050]
 * @param  self [instance]
 * @param  args [function arguments]
 * @return      [list that containing values of accelerometer registers for X, Y and Z axises]
 */
static PyObject* getAccel(PyObject* self, PyObject* args) {
    MPU6050_getAccel(&mpu);

    unsigned int values[] = {mpu.accel_x, mpu.accel_y, mpu.accel_z};
    PyObject* list = _makeList(values, 3);

    return list;
}

/**
 * [Getting a values of gyroscope registers MPU6050]
 * @param  self [instance]
 * @param  args [function arguments]
 * @return      [list that containing values of gyroscope registers for X, Y and Z axises]
 */
static PyObject* getGyro(PyObject* self, PyObject* args) {
    MPU6050_getGyro(&mpu);

    unsigned int values[] = {mpu.gyro_x, mpu.gyro_y, mpu.gyro_z};
    PyObject* list = _makeList(values, 3);

    return list;
}

/**
 * [Computing the temperature in degrees Celsius]
 * @param  self [instance]
 * @param  args [function arguments]
 * @return      [temperature in degrees Celsius]
 */
static PyObject* countTemp(PyObject* self, PyObject* args) {
    MPU6050_countTemp(&mpu);
    return Py_BuildValue("f", mpu.temp);
}

static PyMethodDef helloMethods[] = {
    {"init", (PyCFunction)init, METH_VARARGS, "Initialise and set the settings MPU6050"},
    {"whoAmI", (PyCFunction)whoAmI, METH_VARARGS, "Returning a value of \"whoAmI\" register MPU6050"},
    {"getTemp", (PyCFunction)getTemp, METH_VARARGS, "Getting a value of temperature registers MPU6050"},
    {"getAccel", (PyCFunction)getAccel, METH_VARARGS, "Getting a value of accelerometer registers MPU6050"},
    {"getGyro", (PyCFunction)getGyro, METH_VARARGS, "Getting a values of gyroscope registers MPU6050"},
    {"countTemp", (PyCFunction)countTemp, METH_VARARGS, "Computing the temperature in degrees Celsius"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef helloModule = {
    PyModuleDef_HEAD_INIT,
    "mpu6050",
    "",
    -1,
    helloMethods
};

PyMODINIT_FUNC PyInit_mpu6050(void) {
    return PyModule_Create(&helloModule);
}
