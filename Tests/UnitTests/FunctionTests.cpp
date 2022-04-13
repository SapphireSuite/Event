// Copyright(c) 2022 Sapphire's Suite. All Rights Reserved.

#include <gtest/gtest.h>

#include <SA/Event/Function.hpp>
using namespace Sa;

namespace Sa::UT::FunctionTest
{
//{ Variables

	int Foo(int _i)
	{
		return _i * 2;
	}

	class A
	{
	public:
		int Bar(int _i)
		{
			return _i * 3;
		}
	};

//}

	TEST(Function, ValueConstructors)
	{
		Function<int(int)> f1;
		EXPECT_TRUE(f1.IsEmpty());

		Function f2 = Foo;
		EXPECT_FALSE(f2.IsEmpty());
		EXPECT_EQ(f2(2), 4);

		A a;
		Function f3(&a, &A::Bar);
		EXPECT_FALSE(f3.IsEmpty());
		EXPECT_EQ(f3(2), 6);
	}

	TEST(Function, MoveConstructors)
	{
		// Static function move.
		Function f1 = Foo;
		const Function f2 = std::move(f1);
		EXPECT_TRUE(f1.IsEmpty());
		EXPECT_FALSE(f2.IsEmpty());
		EXPECT_EQ(f2(2), 4);

		// Member function move.
		A a;
		Function f3(&a, &A::Bar);
		const Function f4 = std::move(f3);
		EXPECT_TRUE(f3.IsEmpty());
		EXPECT_FALSE(f4.IsEmpty());
		EXPECT_EQ(f4(2), 6);
	}

	TEST(Function, CopyConstructors)
	{
		// Static function copy.
		const Function f1 = Foo;
		const Function f2 = f1;
		EXPECT_EQ(f2(2), 4);

		// Member function copy.
		A a;
		const Function f3(&a, &A::Bar);
		const Function f4 = f3;
		EXPECT_EQ(f4(2), 6);
	}

	TEST(Function, Equals)
	{
		A a;
		const Function f1 = Foo;
		const Function f2(&a, &A::Bar);

		EXPECT_TRUE(f1.Equals(f1));
		EXPECT_FALSE(f1.Equals(f2));

		EXPECT_EQ(f1, f1);
		EXPECT_FALSE(f1 == f2);

		EXPECT_NE(f1, f2);
		EXPECT_FALSE(f1 != f1);


		Function f3 = Foo;
		EXPECT_FALSE(f3.IsEmpty());

		f3.Clear();
		EXPECT_TRUE(f3.IsEmpty());
	}

	TEST(Function, MoveOperators)
	{
		// Static function move.
		Function f1 = Foo;
		Function<int(int)> f2;
		f2 = std::move(f1);
		EXPECT_TRUE(f1.IsEmpty());
		EXPECT_FALSE(f2.IsEmpty());
		EXPECT_EQ(f2(2), 4);

		// Member function move.
		A a;
		Function f3(&a, &A::Bar);
		Function<int(int)> f4;
		f4 = std::move(f3);
		EXPECT_TRUE(f3.IsEmpty());
		EXPECT_FALSE(f4.IsEmpty());
		EXPECT_EQ(f4(2), 6);
	}

	TEST(Function, CopyOperators)
	{
		// Static function copy.
		const Function f1 = Foo;
		Function<int(int)> f2;
		f2 = f1;
		EXPECT_FALSE(f1.IsEmpty());
		EXPECT_EQ(f2(2), 4);

		// Member function copy.
		A a;
		const Function f3(&a, &A::Bar);
		Function<int(int)> f4;
		f4 = f3;
		EXPECT_FALSE(f1.IsEmpty());
		EXPECT_EQ(f4(2), 6);
	}
}
