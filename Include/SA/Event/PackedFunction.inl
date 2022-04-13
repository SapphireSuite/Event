// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
//{ Constructors

	template <typename R, typename... Args>
	PackedFunction<R, Args...>::PackedFunction(R(*_func)(Args...), Args... _args) noexcept :
		Function<R, Args...>(_func),
		mArgs{ std::forward<Args>(_args)... }
	{
	}

	template <typename R, typename... Args>
	template <typename C>
	PackedFunction<R, Args...>::PackedFunction(C* _caller, R(C::* _func)(Args...), Args... _args) :
		Function<R, Args...>(_caller, _func),
		mArgs{ std::forward<Args>(_args)... }
	{
	}


	template <typename R, typename... Args>
	PackedFunction<R, Args...>::PackedFunction(PackedFunction&& _other) noexcept :
		Function<R, Args...>(std::move(_other)),
		mArgs{ std::move(_other.mArgs) }
	{
	}

	template <typename R, typename... Args>
	PackedFunction<R, Args...>::PackedFunction(const PackedFunction& _other) noexcept :
		Function<R, Args...>(_other),
		mArgs{ _other.mArgs }
	{
	}

//}

//{ Equals

	template <typename R, typename... Args>
	bool PackedFunction<R, Args...>::Equals(const PackedFunction& _other) const
	{
		return Function<R, Args...>::Equals(_other) && mArgs == _other.mArgs;
	}

	template <typename R, typename... Args>
	bool PackedFunction<R, Args...>::operator==(const PackedFunction& _rhs) const
	{
		return Equals(_rhs);
	}

	template <typename R, typename... Args>
	bool PackedFunction<R, Args...>::operator!=(const PackedFunction& _rhs) const
	{
		return !Equals(_rhs);
	}

//}

//{ Set

	template <typename R, typename... Args>
	void PackedFunction<R, Args...>::Set(R(*_func)(Args...), Args... _args)
	{
		Function<R, Args...>::Set(_func);
		mArgs = std::tuple<Args...>{ std::forward<Args>(_args)... };
	}

	template <typename R, typename... Args>
	template <typename C>
	void PackedFunction<R, Args...>::Set(C* _caller, R(C::* _func)(Args...), Args... _args)
	{
		Function<R, Args...>::Set(_caller, _func);
		mArgs = std::tuple<Args...>{ std::forward<Args>(_args)... };
	}


	template <typename R, typename... Args>
	PackedFunction<R, Args...>& PackedFunction<R, Args...>::operator=(PackedFunction&& _rhs) noexcept
	{
		Function<R, Args...>::operator=(std::move(_rhs));
		mArgs = std::move(_rhs.mArgs);

		return *this;
	}

	template <typename R, typename... Args>
	PackedFunction<R, Args...>& PackedFunction<R, Args...>::operator=(const PackedFunction& _rhs) noexcept
	{
		Function<R, Args...>::operator=(_rhs);
		mArgs = _rhs.mArgs;

		return *this;
	}

//}

//{ Execute

	template <typename R, typename... Args>
	R PackedFunction<R, Args...>::Execute() const
	{
		const Function<R, Args...>& fThis = *this;

		return std::apply(fThis, mArgs);
	}


	template <typename R, typename... Args>
	R PackedFunction<R, Args...>::operator()() const
	{
		return Execute();
	}

//}
}
