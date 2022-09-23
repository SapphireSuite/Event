# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)

# Sapphire Suite's CMake tools.
add_subdirectory(CMake)



# Project

project(SA_Event)
SA_ConfigureProject(SA_Event)



# Library

add_library(SA_Event INTERFACE)

SA_ConfigureTarget(SA_Event LINK INTERFACE)
SA_TargetInterfaceSources(SA_Event)



# Options

## Add SA_Event's use SA_Logger.
option(SA_EVENT_USE_LOGGER_OPT "Should compile and use SA_Logger" OFF)

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
