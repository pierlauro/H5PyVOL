cmake_minimum_required(VERSION 3.10)
project(PyVOL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)

message(${CMAKE_MODULE_PATH})

set(HDF5_USE_STATIC_LIBRARIES TRUE)
set(HDF5_PREFER_PARALLEL TRUE)
find_package(HDF5 REQUIRED C)
if(NOT ${HDF5_IS_PARALLEL})
	#message(FATAL_ERROR 'HDF5 is not parallel!')
	message(STATUS "HDF5 is not parallel!")
endif()

find_package(MPI REQUIRED C)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

find_package(NumPy REQUIRED)

add_library(pyvol SHARED)

target_sources(pyvol
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/VOL.h
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/VOL.c
		${CMAKE_CURRENT_LIST_DIR}/python_util.h
		${CMAKE_CURRENT_LIST_DIR}/python_util.c
)

target_include_directories(pyvol
	PRIVATE
		${HDF5_INCLUDE_DIRS}
		${PYTHON_INCLUDE_DIRS}
		${PYTHON_NUMPY_INCLUDE_DIR}
)

target_link_libraries(pyvol
	PRIVATE
		MPI::MPI_C
		${HDF5_INCLUDE_LIBRARIES}
		${PYTHON_LIBRARIES}
)
