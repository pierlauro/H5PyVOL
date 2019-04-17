cmake_minimum_required(VERSION 3.10)
project(PyVOL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 ")

message(${CMAKE_MODULE_PATH})

set(HDF5_USE_STATIC_LIBRARIES FALSE)
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
		${CMAKE_CURRENT_LIST_DIR}/src/c/VOL.h
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/c/VOL.c
		${CMAKE_CURRENT_LIST_DIR}/src/c/python_util.h
		${CMAKE_CURRENT_LIST_DIR}/src/c/python_util.c
		${CMAKE_CURRENT_LIST_DIR}/src/c/datatypes_util.h
		${CMAKE_CURRENT_LIST_DIR}/src/c/datatypes_util.c
)

target_include_directories(pyvol
	PUBLIC
		${HDF5_INCLUDE_DIRS}
	PRIVATE
		${PYTHON_INCLUDE_DIRS}
		${PYTHON_NUMPY_INCLUDE_DIR}
)

target_link_libraries(pyvol
	PUBLIC
		MPI::MPI_C
		${HDF5_LIBRARIES}
	PRIVATE
		${PYTHON_LIBRARIES}
)

file(COPY examples/python_vol DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS pyvol
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)

add_executable(vol examples/vol.c)

target_link_libraries(vol
	PUBLIC
		pyvol
	PRIVATE
		${PYTHON_LIBRARIES}
)

target_include_directories(vol
	PUBLIC
		${HDF5_INCLUDE_DIRS}
		${PYTHON_INCLUDE_DIRS}
		${CMAKE_CURRENT_LIST_DIR}/src/c
)

add_executable(c-py examples/c-py.c)

target_link_libraries(c-py
	PUBLIC
		pyvol
	PRIVATE
		${PYTHON_LIBRARIES}
)

target_include_directories(c-py
	PUBLIC
		${HDF5_INCLUDE_DIRS}
		${PYTHON_INCLUDE_DIRS}
		${CMAKE_CURRENT_LIST_DIR}/src/c
)
