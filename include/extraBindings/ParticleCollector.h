#ifndef CRPROPA_BINDINGS_PARTICLECOLLECTOR_H
#define CRPROPA_BINDINGS_PARTICLECOLLECTOR_H

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

namespace crpropa_bindings{
	template<typename T>
	void ParticleCollector_binder(T cl){
		cl.def("__iter__", [](const crpropa::ParticleCollector &self) {
			return pybind11::make_iterator(self.begin(), self.end());
		});
		cl.def("__len__", &crpropa::ParticleCollector::size);
	}

}


#endif