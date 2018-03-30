#include <python3.5/Python.h>
#include <stdio.h>


static PyObject* hello(PyObject* self, PyObject* args) {

    PyObject *listObj;
    if (!PyArg_ParseTuple(args, "s", listObj)) return NULL;

    printf("Hello. I'm work!\n");

    Py_RETURN_NONE;
}

static char hello_docs[] = "add( ): add all elements of the list\n";

static PyMethodDef helloMethods[] = {
    {"say hello", (PyCFunction)hello, METH_VARARGS, hello_docs},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC inithello(void) {
    Py_InitModule3("hello", helloMethods,
                   "just says hello.");
}
