#!/bin/bash

set -ex

PYTHON_INCLUDE_DIR=$(${PYTHON} -c "import sysconfig; print(sysconfig.get_paths()['include'])")
NUMPY_INCLUDE_DIR=$(${PYTHON} -c "import numpy; print(numpy.get_include())")

cd $SRC_DIR/crpropa_bindings
mkdir build && cd build
cmake .. -G Ninja \
	-DCMAKE_PREFIX_PATH="${PREFIX}" \
	-DPython_EXECUTABLE="${PYTHON}" \
	-DPython_NumPy_INCLUDE_DIR="${NUMPY_INCLUDE_DIR}" \
	-DPython_INCLUDE_DIR="${PYTHON_INCLUDE_DIR}" \
	-DPython_INSTALL_PACKAGE_DIR="${SP_DIR}" \
	-DCMAKE_INSTALL_PREFIX="${PREFIX}" \
	-DBUILD_DOC=OFF \
	-DDOWNLOAD_DATA=OFF \
	-DENABLE_COVERAGE=OFF \
	-DENABLE_GIT=ON \
	-DENABLE_HDF5=ON \
	-DENABLE_OPENMP=ON \
	-DENABLE_QUIMBY=OFF \
	-DENABLE_TESTING=ON \
	-DFAST_WAVES="${FAST_WAVES}" \
	-DOMP_SCHEDULE=dynamic \
	-DSIMD_EXTENSIONS="${SIMD_EXTENSIONS}" \
	-DCRPROPA_TESTS_PATH="${PREFIX}/share/crpropa/test/" \
	-DCRPROPA_SOURCE="${SRC_DIR}/crpropa_src"
cmake --build .
cp -R crpropa ${SP_DIR}/
$PREFIX/bin/pybind11-stubgen -o ${SP_DIR} crpropa
cp *.py $PREFIX/share/crpropa/test/