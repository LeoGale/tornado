#pragma once 

#include <type_traits>

void f(int a)
{
    (void)a;
    return;
}

namespace tornado 
{
    template <typename C>
    struct is_member_pointer_helper : std::false_type{};

    template <typename C, typename U>
    struct is_member_pointer_helper<C U::*> : std::true_type{};

    template <typename C>
    struct is_member_pointer : is_member_pointer_helper<typename std::remove_cv<C>::type> {};

    template <class>
    struct is_function : std::false_type {};

    //NOTE: Ret indicate the function return type
    //NOTE: Args indicate the function's parameter type
    template<class Ret, class... Args>
    struct is_function<Ret(Args...)> : std::true_type {
	//static_assert(sizeof...(Args) == 1, "args size should be 1");
    };

    template<typename T>
    struct is_member_function_pointer_helper : std::false_type {};

    //NOTE: T indicate the function type, like void(int); Test case is a void (Foo::*)(int)
    template<typename T, class U>
    struct is_member_function_pointer_helper<T U::*> : is_function<T> {
	static_assert(std::is_same<decltype(f), T>::value, "T is not equal to void f()");
	static U u_;
    };

    template<typename T>
    struct is_member_function_pointer : is_member_function_pointer_helper<typename std::remove_cv<T>::type> {};

}
