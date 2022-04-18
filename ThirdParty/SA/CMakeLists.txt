# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Entrypoints

include(CMake_FetchModule/SA_FetchModule.cmake)

if(SA_EVENT_USE_LOGGER_OPT)

	SA_FetchModule(Logger)

endif()
