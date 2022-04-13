# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)



# Project

project(SA_Event)

message("SA_Event Main directory: ${CMAKE_CURRENT_SOURCE_DIR}")



# Outputs

### Setup output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)		# .exe
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)		# .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)		# .dll / .so



# Input

# No source files
#file(GLOB_RECURSE SA_EVENT_SOURCES "Source/*")



# Library


## Static library.
add_library(SA_Event INTERFACE)


## Include directories
target_include_directories(SA_Event INTERFACE Include)


## Compile features

### Standard
target_compile_features(SA_Event INTERFACE c_std_11)
target_compile_features(SA_Event INTERFACE cxx_std_20)

### SA_Maths module implementation preprocessor.
target_compile_definitions(SA_Event INTERFACE SA_EVENT_IMPL)



# Options

## Add SA_Event's use SA_Logger.
option(SA_EVENT_USE_LOGGER_OPT "Should compile and use SA_Logger" ON)

if(SA_EVENT_USE_LOGGER_OPT)
	target_link_libraries(SA_Event INTERFACE SA_Logger)
endif()


## Add SA_Event's tests to build tree.
option(SA_EVENT_BUILD_TESTS_OPT "Should build SA_Event tests" OFF)



# Entrypoints

add_subdirectory(ThirdParty)

if(SA_EVENT_BUILD_TESTS_OPT)

	### Enable testing for this directory and below.
	enable_testing()

	add_subdirectory(Tests)
endif()
