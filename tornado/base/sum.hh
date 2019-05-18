#pragma once

  namespace tornado {
  template<typename... Args> struct Count;
  template<typename T, typename... Args>
  struct Count<T, Args...> {
      static constexpr int value = sizeof(T) + Count<Args...>::value;
      static_assert( 1 == sizeof...(Args), "args size is not equal 2");
  };

  template<typename T>
  struct Count<T>
  {
      static constexpr int value = sizeof(T);
      static_assert(sizeof(T) == sizeof(int), "the first element should be char ");
  };
  /*
  template<typename T>
  T add(T lhs, T rhs)
  {
    return (lhs + rhs);
  }
  */

  }
