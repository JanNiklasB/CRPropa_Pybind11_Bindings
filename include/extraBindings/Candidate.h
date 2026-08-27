#ifndef CRPROPA_BINDINGS_CANDIDATE_H
#define CRPROPA_BINDINGS_CANDIDATE_H

#include <CRPropa.h>

#include <string>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

pybind11::handle getProperty(crpropa::Candidate &self, const std::string &name) {

	crpropa::Variant value = self.getProperty(name);

	// implement this conversion here and not in the Variant as
	// __asPythonObject, as extensions cannot be called from extension.
	switch (value.getType()) {
	case crpropa::Variant::TYPE_NONE:
		Py_INCREF(Py_None);
		return Py_None;
	case crpropa::Variant::TYPE_BOOL:
		if (value.toBool()) {
		Py_RETURN_TRUE;
		} else {
		Py_RETURN_FALSE;
		}
	case crpropa::Variant::TYPE_CHAR:
	case crpropa::Variant::TYPE_UCHAR:
	case crpropa::Variant::TYPE_INT16:
	case crpropa::Variant::TYPE_UINT16:
	case crpropa::Variant::TYPE_INT32:
	case crpropa::Variant::TYPE_UINT32:
	case crpropa::Variant::TYPE_INT64:
		return PyLong_FromLongLong(value.toInt64());
	case crpropa::Variant::TYPE_UINT64:
		return PyLong_FromUnsignedLongLong(value.toUInt64());
	case crpropa::Variant::TYPE_FLOAT:
	case crpropa::Variant::TYPE_DOUBLE:
	case crpropa::Variant::TYPE_LONGDOUBLE:
		return PyFloat_FromDouble(value.toDouble());
	case crpropa::Variant::TYPE_STRING:
		return PyUnicode_FromString(value.toString().c_str());
	case crpropa::Variant::TYPE_COMPLEXF:
	case crpropa::Variant::TYPE_COMPLEXD: {
		std::complex<double> complexValue = value.toComplexDouble();
		return PyComplex_FromDoubles(complexValue.real(), complexValue.imag());
	}
	default:
		std::cerr << "ERROR: Unknown Type: " << value.getTypeName() << std::endl;
		PyErr_Format(PyExc_TypeError, "Unsupported candidate property type '%s'", value.getTypeName());
		return Py_None;
	}
}

bool setProperty(crpropa::Candidate &self, const std::string &name, pybind11::handle value) {

	if (pybind11::isinstance<pybind11::none>(value)) {
		self.setProperty(name, crpropa::Variant());
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::bool_>(value)) {
		if(value == Py_True) {
			self.setProperty(name, true);
		} else {
			self.setProperty(name, false);
		}
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::int_>(value)) {
		self.setProperty(name, crpropa::Variant::fromUInt64(pybind11::cast<long>(value)));
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::float_>(value)) {
		self.setProperty(name, crpropa::Variant::fromDouble(pybind11::cast<double>(value)));
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::str>(value)){
		self.setProperty(name, pybind11::cast<std::string>(value));
		Py_RETURN_TRUE;
	} else {
		std::string typinfo = pybind11::cast<std::string>(value.attr("__class__").attr("__name__"));
		std::cerr << "ERROR: Unknown Type: " << typinfo << std::endl;
		return NULL;
	}
}


namespace crpropa_bindings{
	template<typename T>
	void Candidate_binder(T cl){
		cl.def("getProperty", &getProperty, 
		R"(
		Sets a arbitrary property
		This function either creates a property if it does not exist or updates it.
		
		Parameter
		---------
		key : str 
			Key to put into unordered_map
		value : None, bool, int, float, str
			Any Variant object, Variant can represent a variety of data types so
			that a property can have any basic datatype
		)");
		cl.def("setProperty", &setProperty,
		R"(
		Returns the value of the Property with given key
		This function loops through the unordered_map and returns the first property fitting to
		the provided key. If no key value pair is found it throws an error

		Parameter
		---------
		key : str
			Key to search for
		)");
	}
}

#endif