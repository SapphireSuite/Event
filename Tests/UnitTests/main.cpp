// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <gtest/gtest.h>

#include <SA/Event/Debug.hpp>

int main(int argc, char** argv)
{
#if SA_LOGGER_IMPL

	SA::Logger logger;
	SA::ConsoleLogStream cslStr;
	logger.Register(cslStr);

	SA::Debug::logger = &logger;

#endif

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
