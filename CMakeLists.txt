cmake_minimum_required(VERSION 3.14)

project(crpropa_pybind11_bindings)

set(Python_FIND_VIRTUALENV "FIRST")
set(Python_FIND_STRATEGY "LOCATION")
find_package(Python 3.0 COMPONENTS Interpreter Development NumPy REQUIRED)

option(ENABLE_PYBIND11_STUBGEN "Generate Pybind11 stubs" On)
option(ENABLE_TESTING "Build tests and enable test target" On)
# set(Python_INSTALL_PACKAGE_DIR "${Python_SITELIB}" CACHE PATH "folder in which the python package is installed")
set(CRPROPA_GIT_REPOSITORY "https://github.com/JanNiklasB/CRPropa3.git" CACHE STRING "The git repository to fetch")
set(CRPROPA_GIT_TAG "pybind11PluginAdjustments" CACHE STRING "The git tag to check out to")
set(CRPROPA_SOURCE "" CACHE PATH "An optional local CRPropa source, needs to point to the same folder the CMakeLists.txt is in")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENABLE_PYTHON OFF CACHE BOOL "")
mark_as_advanced(ENABLE_PYTHON)
set(ENABLE_BUILTIN OFF CACHE BOOL "")
mark_as_advanced(ENABLE_BUILTIN)

# build crpropa and add resulting libcrpropa.so as library
if(NOT CRPROPA_SOURCE)
	if(NOT crpropa_POPULATED)
		include(FetchContent)
		
		# pulls repository specified and can even be pinned on specific commit
		FetchContent_Declare(
			crpropa
			GIT_REPOSITORY "${CRPROPA_GIT_REPOSITORY}"
			GIT_TAG "${CRPROPA_GIT_TAG}"
		)

		# contains .cmake files necessary for finding modules
		list(APPEND CMAKE_MODULE_PATH "${CRPropa_SOURCE_DIR}/cmake")
		
		FetchContent_MakeAvailable(crpropa)
	endif(NOT crpropa_POPULATED)

	set(CRPropa_SOURCE_DIR "${crpropa_SOURCE_DIR}")
	set(CRPropa_BINARY_DIR "${crpropa_BINARY_DIR}")

else()

	add_subdirectory(${CRPROPA_SOURCE} ${CMAKE_CURRENT_BINARY_DIR}/_deps/crpropa-build)

	set(CRPropa_SOURCE_DIR ${CRPROPA_SOURCE})
	set(CRPropa_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/crpropa-build)

endif(NOT CRPROPA_SOURCE)

list(APPEND crpropa_all_includes 
	${CRPROPA_EXTRA_INCLUDES}
	${CRPropa_SOURCE_DIR}/include
	${CRPropa_BINARY_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
# list(APPEND crpropa_pybind_extra_sources 
# 	${CMAKE_CURRENT_SOURCE_DIR}/src/Vector3.cpp
# )
add_custom_target(crpropa-pybind11-config
	COMMAND cmake -G ${CMAKE_GENERATOR}
		-S "${CMAKE_CURRENT_SOURCE_DIR}/python"
		-B "${CMAKE_CURRENT_BINARY_DIR}/bindings-bld"
		-D headers_to_bind_file="${CRPropa_SOURCE_DIR}/include/CRPropa.h"
		-D root_module_name="crpropa"
		-D project_lib_file="${CRPropa_BINARY_DIR}/libcrpropa.so"
		-D project_includes="${crpropa_all_includes}"
		-D project_extra_sources="${crpropa_pybind_extra_sources}"
		-D output_dir="${CMAKE_CURRENT_BINARY_DIR}"
		-D compile_commands_file="${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json"
	USES_TERMINAL
	DEPENDS crpropa
)
add_custom_target(crpropa-pybind11-build ALL
	COMMAND cmake --build ${CMAKE_CURRENT_BINARY_DIR}/bindings-bld
	USES_TERMINAL
	DEPENDS crpropa-pybind11-config
)

# first copy everything from the original python/crpropa and then overwrite it necessary files:
file(
	COPY
	"${CRPropa_SOURCE_DIR}/python/crpropa/"
	DESTINATION
	"${CMAKE_CURRENT_BINARY_DIR}/crpropa"
)
# move __init__.py and other needed files to build folder for tests and usage without installation
file(
	COPY
	"${CMAKE_CURRENT_SOURCE_DIR}/python/crpropa/"
	DESTINATION
	"${CMAKE_CURRENT_BINARY_DIR}/crpropa"
)

if(ENABLE_TESTING)
	enable_testing()
	function(addTestPy testName)
      configure_file(${CRPropa_SOURCE_DIR}/test/${testName}.py ${CMAKE_CURRENT_BINARY_DIR}/${testName}.py COPYONLY)
      add_test(NAME ${testName} COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/${testName}.py)
    endfunction()

	function(addTestPyLocal testName)
      configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test/${testName}.py ${CMAKE_CURRENT_BINARY_DIR}/${testName}.py COPYONLY)
      add_test(NAME ${testName} COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/${testName}.py)
    endfunction()

    addTestPy(testSimulationExecution)
    addTestPy(testDiffusionSDE)
    addTestPy(testMomentumDiffusion)
    
	addTestPyLocal(testPythonExtension)
	addTestPyLocal(testImports)

endif(ENABLE_TESTING)

install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/crpropa" DESTINATION "${Python_SITELIB}")

if(ENABLE_PYBIND11_STUBGEN)
	find_program(PYBIND11_STUBGEN_EXECUTABLE NAMES "pybind11-stubgen")
	if(PYBIND11_STUBGEN_EXECUTABLE)
		message(STATUS "Found pybind11-stubgen at ${PYBIND11_STUBGEN_EXECUTABLE}")
		install(CODE "execute_process(COMMAND ${PYBIND11_STUBGEN_EXECUTABLE} --ignore-all-errors -o ${Python_SITELIB} crpropa)")
		install(CODE "execute_process(COMMAND echo -- Generated python stubs over pybind11-stubgen for crpropa)")
	endif(PYBIND11_STUBGEN_EXECUTABLE)
endif(ENABLE_PYBIND11_STUBGEN)