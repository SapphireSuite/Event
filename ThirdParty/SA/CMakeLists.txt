# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Entrypoints

add_subdirectory(CMake_Utils)

if(SA_EVENT_USE_LOGGER_OPT)

	SA_FetchModule(Logger)

endif()
