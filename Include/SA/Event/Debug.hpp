// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_EVENT_DEBUG_GUARD
#define SAPPHIRE_EVENT_DEBUG_GUARD

/**
*	\file Event/Debug.hpp
*
*	\brief Event specific Debug file.
*
*	\ingroup Event
*	\{
*/


#if SA_LOGGER_IMPL || defined(DOXYGEN)

	// Add Sapphire Logger if implementation linked
	#include <SA/Collections/Debug>

#else

	// Define empty logger macro.

	#define SA_LOG(...) {}

	#define SA_WARN(...) {}

	#define SA_ERROR(...) {}


	#define SA_ASSERT(...) {}

	#define SA_ASSERT_EXEC(_type, _chan, _exec, ...) { _exec; }

#endif


/** \} */

#endif // GUARD
