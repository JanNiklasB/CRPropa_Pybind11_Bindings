#ifndef CRPROPA_BINDINGS_VECTOR3_H
#define CRPROPA_BINDINGS_VECTOR3_H

#include <CRPropa.h>

#include <string>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>
#include <pybind11/operators.h>

namespace crpropa_bindings{

	using namespace std;
	using namespace pybind11::literals;
	namespace py = pybind11;
	namespace cp = crpropa;

	template <typename T>
	class Vector3Trampoline : public cp::Vector3<T> {
		public:
			using cp::Vector3<T>::Vector3;
	};

	template<typename T>
	void Vector3_binder(py::module &m, string const &typestring){
		string pyclassname = "Vector3" + typestring;
		if(typestring=="double")
			pyclassname = "Vector3d";
		else if (typestring=="float")
			pyclassname = "Vector3f";

		auto cl = py::class_<Vector3Trampoline<T>>(m, pyclassname.c_str(), py::buffer_protocol());
		cl.def(py::init<>());
		// cl.def(py::init<const cp::Vector3<double>&>());
		// cl.def(py::init<const cp::Vector3<float>&>());
		cl.def(py::init<const T &, const T &, const T &>());
		cl.def(py::init<T>());
		// pybind11 automatically casts any iterable into a std::vector, so it is enough to add a std::vector constructor
		cl.def(py::init([](const std::vector<T> &vec){
			if (vec.size() != 3){
				cout << "Array of size " << vec.size() << " does not fit the required size of 3" << endl;
				throw py::index_error();
			}
			return new Vector3Trampoline<T>(vec[0], vec[1], vec[2]);
		}));
		// functions:
		cl.def("setX", &Vector3Trampoline<T>::setX);
		cl.def("setY", &Vector3Trampoline<T>::setY);
		cl.def("setZ", &Vector3Trampoline<T>::setZ);
		cl.def("setXYZ", &Vector3Trampoline<T>::setXYZ);
		cl.def("setR", &Vector3Trampoline<T>::setR);
		cl.def("setRThetaPhi", &Vector3Trampoline<T>::setRThetaPhi);
		cl.def("getX", &Vector3Trampoline<T>::getX);
		cl.def("getY", &Vector3Trampoline<T>::getY);
		cl.def("getZ", &Vector3Trampoline<T>::getZ);
		cl.def("getR", &Vector3Trampoline<T>::getR);
		cl.def("getR2", &Vector3Trampoline<T>::getR2);
		cl.def("getPhi", &Vector3Trampoline<T>::getPhi);
		cl.def("getTheta", &Vector3Trampoline<T>::getTheta);
		cl.def("getUnitVector", &Vector3Trampoline<T>::getUnitVector);
		cl.def("getUnitVectorTheta", &Vector3Trampoline<T>::getUnitVectorTheta);
		cl.def("getUnitVectorPhi", &Vector3Trampoline<T>::getUnitVectorPhi);
		cl.def("getAngleTo", &Vector3Trampoline<T>::getAngleTo);
		cl.def("isParallelTo", &Vector3Trampoline<T>::isParallelTo);
		cl.def("getDistanceTo", &Vector3Trampoline<T>::getDistanceTo);
		cl.def("getParallelTo", &Vector3Trampoline<T>::getParallelTo);
		cl.def("getPerpendicularTo", &Vector3Trampoline<T>::getPerpendicularTo);
		cl.def("getRotated", &Vector3Trampoline<T>::getRotated);
		cl.def("clip", &Vector3Trampoline<T>::clip);
		cl.def("abs", &Vector3Trampoline<T>::abs);
		cl.def("floor", &Vector3Trampoline<T>::floor);
		cl.def("ceil", &Vector3Trampoline<T>::ceil);
		cl.def("min", &Vector3Trampoline<T>::min);
		cl.def("max", &Vector3Trampoline<T>::max);
		cl.def("dot", &Vector3Trampoline<T>::dot);
		cl.def("cross", &Vector3Trampoline<T>::cross);
		cl.def("getDescription", &Vector3Trampoline<T>::getDescription);
		// python side functions:
		cl.def("__str__", &Vector3Trampoline<T>::getDescription);
		cl.def("__repr__", &Vector3Trampoline<T>::getDescription);
		cl.def("__doc__", [](const Vector3Trampoline<T>& c){return "\
Allows accessing and changing the elements x, y, z directly or  through the\n\
corresponding get and set methods.\n\
\n\
Angle definitions are\n\
phi [-pi, pi]: azimuthal angle in the x-y plane, 0 pointing in x-direction\n\
theta [0, pi]: zenith angle towards the z axis, 0 pointing in z-direction";
		});
		cl.def("getDict", [](const Vector3Trampoline<T>& c) -> const py::dict {
			return py::dict(
				"x"_a=c.x,
				"y"_a=c.y,
				"z"_a=c.z
			);
		});
		cl.def("__len__", [](const Vector3Trampoline<T>& c){return 3;});
		cl.def("__getitem__", [](Vector3Trampoline<T>& c, const int& idx){
			if (idx==-1)
				return c.data[2];
			if (idx==-2)
				return c.data[1];
			if (idx>2 || idx<-2)
				throw py::index_error();
			return c.data[idx];
		});
		cl.def("__setitem__", [](Vector3Trampoline<T>& c, const int& idx, T val){
			if (idx==-1)
				c.data[2]=val;
			if (idx==-2)
				c.data[1]=val;
			if (idx>2 || idx<-2)
				throw py::index_error();
			c.data[idx]=val;
		});
		// needed for numpy array compability and other buffer stuff (like very fast no copy instructions)
		cl.def_buffer([](Vector3Trampoline<T>& c) -> py::buffer_info {
			return py::buffer_info(
				c.data,  // pointer to buffer
				sizeof(T),  // size of one scalar
				py::format_descriptor<T>::format(),  // python struct-style format descriptor
				1,  // number of dimensions
				{3},  // buffer dimensions
				{sizeof(T)}  // strides (in bytes) for each index
			);
		});
		// operators
		cl.def(py::self == py::self);
		cl.def(py::self + py::self);
		cl.def(py::self + T());
		cl.def(py::self - py::self);
		cl.def(py::self - T());
		cl.def(py::self * py::self);
		cl.def(py::self * T());
		cl.def(py::self / py::self);
		cl.def(py::self / T());
		cl.def(py::self % py::self);
		cl.def(py::self % T());
		cl.def(py::self += py::self);
		cl.def(py::self += T());
		cl.def(py::self -= py::self);
		cl.def(py::self -= T());
		cl.def(py::self *= py::self);
		cl.def(py::self *= T());
		cl.def(py::self /= py::self);
		cl.def(py::self /= T());
		cl.def(py::self %= py::self);
		cl.def(py::self %= T());
		// variables:
		cl.def_readwrite("x", &Vector3Trampoline<T>::x);
		cl.def_readwrite("y", &Vector3Trampoline<T>::y);
		cl.def_readwrite("z", &Vector3Trampoline<T>::z);
	}


}

#endif