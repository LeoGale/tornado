# template
## generic template
template<typename T>
class Foo {

};

template<typename T>
void foo( T t);
## variadic template

* Args... defines what is called a "parameter pack". That's basically a sequence of (type/value) pairs from which you can "peel off" arguments starting with the first.
* How the program unpack the Args...
  * printf
      1. To build a type-safe printf.
  * count
  * tuple
      1. To implement a tuple
        2. To implement a tuple helper class
  * invoke
      1. to implement a invoke, like invoke(f, t1, t2, ..., tN)
        1.1 (t1.*f)(t2, ..., tN) when f is a pointer to a member function of a class T.
        1.2 ((*t1).*f)(t2,..., tN)
        1.3 t1.*f when f is a pointer to member data of a class T.
        1.4 (*t1).*f
        1.5 f(t1,t2,...,tN) in all other cases.
        1.6 zeroCopy parameters??

### member pointer of template class
#### A pointer to non-static member function
* have a hidden parameter that corresponds to the this pointer which points to the instance data for the object[RpcCallback]().
* A member function is meaningless without an object to invoke it on.
* Can Not convert a pointer to non-static member function to void\*
* Don't forget the const keyword if member function has const qualifier.
#### A pointer to static member function
* static member functions do not require an actual object to be invoked, so pointers-to-static-member-functions are usually type-compatible with regular pointers-to-functions.
* It actually would have to be an __extern "C"__ non-member function to be correct, since "C linkage" doesn't only cover things like name mangling, but also calling conventions, which might be different between C and C++.

#### Reference

```C++
#define CALL_MEMBER_FUNC(object, memFuncPtr) ((object).*(memFuncPtr))
int hello()
{
    return 1;
}
class Foo {
public:
    int cal(char lhs, float rhs){return 0;}
    int age() const {return age_;}
    static void say(){std::cout <<"I'm leon" << std::endl;}
private:
    int age_;
};

typedef int (Foo::*MemFuncPtr)(char, float);
typedef int (*GlobalFuncPtr)(char, float);
typedef int (Foo::*constMemFuncPtr)();
int main()
{
    Foo aFoo;
    //normal member function pointer
    MemFuncPtr calFunc = &Foo::cal;
    (aFoo.*calFunc)('a', 0.123);
    CALL_MEMBER_FUNC(aFoo, calFunc)('a', 0.123);
    //const member function pointer
    ConstMemFuncPtr ageFunc = &Foo::age;
    (aFoo.*ageFunc)();

    //global function

    GlobalFuncPtr sayStatFunc = &Foo::say;
    sayStatFunc();

    GlobalFuncPtr helloFunc = hello;
    helloFunc();

}
```

```C++
#include <functional>
#include <iostream>
#define USE_PTR
#define CALL_MEMBER_FUNC(object, memFuncPtr) ((object).*(memFuncPtr))
class Foo {
    public:
        void say(){
            std::cout <<"I'm a Foo, age is " <<age_  << std::endl;
        };
        void setAge(int age)
        {
            age_ = age;
        }
    private:
        int age_{1};
};
#ifdef USE_PTR
using FooSayFunc = std::function<void(Foo*)>;
#else
using FooSayFunc = std::function<void(Foo&)>;
//using FooSayFunc = std::function<void(Foo)>;
#endif

using FooMemPtr = void(Foo::*)();
//typedef void(Foo::*FooMemPtr)();

int main()
{
    Foo aFoo;
    FooSayFunc aFunc = &Foo::say;
#ifdef USE_PTR
    aFunc(&aFoo);
#else
    aFunc(aFoo);//aFunc(std::ref(aFoo));
#endif
    aFoo.setAge(2);
#ifdef USE_PTR
    aFunc(&aFoo);
#else
    aFunc(aFoo);//aFunc(std::ref(aFoo));
#endif
    aFoo.setAge(3);

    FooMemPtr aMemFunc = &Foo::say;
    //(aFoo.*aMemFunc)();
    CALL_MEMBER_FUNC(aFoo, aMemFunc)();
}

```

