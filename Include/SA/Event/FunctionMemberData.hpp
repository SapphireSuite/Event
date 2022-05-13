// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_EVENT_FUNCTION_MEMBER_DATA_GUARD
#define SAPPHIRE_EVENT_FUNCTION_MEMBER_DATA_GUARD

#include <cstdint>

#include <SA/Event/Debug.hpp>

/**
*	\file FunctionMemberData.hpp
*
*	\brief Internal \b Definition of Sapphire \b FunctionMemberData type.
*
*	\ingroup Event
*	\{
*/


namespace SA
{
	namespace Intl
	{
		/**
		*	\brief Base struct of member function data.
		*
		*	Interface class with virtual destructor to store template child class.
		*/
		struct FuncMemberDataBase
		{
			/**
			*	\brief default virtual destructor.
			*	Ensure correct child class destruction on delete.
			*/
			virtual ~FuncMemberDataBase() = default;

			/**
			*	\brief \b Duplicate child data (used for copy operations).
			*
			*	\return new data duplicated.
			*/
			virtual FuncMemberDataBase* Duplicate() const = 0;

			/**
			*	\brief \b Compare child data class
			*
			*	\param[in] _other	member to compare to.
			*
			*	\return true on equality.
			*/
			virtual bool Compare(const FuncMemberDataBase* _other) const = 0;
		};

		/**
		*	\brief Data struct for <b>typed</b> member function.
		*
		*	\tparam C		Caller type of function's declaration.
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename C, typename R, typename... Args>
		struct FuncMemberData : public FuncMemberDataBase
		{
			/// Caller ptr handle.
			C* caller = nullptr;

			/// Function ptr handle.
			R(C::* func)(Args...) = nullptr;

			/**
			*	\brief Default value constructor.
			*
			*	\param[in] _caller	Caller of the member function.
			*	\param[in] _func	Member function to call.
			*/
			FuncMemberData(C* _caller, R(C::* _func)(Args...));

			FuncMemberDataBase* Duplicate() const override final;
			bool Compare(const FuncMemberDataBase* _other) const override final;

			/**
			*	\brief Interface methods requiered for function handle.
			*	Ensure correct child type call.
			*
			*	\param[in] _data	Stored typed FuncMemberData.
			*	\param[in] _args	Function arguments.
			*
			*	\return function return value.
			*/
			static R InterfaceCall(void* _data, Args... _args);
		};
	}
}

#include <SA/Event/FunctionMemberData.inl>


/** \} */

#endif // GUARD
