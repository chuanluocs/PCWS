#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <numpy/ndarrayobject.h>
#include "../WeightedMinHash.h"

static PyObject *convert_2d_vector(size_t dim0, size_t dim1, vector<vector<double>> &data_vec)
{
    npy_intp dims[2] = {(npy_intp)dim0, (npy_intp)dim1};
    PyObject *arr = PyArray_SimpleNew(2, dims, NPY_DOUBLE);
    double *data = (double *)PyArray_DATA(arr);
    for (size_t i = 0; i < dim0; i++)
    {
        memcpy(data + i * dim1, data_vec[i].data(), dim1 * sizeof(double));
    }
    return arr;
}

static vector<vector<double>> convert_to_2d_vector(PyObject *data_arr)
{
    // Assert/check the size of data_arr
    npy_intp *dims = PyArray_DIMS(data_arr);
    vector<vector<double>> vec(dims[0], vector<double>(dims[1]));
    for (int i = 0; i < dims[0]; i++)
    {
        memcpy(vec[i].data(), PyArray_GETPTR1(data_arr, i), dims[1] * sizeof(double));
    }
    return vec;
}

static PyObject *pcws(PyObject *self, PyObject *args)
{
    int dimension_num, seed;
    PyObject *data_arr;
    PyArg_ParseTuple(args, "iiO", &dimension_num, &seed, &data_arr);
    data_arr = PyArray_FromAny(data_arr, PyArray_DescrFromType(NPY_DOUBLE), 2, 2, NPY_ENSUREARRAY | NPY_ARRAY_C_CONTIGUOUS | NPY_ALIGNED, NULL);

    vector<vector<double>> data = convert_to_2d_vector(data_arr);

    WeightedMinHash wmh(data, dimension_num, seed);
    ResultTuple ret = wmh.pcws();

    return PyTuple_Pack(3,
                        convert_2d_vector(ret.fingerprints_k.size(), dimension_num, ret.fingerprints_k),
                        convert_2d_vector(ret.fingerprints_y.size(), dimension_num, ret.fingerprints_y),
                        PyFloat_FromDouble(ret.elapsed));
}

static PyMethodDef PcwsMethods[] = {
    {"pcws", pcws, METH_VARARGS, "PCWS"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "pcws", /* name of module */
    NULL,   /* module documentation */
    -1,
    PcwsMethods};

PyMODINIT_FUNC PyInit_pcws(void)
{
    import_array();
    return PyModule_Create(&spammodule);
}