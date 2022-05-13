// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_EVENT_PACKED_FUNCTION_GUARD
#define SAPPHIRE_EVENT_PACKED_FUNCTION_GUARD

#include <tuple>

#include <SA/Event/Function.hpp>

/**
*	\file PackedFunction.hpp
*
*	\brief \b Definition of Sapphire <b>Packed Function</b> type.
*
*	\ingroup Event
*	\{
*/


namespace SA
{
	/**
	*	\brief <b>Packed Function</b> type implementation.
	*
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class PackedFunction : private Function<R, Args...>
	{
		std::tuple<Args...> mArgs;

	public:

	//{ Constructors

		/// Default constructor.
		PackedFunction() = default;

		/**
		*	\e Value constructor with static function.
		*
		*	\param[in] _func	Static function to bind.
		*	\param[in] _args	Args to pack.
		*/
		PackedFunction(R(*_func)(Args...), Args... _args) noexcept;

		/**
		*	\e Value constructor with member function.
		*
		*	\tparam C			Caller type.
		*	\param[in] _caller	Object caller of member function.
		*	\param[in] _func	Member function to bind.
		*	\param[in] _args	Args to pack.
		*/
		template <typename C>
		PackedFunction(C* _caller, R(C::* _func)(Args...), Args... _args);


		/**
		*	\e Move constructor.
		*	Steal function handle (no additional memory allocation).
		*
		*	\param[in] _other	Other handle to move.
		*/
		PackedFunction(PackedFunction&& _other) noexcept;

		/**
		*	\e Copy constructor.
		*	Additional memory allocation on member function copy.
		*
		*	\param[in] _other	Other handle to copy.
		*/
		PackedFunction(const PackedFunction& _other) noexcept;

	//}

	//{ Equals

		using Function<R, Args...>::IsEmpty;
		using Function<R, Args...>::operator bool;


		/**
		*	\brief \e Compare 2 function handle.
		*
		*	\param[in] _other		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool Equals(const PackedFunction& _other) const;

		/**
		*	\brief \e Compare 2 function handle equality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool operator==(const PackedFunction& _rhs) const;


		/**
		*	\brief \e Compare 2 function handle inequality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are non-equal.
		*/
		bool operator!=(const PackedFunction& _rhs) const;

	//}

	//{ Set

		using Function<R, Args...>::Clear;

		/**
		*	\brief Set (assignation) new <b>static function</b> to bind.
		*	Free previous allocated memory.
		*
		*	\param[in] _func	New static function to bind.
		*	\param[in] _args	Args to pack.
		*/
		void Set(R(*_func)(Args...), Args... _args);

		/**
		*	\brief Set (assignation) new <b>member function</b> to bind.
		*	Free previous allocated memory.
		*
		*	\tparam C			Caller type.
		*	\param[in] _caller	New object caller of member function.
		*	\param[in] _func	New member function to bind.
		*	\param[in] _args	Args to pack.
		*/
		template <typename C>
		void Set(C* _caller, R(C::* _func)(Args...), Args... _args);


		/**
		*	\brief Move operator
		*	Steal function handle (no additional memory allocation).
		*
		*	\param[in] _rhs		Function handle to move.
		*
		*	\return this.
		*/
		PackedFunction& operator=(PackedFunction&& _rhs) noexcept;

		/**
		*	\brief Copy operator
		*	Additional memory allocation on member function copy.
		*
		*	\param[in] _rhs		Function handle to move.
		*
		*	\return this.
		*/
		PackedFunction& operator=(const PackedFunction& _rhs) noexcept;

	//}

	//{ Execute

		/**
		*	\brief \b Execute bound function with packed args.
		*
		*	\return Bound function result value.
		*/
		R Execute() const;


		/**
		*	\brief \b Execute bound function with packed args operator.
		*
		*	\return Bound function result value.
		*/
		R operator()() const;

	//}
	};


	/// \cond Internal

	/**
	*	\brief Template specialization for R(Args...) deduction.
	*
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class PackedFunction<R(Args...)> : public PackedFunction<R, Args...>
	{
	public:
		using PackedFunction<R, Args...>::PackedFunction;
		using PackedFunction<R, Args...>::operator=;
	};

	/// \endcond
}

#include <SA/Event/PackedFunction.inl>


/**
*	\example PackedFunctionTests.cpp
*	Examples and Unitary Tests for PackedFunction.
*/

/** \} */

#endif // GUARD
