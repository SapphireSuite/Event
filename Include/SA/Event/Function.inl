// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
//{ Constructors

	template <typename R, typename... Args>
	Function<R, Args...>::Function(R(*_func)(Args...)) noexcept :
		mData{ nullptr },
		mSFunc{ _func }
	{
	}

	template <typename R, typename... Args>
	template <typename C>
	Function<R, Args...>::Function(C* _caller, R(C::* _func)(Args...)) :
		mData{ new Intl::FuncMemberData<C, R, Args...>(_caller, _func) },
		mIntlFunc{ Intl::FuncMemberData<C, R, Args...>::InterfaceCall }
	{
	}


	template <typename R, typename... Args>
	Function<R, Args...>::Function(Function&& _other) noexcept
	{
		if (_other.mData)
		{
			mData = _other.mData;
			_other.mData = nullptr;

			mIntlFunc = _other.mIntlFunc;
			_other.mIntlFunc = nullptr;
		}
		else
		{
			mSFunc = _other.mSFunc;
			_other.mSFunc = nullptr;
		}
	}

	template <typename R, typename... Args>
	Function<R, Args...>::Function(const Function& _other) noexcept
	{
		if (_other.mData)
		{
			mData = _other.mData->Duplicate();
			mIntlFunc = _other.mIntlFunc;
		}
		else
			mSFunc = _other.mSFunc;
	}

	template <typename R, typename... Args>
	Function<R, Args...>::~Function()
	{
		Clear();
	}

//}

//{ Equals

	template <typename R, typename... Args>
	bool Function<R, Args...>::IsEmpty() const noexcept
	{
		return !mSFunc;
	}

	template <typename R, typename... Args>
	Function<R, Args...>::operator bool() const
	{
		return mSFunc;
	}


	template <typename R, typename... Args>
	bool Function<R, Args...>::Equals(const Function& _other) const
	{
		if (mData)
		{
			if (_other.mData)
				return mData->Compare(_other.mData);
		}
		else if (mSFunc)
			return mSFunc == _other.mSFunc;

		return false;
	}

	template <typename R, typename... Args>
	bool Function<R, Args...>::operator==(const Function& _rhs) const
	{
		return Equals(_rhs);
	}

	template <typename R, typename... Args>
	bool Function<R, Args...>::operator!=(const Function& _rhs) const
	{
		return !Equals(_rhs);
	}

//}

//{ Set

	template <typename R, typename... Args>
	void Function<R, Args...>::Clear()
	{
		if (mData)
		{
			delete mData;
			mData = nullptr;
		}

		mSFunc = nullptr;
	}


	template <typename R, typename... Args>
	void Function<R, Args...>::Set(R(*_func)(Args...))
	{
		Clear();

		mSFunc = _func;
	}

	template <typename R, typename... Args>
	template <typename C>
	void Function<R, Args...>::Set(C* _caller, R(C::* _func)(Args...))
	{
		Clear();

		mData = new Intl::FuncMemberData<C, R, Args...>(_caller, _func);
		mIntlFunc = Intl::FuncMemberData<C, R, Args...>::InterfaceCall;
	}


	template <typename R, typename... Args>
	Function<R, Args...>& Function<R, Args...>::operator=(Function&& _rhs) noexcept
	{
		Clear();

		if (_rhs.mData)
		{
			mData = _rhs.mData;
			_rhs.mData = nullptr;

			mIntlFunc = _rhs.mIntlFunc;
			_rhs.mIntlFunc = nullptr;
		}
		else
		{
			mSFunc = _rhs.mSFunc;
			_rhs.mSFunc = nullptr;
		}

		return *this;
	}


	template <typename R, typename... Args>
	Function<R, Args...>& Function<R, Args...>::operator=(const Function& _rhs) noexcept
	{
		Clear();

		if (_rhs.mData)
		{
			mData = _rhs.mData->Duplicate();
			mIntlFunc = _rhs.mIntlFunc;
		}
		else
			mSFunc = _rhs.mSFunc;

		return *this;
	}


	template <typename R, typename... Args>
	Function<R, Args...>& Function<R, Args...>::operator=(R(*_func)(Args...)) noexcept
	{
		Set(_func);

		return *this;
	}
//}

//{ Execute

	template <typename R, typename... Args>
	R Function<R, Args...>::Execute(Args... _args) const
	{
		if (mData)
			return mIntlFunc(mData, std::forward<Args>(_args)...);
		else if(mSFunc)
			return mSFunc(std::forward<Args>(_args)...);

		return R();
	}

	template <typename R, typename... Args>
	R Function<R, Args...>::operator()(Args... _args) const
	{
		return Execute(std::forward<Args>(_args)...);
	}

//}
}
