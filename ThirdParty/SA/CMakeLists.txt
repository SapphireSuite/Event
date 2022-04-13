# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Entrypoints

include(FetchContent)

if(NOT TARGET SA_Logger AND SA_EVENT_USE_LOGGER_OPT)

	message("Fetching SA_Logger...")

	set(SA_LOGGER_TARGET_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/SA/Logger)

	FetchContent_Declare(
		SA_Logger
		GIT_REPOSITORY https://github.com/SapphireSuite/Logger.git
		GIT_TAG        main
		SOURCE_DIR ${SA_LOGGER_TARGET_SOURCE_DIR}
	)

	FetchContent_MakeAvailable(SA_Logger)

endif()
