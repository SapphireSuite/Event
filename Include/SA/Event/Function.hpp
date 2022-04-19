// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_EVENT_FUNCTION_GUARD
#define SAPPHIRE_EVENT_FUNCTION_GUARD

#include <SA/Event/FunctionMemberData.hpp>

/**
*	\file Function.hpp
*
*	\brief \b Definition of Sapphire \b Function type.
*
*	\ingroup Event
*	\{
*/


namespace Sa
{
	/**
	*	\brief \b Function type implementation.
	* 
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Function
	{
		/// Abstract member data (used by function interface for member function call).
		Intl::FuncMemberDataBase* mMemberData = nullptr;

		union
		{
			/// Static function ptr.
			R(*mSFunc)(Args...) = nullptr;

			/// Internal interface function ptr (handle for member function call).
			R(*mIntlFunc)(void*, Args...);
		};

	public:

//{ Constructors

		/// Default constructor.
		Function() = default;

		/**
		*	\e Value constructor with static function.
		* 
		*	\param[in] _func	Static function to bind.
		*/
		Function(R(*_func)(Args...)) noexcept;

		/**
		*	\e Value constructor with member function.
		* 
		*	\tparam C			Caller type.
		*	\param[in] _caller	Object caller of member function.
		*	\param[in] _func	Member function to bind.
		*/
		template <typename C>
		Function(C* _caller, R(C::*_func)(Args...));


		/**
		*	\e Move constructor.
		*	Steal function handle (no additional memory allocation).
		* 
		*	\param[in] _other	Other handle to move.
		*/
		Function(Function&& _other) noexcept;

		/**
		*	\e Copy constructor.
		*	Additional memory allocation on member function copy.
		* 
		*	\param[in] _other	Other handle to copy.
		*/
		Function(const Function& _other) noexcept;

		/// Destructor (free memory).
		~Function();

//}

//{ Equals

		/**
		*	\brief Check whether this function handle is <b>empty</b> (no function bound).
		*
		*	\returns true if empty.
		*/
		bool IsEmpty() const noexcept;

		/**
		*	\brief !IsEmpty bool operator.
		* 
		*	\return true if non empty.
		*/
		operator bool() const;


		/**
		*	\brief \e Compare 2 function handle.
		*
		*	\param[in] _other		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool Equals(const Function& _other) const;

		/**
		*	\brief \e Compare 2 function handle equality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool operator==(const Function& _rhs) const;


		/**
		*	\brief \e Compare 2 function handle inequality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are non-equal.
		*/
		bool operator!=(const Function& _rhs) const;

//}

//{ Set

		/**
		*	\brief <b>Clear</b> bound function.
		*	Free allocated memory.
		*/
		void Clear();


		/**
		*	\brief Set (assignation) new <b>static function</b> to bind.
		*	Free previous allocated memory.
		* 
		*	\param[in] _func	New static function to bind.
		*/
		void Set(R(*_func)(Args...));
		
		/**
		*	\brief Set (assignation) new <b>member function</b> to bind.
		*	Free previous allocated memory.
		* 
		*	\tparam C			Caller type.
		*	\param[in] _caller	New object caller of member function.
		*	\param[in] _func	New member function to bind.
		*/
		template <typename C>
		void Set(C* _caller, R(C::* _func)(Args...));


		/**
		*	\brief Move operator
		*	Steal function handle (no additional memory allocation).
		* 
		*	\param[in] _rhs		Function handle to move.
		* 
		*	\return this.
		*/
		Function& operator=(Function&& _rhs) noexcept;

		/**
		*	\brief Copy operator
		*	Additional memory allocation on member function copy.
		* 
		*	\param[in] _rhs		Function handle to move.
		* 
		*	\return this.
		*/
		Function& operator=(const Function& _rhs) noexcept;


		/**
		*	\e Value assignation with static function.
		*	Free previous allocated memory.
		*
		*	\param[in] _func	Static function to bind.
		* 
		*	\return this
		*/
		Function& operator=(R(*_func)(Args...)) noexcept;

		//template <typename C>
		//Function& operator=(C* _caller, R(C::* _func)(Args...));

//}

//{ Execute

		/**
		*	\brief \b Execute bound function with args.
		* 
		*	\param[in] _args	Argument to forward to bound function.
		* 
		*	\return Bound function result value.
		*/
		R Execute(Args... _args) const;


		/**
		*	\brief \b Execute bound function with args operator.
		* 
		*	\param[in] _args	Argument to forward to bound function.
		* 
		*	\return Bound function result value.
		*/
		R operator()(Args... _args) const;

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
	class Function<R(Args...)> : public Function<R, Args...>
	{
	public:
		using Function<R, Args...>::Function;
		using Function<R, Args...>::operator=;
	};

	/// \endcond
}

#include <SA/Event/Function.inl>


/** \} */

#endif // GUARD
