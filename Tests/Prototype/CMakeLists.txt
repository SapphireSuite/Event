# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_EventProto)



# Executable

## Add executable target.
add_executable(SA_EventProto "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_EventProto PRIVATE SA_Event)



# Tests

add_test(NAME CSA_EventProto COMMAND SA_EventProto)
