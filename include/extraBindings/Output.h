#ifndef CRPROPA_BINDINGS_OUTPUT_H
#define CRPROPA_BINDINGS_OUTPUT_H

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

pybind11::handle enableProperty(crpropa::Output &self, const std::string &name, pybind11::handle defaultValue, const std::string &comment="") {

	if (pybind11::isinstance<pybind11::none>(defaultValue)) {
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::bool_>(defaultValue)) {
		if(defaultValue == Py_True) {
			self.enableProperty(name, true, comment);
		} else {
			self.enableProperty(name, false, comment);
		}
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::int_>(defaultValue)) {
		self.enableProperty(name, crpropa::Variant::fromInt64(pybind11::cast<long>(defaultValue)), comment);
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::float_>(defaultValue)) {
		self.enableProperty(name, crpropa::Variant::fromDouble(pybind11::cast<double>(defaultValue)), comment);
		Py_RETURN_TRUE;
	} else if (pybind11::isinstance<pybind11::str>(defaultValue)){
		std::string ss = pybind11::cast<std::string>(defaultValue);
		self.enableProperty(name, ss, comment);
		Py_RETURN_TRUE;
	} else {
		std::string typinfo = pybind11::cast<std::string>(defaultValue.attr("__class__").attr("__name__"));
		std::cerr << "ERROR: Unknown Type: " << typinfo << std::endl;
		return Py_None;
	}

}

namespace crpropa_bindings{
	template<typename T>
	void Output_binder(T cl){
		cl.def("enableProperty", &enableProperty,
		R"(
		Add a property to output.
		Default value is required to assign a type in the output.

		Parameters
		----------
		property : str 
			string containing name of property
		defaultValue : None, bool, int, float, str
			default value of property
		comment : str, optional
			string with a comment
		)");
	}
}

#endif