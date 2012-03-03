#include <boost/python.hpp>
#include <string>
#include "numpy_to_blitz.hpp"

using namespace std;

BOOST_PYTHON_MODULE(numpy_to_blitz) {
    using namespace boost::python;

    numeric::array::set_module_and_type("numpy", "ndarray");
    def("setArray1D", set_array<double, 1>);
    def("setArray2D", set_array<double, 2>);
}
