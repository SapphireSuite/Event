# Event

[![Unix](https://github.com/SapphireSuite/Event/actions/workflows/test_unix.yml/badge.svg)](https://github.com/SapphireSuite/Event/actions/workflows/test_unix.yml)
[![Windows](https://github.com/SapphireSuite/Event/actions/workflows/test_windows.yml/badge.svg)](https://github.com/SapphireSuite/Event/actions/workflows/test_windows.yml)
[![MacOS](https://github.com/SapphireSuite/Event/actions/workflows/test_macos.yml/badge.svg)](https://github.com/SapphireSuite/Event/actions/workflows/test_macos.yml)

Sapphire Suite's C++ Event and Function library.\
Links to the **official** [documentation](https://SapphireSuite.github.io/Event/).



# How To Use

## CMake
Add the subdirectory to the build tree with
```cmake
add_subdirectory(Event)
```
and link the library to your taget with
```cmake
target_link_libraries(<target> <link> SA_Event)
```


## I. Event
Create your **event** of type *Event<R(Args)>* with *R* as **return type** and _Args_ as **argument types**:
```cpp
Event<void(int)> ev;
```
Then **subscribe**/**unsubscribe** functions to the event:
```cpp
struct MyStruct
{
	void Bar(int _i);
	static void Foo(int _i);
};

// Static function.
ev += &MyStruct::Foo;

// Member function.
MyStruct mem;
ev.Add(&mem, &MyStruct::Bar);

// Lambda function.
auto lambda = [](int _i) {};
ev += lambda;

// Unsubscribe.
ev.Remove(&mem, &MyStruct::Bar);
ev -= lambda;
```
To **raise** the event, simply use the *operator()* or the *Execute* method:
```cpp
ev(5);
ev.Execute(6);
```
For event with return types, you can pass a _std::vector<R>_ to get the output results:
```cpp
Event<float(int)> rev;
std::vector<float> results;
rev.Execute(results, 7);
```
For more examples, see [Event Unit Tests](https://github.com/SapphireSuite/Event/blob/main/Tests/UnitTests/EventTests.cpp).


## II. Function
_Function_ is used to easliy store a pointer to function.
Create your **function** of type *Function<R(Args)>* with *R* as **return type** and _Args_ as **argument types**:
```cpp
Function<void(int)> func;
```
Then **assign** a function:
```cpp
struct MyStruct
{
	void Bar(int _i);
	static void Foo(int _i);
};

// Static function.
func = &MyStruct::Foo;

// Member function.
MyStruct mem;
func.Set(&mem, &MyStruct::Bar);

// Lambda function.
auto lambda = [](int _i) {};
func = lambda;

// Clear.
func.Clear();
func = nullptr;
```
To **raise** the function, simply use the *operator()* or the *Execute* method:
```cpp
func(5);
func.Execute(6);
```
For function with return types, the value is normally returned:
```cpp
Function<float(int)> rfunc;
float result = rfunc.Execute(7);
```
For more examples, see [Function Unit Tests](https://github.com/SapphireSuite/Event/blob/main/Tests/UnitTests/FunctionTests.cpp).

## III. PackedFunction
PackedFunction is used to easliy store a pointer to function with **packed** arguments.
Create your **packed function** of type *PackedFunction<R(Args)>* with *R* as **return type** and _Args_ as **argument types**:
```cpp
PackedFunction<void(int)> pfunc;
```
Then **assign** a function:
```cpp
struct MyStruct
{
	void Bar(int _i);
	static void Foo(int _i);
};

// Static function.
pfunc.Set(&MyStruct::Foo, 5);

// Member function.
MyStruct mem;
pfunc.Set(&mem, &MyStruct::Bar, 5);

// Lambda function.
auto lambda = [](int _i) {};
pfunc.Set(lambda, 5);

// Clear.
pfunc.Clear();
pfunc = nullptr;
```
To **raise** the packed function, simply use the *operator()* or the *Execute* method:
```cpp
pfunc();
pfunc.Execute();
```
For function with return types, the value is normally returned:
```cpp
PackedFunction<float(int)> rpfunc;
float result = rpfunc.Execute();
```
For more examples, see [Packed Unit Tests](https://github.com/SapphireSuite/Event/blob/main/Tests/UnitTests/PackedFunctionTests.cpp).



# Authors

**Maxime "mrouffet" ROUFFET** - main developer (maximerouffet@gmail.com)
