#ifndef CRPROPA_BINDINGS_VECTOR3_H
#define CRPROPA_BINDINGS_VECTOR3_H

#include <CRPropa.h>

#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>


namespace crpropa_bindings{

	using namespace std;
	using namespace pybind11::literals;
	namespace py = pybind11;
	namespace cp = crpropa;

	template<typename T>
	void Vector3_binder(py::module &m, string const &typestring){
		string pyclassname = "Vector3" + typestring;
		if(typestring=="double")
			pyclassname = "Vector3d";
		else if (typestring=="float")
			pyclassname = "Vector3f";

		py::class_<cp::Vector3<T>>(m, pyclassname.c_str(), py::buffer_protocol())
			.def(py::init<>())
			.def(py::init<const cp::Vector3<double>&>())
			.def(py::init<const cp::Vector3<float>&>())
			.def(py::init<const T &, const T &, const T &>())
			.def(py::init<T>())
			// functions:
			.def("setX", &cp::Vector3<T>::setX)
			.def("setY", &cp::Vector3<T>::setY)
			.def("setZ", &cp::Vector3<T>::setZ)
			.def("setXYZ", &cp::Vector3<T>::setXYZ)
			.def("setR", &cp::Vector3<T>::setR)
			.def("setRThetaPhi", &cp::Vector3<T>::setRThetaPhi)
			.def("getX", &cp::Vector3<T>::getX)
			.def("getY", &cp::Vector3<T>::getY)
			.def("getZ", &cp::Vector3<T>::getZ)
			.def("getR", &cp::Vector3<T>::getR)
			.def("getR2", &cp::Vector3<T>::getR2)
			.def("getPhi", &cp::Vector3<T>::getPhi)
			.def("getTheta", &cp::Vector3<T>::getTheta)
			.def("getUnitVector", &cp::Vector3<T>::getUnitVector)
			.def("getUnitVectorTheta", &cp::Vector3<T>::getUnitVectorTheta)
			.def("getUnitVectorPhi", &cp::Vector3<T>::getUnitVectorPhi)
			.def("getAngleTo", &cp::Vector3<T>::getAngleTo)
			.def("isParallelTo", &cp::Vector3<T>::isParallelTo)
			.def("getDistanceTo", &cp::Vector3<T>::getDistanceTo)
			.def("getParallelTo", &cp::Vector3<T>::getParallelTo)
			.def("getPerpendicularTo", &cp::Vector3<T>::getPerpendicularTo)
			.def("getRotated", &cp::Vector3<T>::getRotated)
			.def("clip", &cp::Vector3<T>::clip)
			.def("abs", &cp::Vector3<T>::abs)
			.def("floor", &cp::Vector3<T>::floor)
			.def("ceil", &cp::Vector3<T>::ceil)
			.def("min", &cp::Vector3<T>::min)
			.def("max", &cp::Vector3<T>::max)
			.def("dot", &cp::Vector3<T>::dot)
			.def("cross", &cp::Vector3<T>::cross)
			.def("getDescription", &cp::Vector3<T>::getDescription)
			// python side functions:
			.def("__repr__", &cp::Vector3<T>::getDescription)
			.def("__doc__", [](const cp::Vector3<T>& c){return "\
Allows accessing and changing the elements x, y, z directly or  through the\n\
corresponding get and set methods.\n\
\n\
Angle definitions are\n\
phi [-pi, pi]: azimuthal angle in the x-y plane, 0 pointing in x-direction\n\
theta [0, pi]: zenith angle towards the z axis, 0 pointing in z-direction";
			})
			.def("getDict", [](const cp::Vector3<T>& c) -> const py::dict {
				return py::dict(
					"x"_a=c.x,
					"y"_a=c.y,
					"z"_a=c.z
				);
			})
			.def("__len__", [](const cp::Vector3<T>& c){return 3;})
			.def("__getitem__", [](cp::Vector3<T>& c, const int& idx){return c.data[idx];})
			.def("__setitem__", [](cp::Vector3<T>& c, const int& idx, T val){c.data[idx]=val;})
			// needed for numpy array compability and other buffer stuff (like very fast no copy instructions)
			.def_buffer([](cp::Vector3<T>& c) -> py::buffer_info {
				return py::buffer_info(
					c.data,  // pointer to buffer
					sizeof(T),  // size of one scalar
					py::format_descriptor<T>::format(),  // python struct-style format descriptor
					1,  // number of dimensions
					{3},  // buffer dimensions
					{sizeof(T)}  // strides (in bytes) for each index
				);
			})
			// operators
			.def(py::self == py::self)
			.def(py::self + py::self)
			.def(py::self + T())
			.def(py::self - py::self)
			.def(py::self - T())
			.def(py::self * py::self)
			.def(py::self * T())
			.def(py::self / py::self)
			.def(py::self / T())
			.def(py::self % py::self)
			.def(py::self % T())
			.def(py::self += py::self)
			.def(py::self += T())
			.def(py::self -= py::self)
			.def(py::self -= T())
			.def(py::self *= py::self)
			.def(py::self *= T())
			.def(py::self /= py::self)
			.def(py::self /= T())
			.def(py::self %= py::self)
			.def(py::self %= T())
			// .def(py::self = py::self)
			// .def(py::self = T());
			// variables:
			.def_readwrite("x", &cp::Vector3<T>::x)
			.def_readwrite("y", &cp::Vector3<T>::y)
			.def_readwrite("z", &cp::Vector3<T>::z)

			;
	}


}

#endif