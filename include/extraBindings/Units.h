#ifndef CRPROPA_BINDINGS_UNITS_H
#define CRPROPA_BINDINGS_UNITS_H

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

	void binder_for_crpropa_units(py::module &m){
		m.attr("meter") = cp::meter;
		m.attr("second") = cp::second;
		m.attr("kilogram") = cp::kilogram;
		m.attr("ampere") = cp::ampere;
		m.attr("mol") = cp::mol;
		m.attr("kelvin") = cp::kelvin;
		m.attr("newton") = cp::newton;
		m.attr("pascal") = cp::pascal;
		m.attr("joule") = cp::joule;
		m.attr("tesla") = cp::tesla;
		m.attr("volt") = cp::volt;
		m.attr("coulomb") = cp::coulomb;
		m.attr("hertz") = cp::hertz;
		m.attr("rad") = cp::rad;
		m.attr("deg") = cp::deg;
		m.attr("yocto") = cp::yocto;
		m.attr("zepto") = cp::zepto;
		m.attr("atto") = cp::atto;
		m.attr("femto") = cp::femto;
		m.attr("pico") = cp::pico;
		m.attr("nano") = cp::nano;
		m.attr("micro") = cp::micro;
		m.attr("milli") = cp::milli;
		m.attr("kilo") = cp::kilo;
		m.attr("mega") = cp::mega;
		m.attr("giga") = cp::giga;
		m.attr("tera") = cp::tera;
		m.attr("peta") = cp::peta;
		m.attr("exa") = cp::exa;
		m.attr("zetta") = cp::zetta;
		m.attr("yotta") = cp::yotta;
		m.attr("eplus") = cp::eplus;
		m.attr("c_light") = cp::c_light;
		m.attr("c_squared") = cp::c_squared;
		m.attr("amu") = cp::amu;
		m.attr("mass_proton") = cp::mass_proton;
		m.attr("mass_neutron") = cp::mass_neutron;
		m.attr("mass_electron") = cp::mass_electron;
		m.attr("h_planck") = cp::h_planck;
		m.attr("k_boltzmann") = cp::k_boltzmann;
		m.attr("mu0") = cp::mu0;
		m.attr("epsilon0") = cp::epsilon0;
		m.attr("alpha_finestructure") = cp::alpha_finestructure;
		m.attr("radius_electron") = cp::radius_electron;
		m.attr("sigma_thomson") = cp::sigma_thomson;
		m.attr("gauss") = cp::gauss;
		m.attr("microgauss") = cp::microgauss;
		m.attr("nanogauss") = cp::nanogauss;
		m.attr("muG") = cp::muG;
		m.attr("nG") = cp::nG;
		m.attr("erg") = cp::erg;
		m.attr("electronvolt") = cp::electronvolt;
		m.attr("kiloelectronvolt") = cp::kiloelectronvolt;
		m.attr("megaelectronvolt") = cp::megaelectronvolt;
		m.attr("gigaelectronvolt") = cp::gigaelectronvolt;
		m.attr("teraelectronvolt") = cp::teraelectronvolt;
		m.attr("petaelectronvolt") = cp::petaelectronvolt;
		m.attr("exaelectronvolt") = cp::exaelectronvolt;
		m.attr("eV") = cp::eV;
		m.attr("keV") = cp::keV;
		m.attr("MeV") = cp::MeV;
		m.attr("GeV") = cp::GeV;
		m.attr("TeV") = cp::TeV;
		m.attr("PeV") = cp::PeV;
		m.attr("EeV") = cp::EeV;
		m.attr("barn") = cp::barn;
		m.attr("au") = cp::au;
		m.attr("ly") = cp::ly;
		m.attr("parsec") = cp::parsec;
		m.attr("kiloparsec") = cp::kiloparsec;
		m.attr("megaparsec") = cp::megaparsec;
		m.attr("gigaparsec") = cp::gigaparsec;
		m.attr("pc") = cp::pc;
		m.attr("kpc") = cp::kpc;
		m.attr("Mpc") = cp::Mpc;
		m.attr("Gpc") = cp::Gpc;
		m.attr("kilometer") = cp::kilometer;
		m.attr("centimeter") = cp::centimeter;
		m.attr("km") = cp::km;
		m.attr("cm") = cp::cm;
		m.attr("nanosecond") = cp::nanosecond;
		m.attr("microsecond") = cp::microsecond;
		m.attr("millisecond") = cp::millisecond;
		m.attr("minute") = cp::minute;
		m.attr("hour") = cp::hour;
		m.attr("day") = cp::day;
		m.attr("year") = cp::year;
		m.attr("kiloyear") = cp::kiloyear;
		m.attr("Megayear") = cp::Megayear;
		m.attr("Gigayear") = cp::Gigayear;
		m.attr("ns") = cp::ns;
		m.attr("mus") = cp::mus;
		m.attr("ms") = cp::ms;
		m.attr("sec") = cp::sec;
		m.attr("yr") = cp::yr;
		m.attr("kyr") = cp::kyr;
		m.attr("Myr") = cp::Myr;
		m.attr("Gyr") = cp::Gyr;
		m.attr("ccm") = cp::ccm;

	}
}

#endif