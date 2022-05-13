// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

namespace SA
{
	namespace Intl
	{
		template <typename C, typename R, typename... Args>
		FuncMemberData<C, R, Args...>::FuncMemberData(C* _caller, R(C::* _func)(Args...)) :
			caller{ _caller },
			func{ _func }
		{
			SA_ASSERT(Nullptr, SA/Event/Function, _caller);
			SA_ASSERT(Nullptr, SA/Event/Function, _func);
		}

		template <typename C, typename R, typename... Args>
		FuncMemberDataBase* FuncMemberData<C, R, Args...>::Duplicate() const
		{
			return new FuncMemberData(caller, func);
		}

		template <typename C, typename R, typename... Args>
		bool FuncMemberData<C, R, Args...>::Compare(const FuncMemberDataBase* _other) const
		{
			SA_ASSERT(Nullptr, SA/Event/Function, _other, L"Compare with internal data nullptr");
			const FuncMemberData* const otherData = reinterpret_cast<const FuncMemberData*>(_other);

			return caller == otherData->caller && func == otherData->func;
		}


		template <typename C, typename R, typename... Args>
		R FuncMemberData<C, R, Args...>::InterfaceCall(void* _data, Args... _args)
		{
			FuncMemberData* const fData = reinterpret_cast<FuncMemberData*>(_data);

			SA_ASSERT(Nullptr, SA/Event/Function, fData, L"Internal function call: data nullptr!");

			return (fData->caller->*fData->func)(std::forward<Args>(_args)...);
		}
	}

}