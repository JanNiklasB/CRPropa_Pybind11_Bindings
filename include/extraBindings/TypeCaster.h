#ifndef CRPROPA_TYPECASTER_H
#define CRPROPA_TYPECASTER_H

#include "crpropa/Vector3.h"

#include <pybind11/pybind11.h>

namespace pybind11::detail{

	namespace py = pybind11;

	template <>
	struct type_caster<crpropa::Vector3d> {
		PYBIND11_TYPE_CASTER(crpropa::Vector3d, io_name("Sequence[float]", "crpropa.Vector3d"));

		bool load(handle src, bool){
			if (py::hasattr(src, "x") && py::hasattr(src, "y") && py::hasattr(src, "z")) {
				value.x = py::cast<double>(src.attr("x"));
				value.y = py::cast<double>(src.attr("y"));
				value.z = py::cast<double>(src.attr("z"));
				return true;
			}

			if (!py::isinstance<py::sequence>(src)) {
				return false;
			}
			auto seq = py::reinterpret_borrow<py::sequence>(src);
			// Check if exactly two values are in the Sequence
			if (seq.size() != 3) {
				return false;
			}
			// Check if each element is either a float or an int
			for (auto item : seq) {
				if (!py::isinstance<py::float_>(item) && !py::isinstance<py::int_>(item)) {
					return false;
				}
			}
			value.x = seq[0].cast<double>();
			value.y = seq[1].cast<double>();
			value.z = seq[2].cast<double>();
			return true;
		}

		static handle cast(const crpropa::Vector3d &src, return_value_policy, handle){
			py::object py_vec = py::module::import("crpropa").attr("Vector3d")(src.x, src.y, src.z);
       		return py_vec.release();
		}
	};

}


#endif