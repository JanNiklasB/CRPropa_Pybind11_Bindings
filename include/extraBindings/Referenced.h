#ifndef CRPROPA_BINDINGS_REFERENCED_H
#define CRPROPA_BINDINGS_REFERENCED_H

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

	void Referenced_binder(py::module &m){
	
		pybind11::class_<crpropa::Referenced, std::unique_ptr<crpropa::Referenced, py::nodelete>> cl(m, "Referenced", "Base class for reference counting\n\n A form of memory management is needed to prevent memory leaks when using MPC in Python via SWIG.\n This base class enables reference counting.\n Every reference increases the reference counter, every dereference decreases it.\n When the counter is decreased to 0, the object is deleted.\n Candidate, Module, MagneticField and Source inherit from this class");
		// function-signature: crpropa::Referenced::Referenced()() file: line:31
		cl.def( pybind11::init<>() );
		// function-signature: crpropa::Referenced::Referenced(const class crpropa::Referenced &)(const class crpropa::Referenced &) file: line:35
		cl.def( pybind11::init<const crpropa::Referenced&>() );
		// function-signature: class crpropa::Referenced & crpropa::Referenced::operator=(const class crpropa::Referenced &)(const class crpropa::Referenced &) file: line:39
		cl.def("assign", (class crpropa::Referenced & (crpropa::Referenced::*)(const class crpropa::Referenced &)) &crpropa::Referenced::operator=, "C++: crpropa::Referenced::operator=(const class crpropa::Referenced &) --> class crpropa::Referenced &", pybind11::return_value_policy::automatic, pybind11::arg(""));
		// function-signature: unsigned long crpropa::Referenced::addReference() const() file: line:43
		cl.def("addReference", (unsigned long (crpropa::Referenced::*)() const) &crpropa::Referenced::addReference, "C++: crpropa::Referenced::addReference() const --> unsigned long");
		// function-signature: unsigned long crpropa::Referenced::removeReference() const() file: line:64
		cl.def("removeReference", (unsigned long (crpropa::Referenced::*)() const) &crpropa::Referenced::removeReference, "C++: crpropa::Referenced::removeReference() const --> unsigned long");
		// function-signature: int crpropa::Referenced::removeReferenceNoDelete() const() file: line:83
		cl.def("removeReferenceNoDelete", (int (crpropa::Referenced::*)() const) &crpropa::Referenced::removeReferenceNoDelete, "C++: crpropa::Referenced::removeReferenceNoDelete() const --> int");
		// function-signature: unsigned long crpropa::Referenced::getReferenceCount() const() file: line:87
		cl.def("getReferenceCount", (unsigned long (crpropa::Referenced::*)() const) &crpropa::Referenced::getReferenceCount, "C++: crpropa::Referenced::getReferenceCount() const --> unsigned long");

	}
}

#endif