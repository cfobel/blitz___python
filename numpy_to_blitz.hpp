#ifndef PY_TO_BLITZ_H
#define PY_TO_BLITZ_H

#include <iostream>
#include <algorithm>
#include <exception>
#include <boost/format.hpp>
#include <boost/python/numeric.hpp>
#include <boost/python/tuple.hpp>
#include <numpy/noprefix.h>
#include "Python.h"
#include "blitz/array.h"

using namespace blitz;
using namespace std;
typedef boost::format _f;
using namespace boost;
using namespace boost::python;
using boost::python::extract;
using namespace boost::python::numeric;


// Functions to demonstrate extraction
template<class T, int N>
Array<T, N> numpy_to_blitz(boost::python::numeric::array &data) {
    // Access a built-in type (an array)
    boost::python::numeric::array a = data;
    TinyVector<int, N> shape(0);
    TinyVector<int, N> strides(0);
    const int T_size = sizeof(T);

    // Need to extract array elements because their type is unknown
    const boost::python::tuple &shape_tuple = extract<boost::python::tuple>(data.attr("shape"));
    const boost::python::tuple &strides_tuple = extract<boost::python::tuple>(data.attr("strides"));
    size_t ndims = len(shape_tuple);
    if(ndims != N) {
        throw std::runtime_error((_f("Invalid dimensions - expected=%d  actual=%d")
                % N % ndims).str());
    }

    for (int i = 0; i < N; ++i) {
        shape[i] = extract<size_t>(shape_tuple[i]);
        strides[i] = extract<size_t>(strides_tuple[i]) / T_size;
        cout << _f("shape[%d]=%d  strides[%d]=%d")
                % i % i % shape[i] % strides[i] << endl;
    }
    double *data_ptr = static_cast<double*> PyArray_DATA(a.ptr());
    Array<T, N> temp_blitz((T*) data_ptr, shape, strides, neverDeleteData);
    return temp_blitz;
}

template<class T, int N>
void set_array(boost::python::numeric::array &data, T value) {
    Array<T, N> temp_blitz = numpy_to_blitz<T, N>(data);
    temp_blitz = value;
    cout << temp_blitz << endl;
}

#endif // PY_TO_BLITZ_H
