cmake_minimum_required(VERSION 3.15)
project(PyVOL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O3 ")

message(${CMAKE_MODULE_PATH})

if(DEFINED ENV{HDF5_PLUGIN_PATH})
	set(HDF5_PLUGIN_PATH $ENV{HDF5_PLUGIN_PATH})
else()
	set(HDF5_PLUGIN_PATH /usr/local/hdf5/lib/plugin)
endif()

set(HDF5_USE_STATIC_LIBRARIES FALSE)
set(HDF5_PREFER_PARALLEL TRUE)
find_package(HDF5 REQUIRED C)
if(NOT ${HDF5_IS_PARALLEL})
	message(STATUS "HDF5 is not parallel!")
endif()

find_package(MPI REQUIRED C)

find_package (Python3 COMPONENTS Interpreter Development NumPy)


### LIBRARY
add_library(pyvol SHARED)

file(GLOB PYVOL_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/c/**.c)

target_sources(pyvol
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/src/c/PyVOL.h
	PRIVATE
		${PYVOL_SOURCES}
		${CMAKE_CURRENT_LIST_DIR}/src/c/python_util.h
		${CMAKE_CURRENT_LIST_DIR}/src/c/datatypes_util.h
)

target_include_directories(pyvol
	PUBLIC
		${HDF5_INCLUDE_DIRS}
	PRIVATE
		${Python3_INCLUDE_DIRS}
		${Python3_NumPy_INCLUDE_DIRS}
)

target_link_libraries(pyvol
	PUBLIC
		MPI::MPI_C
		${HDF5_LIBRARIES}
	PRIVATE
		${Python3_LIBRARIES}
)


install(TARGETS pyvol
	LIBRARY DESTINATION ${HDF5_PLUGIN_PATH}
)


### EXAMPLE
add_executable(vol examples/vol.c)

file(COPY examples/python_vol DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(vol
	PUBLIC
		${HDF5_LIBRARIES}
		${Python3_LIBRARIES}
)

target_include_directories(vol
	PUBLIC
		${HDF5_INCLUDE_DIRS}
		${Python3_INCLUDE_DIRS}
		${Python3_NumPy_INCLUDE_DIRS}
)

