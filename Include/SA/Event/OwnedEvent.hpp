// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_OWNED_EVENT_EVENT_GUARD
#define SAPPHIRE_OWNED_EVENT_EVENT_GUARD

#include <SA/Event/Event.hpp>

/**
*	\file OwnedEvent.hpp
*
*	\brief \b Definition of Sapphire \b Owned-Event type.
*
*	\ingroup Event
*	\{
*/


namespace SA
{
	/**
	*	\brief Sapphire Owned-Event default (undefined) declaration.
	* 
	*	\tparam OwnerT	Owner type.
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename OwnerT, typename R, typename... Args>
	class OwnedEvent;

	/**
	*	\brief Sapphire Owned-Event class.
	* 
	*	Event class with Execute-protected system.
	*	Only Owner class is allowed to call Execute().
	* 
	*	\tparam OwnerT	Owner type.
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename OwnerT, typename R, typename... Args>
	class OwnedEvent<OwnerT, R(Args...)> : private Event<R(Args...)>
	{
		// Only OwnerT can call Execute.
		friend OwnerT;

		using Event<R(Args...)>::Execute;
		using Event<R(Args...)>::operator();

	public:
		using Event<R(Args...)>::Event;
		using Event<R(Args...)>::IsEmpty;
		using Event<R(Args...)>::Clear;
		using Event<R(Args...)>::Add;
		using Event<R(Args...)>::Remove;
		using Event<R(Args...)>::RRemove;
		using Event<R(Args...)>::operator=;
		using Event<R(Args...)>::operator+=;
		using Event<R(Args...)>::operator-=;
	};
}

/**
*	\example OwnedEventTests.cpp
*	Examples and Unitary Tests for OwnedEvent.
*/


/** \} */

#endif // GUARD