#### A pointer to static member function
* **Conclusion**
Using the expression __int(CLASS: : *)__ to present a member pointer(member object pointer or member function pointer), int is non-meaningful, it can be double, long, be any concrete type that the compiler can know.

Using __(T CLASS: : \*)__ to declare a member function pointer which return type is T


* **Practice**
EventCallback in Epoll
```C++

```

### template function

```C++
template<typename T>
add(T lhs, T rhs)->decltype(lhs+rhs)
{
    return (lhs + rhs);
}
```

### template class

```C++
template <typename T>
class A {
    T t_;
};
```

## partial template specialization

```C++
template<class T1, class T2, int I>
class A{};
```

> partial specialization where T2 is a pointer to T1

```C++
template <class T, int I>
class A<T, T*, I> {};
```

> partial specialization where T1 is a pointer

```C++
template <class T, class T2, int I>
class A<T*, T2, I> {};
```

> partial specialization where T1 is a Int, I is 5, and T2 is a pointer

```C++
template <class T>
class A<int, T*, 5> {};
```

> Partial specialization where T2 is a pointer

```C++
template<class X, class T, int I>
class <X, T*, I> {};
```

### partial specialization requires

* The argument list cannot be identical to the non-specialized argument list.

```C++
template<class T1, class T2, int I> class B{}; //primary template
template<class X, class Y, int N> classB<X,Y,N> {};//error
```

```C++
//c++14
template<int N, typename T1, typename... Ts> struct B;
template<typename... Ts> struct B<0, Ts...> {};//Error: not more specialized
```
* Default arguments cannot appear int the argument list
* If any argument is a pack expansion, it must be the last argument in the list
* Non-type argument expression cannot use the name of the template parameter except when it is exactly the name of the template parameter(util c++14) Non-type argument expressions can use template parameters as long as the parameter appears at least once outside a non-deduced context(since C++14)

```C++
template <int I, int J> struct A {};
template <int I> struct A<I+5, I*2> {}; // error, I is not deducible

template <int I, int J, int K> struct B {};
template <int I> struct B<I, I*2, 2> {};  // OK: first parameter is deducible
```
* Non-type template argument cannot specialize a template parameter whose type depends on a parameter of the specialization

```C++
template <class T, T t> struct C{};//primary template
template <class T> struct C<T, 1>; //error: type of the argument 1 is T,
                                   // which depends on the parameter T
template<int X, int (*array_ptr)[X]> class B{}; //primary template

int array[5];

template<int X. class B<X, &array>{};//error: type of the argument &array is int(*)[X], which depends on the parameter X
```

### Name lookup
In particular, a using declaration that makes a primary template visiable, makes partial specializations visible as well:

```C++
namespace N {
    template<class T1, class T2> class Z {};//primary template
}

using N::Z;//refers to the primary template

namespace N {
    template<class T> class Z<T, T*>{};//partial specialization
}

Z<int, int*> z;//name lookup finds N::Z(the primary specialization),
		// the partial specialization with T = int is then used
```

### Partial ordering

When a class or visiable(since C++14) template is instantiated, and there are partial specializations available, the compiler has to decide if the primary template is going to be used or one of its partial specializations.

* If only one specialization matchs the template arguments, that specialization is used.
* If more than one specialization matchs, partial order rules are used to determine which specialization is more specialized. The most specialized specialization is used, if it is unique(if it is not unique, the program cannot be compiled)
* If no specializations match, the primary template is used

```C++
template<class T1, class T2, int I>
class A {};            // primary template

template<class T, int I>
class A<T, T*, I> {};  // #1: partial specialization where T2 is a pointer to T1

template<class T, class T2, int I>
class A<T*, T2, I> {}; // #2: partial specialization where T1 is a pointer

template<class T>
class A<int, T*, 5> {}; // #3: partial specialization where T1 is int, I is 5,
                        //     and T2 is a pointer

 template<class X, class T, int I>
 class A<X, T*, I> {};   // #4: partial specialization where T2 is a pointer

 A<int, int, 1> a1; //no specialization match, uses primary template
 A<int, int*, 1> a2; // uses partial specialization #1(T=int, I=1)
 A<int, char*, 5> a3; //uses partial specialiation #3, (T= char)
 A<int, char*, 1> a4; //uses partial specialization #4, (X = int, T=char, I=1)

 A<int*, int*, 2> a5; //error: matches #2(T=int, T2=int*, I=2)
		      //               #4(X=int*, T=int, I=2)
                      // neither one is more specialized than the other

 ```

