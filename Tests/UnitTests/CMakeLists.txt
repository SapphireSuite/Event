# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_EventUT)


SA_FetchGoogleTest()



# Executable

## Inputs

file(GLOB_RECURSE SA_EVENT_UT_SOURCES "*.cpp")

## Add executable target.
add_executable(SA_EventUT ${SA_EVENT_UT_SOURCES})



# Dependencies

### Add library dependencies.
target_link_libraries(SA_EventUT PRIVATE SA_Event)

### Google test module dependency.
target_link_libraries(SA_EventUT PRIVATE gtest)



# Tests

add_test(NAME CSA_EventUT COMMAND SA_EventUT)