* How to judge which one is more specialized.

```C++
template<int I, int J, class T> struct X { }; // primary template
template<int I, int J>          struct X<I, J, int> {
        static const int s = 1;
}; // partial specialization #1
// fictitious function template for #1 is
// template<int I, int J> void f(X<I, J, int>); #A

template<int I>                 struct X<I, I, int> {
        static const int s = 2;
}; // partial specialization #2
// fictitious function template for #2 is
// template<int I>        void f(X<I, I, int>); #B

int main()
{
    X<2, 2, int> x; // both #1 and #2 match
// partial ordering for function templates:
// #A from #B: void(X<I,J,int>) from void(X<U1, U1, int>): deduction ok
// #B from #A: void(X<I,I,int>) from void(X<U1, U2, int>): deduction fails
// #B is more specialized
// #2 is the specialization that is instantiated
    std::cout << x.s << '\n'; // prints 2
}
```

### Members of partial specializations

* Members of partial specializations are not related to the members of the primary template

* Explicit(full) specialization of a member of a partial a partial specialization is declared the same way as an explicit specialization of the primary template

```C++
template<class T, int I>  // primary template
struct A {
    void f(); // member declaration
};

template<class T, int I>
void A<T,I>::f() { } // primary template member definition

// partial specialization
template<class T>
struct A<T,2> {
    void f();
    void g();
    void h();
};

// member of partial specialization
template<class T>
void A<T,2>::g() { }

// explicit (full) specialization
// of a member of partial specialization
template<>
void A<char,2>::h() {}

int main() {
    A<char,0> a0;
    A<char,2> a2;
    a0.f(); // OK, uses primary template’s member definition
    a2.g(); // OK, uses partial specialization's member definition
    a2.h(); // OK, uses fully-specialized definition of
            // the member of a partial specialization
    a2.f(); // error: no definition of f() in the partial
            // specialization A<T,2> (the primary template is not used)
}
```

* If a primary template is a member of another class template, its partial specialization are members of the enclosing class template.

* If the primary member template is explicitly (fully) specialized for a given (implicit) specialization of the enclosing class template, the partial specializations of the member template are ignored for this specialization of the enclosing class template.

* If a partial specialization of the member template is explicitly specialized for a given (implicit) specialization of the enclosing class template, the primary member template and its other partial specializations are still considered for this specialization of the enclosing class template.

```C++
template<class T> struct A { // enclosing class template
  template<class T2>
  struct B {}; // primary member template
  template<class T2>
  struct B<T2*> {}; // partial specialization of member template
};

template<>
template<class T2>
struct A<short>::B {}; // full specialization of primary member template
                       // (will ignore the partial)

A<char>::B<int*> abcip; // uses partial specialization T2=int
A<short>::B<int*> absip; // uses full specialization of the primary (ignores partial)
A<char>::B<int> abci; // uses primary
```
### practice
>T is R(Args...)
U is a CLASS
For instance:
  void func(int param);
  void Foo::setAge(int age) {/*implementation*/}
  is_member_pointer<decltype(&Foo::setAge)>::value;
  in instataiation of is_member_pointer_help<T U::*>
  T is same as func, U is same as Foo

* __is_member_function_pointer__

    ```C++
    template<class T>
    struct is_member_pointer_helper : std::false_type{};

    template<typename T, class U>
    struct is_member_pointer_helper<T U::*> : std::true_type{};

    template<class T>
    struct is_member_pointer : is_member_pointer_helper<typename std::remove_cv<T>::type> {};
    ```

### FAQ

* What the heck is a functionoid, and why would I use one?
* What's the difference between a functionoid and a functor?
* Can you make functionoids faster than normal function calls?
* What's the difference between a pointer to member function and a pointer to function?
