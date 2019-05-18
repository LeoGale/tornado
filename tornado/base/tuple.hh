#pragma once
namespace tornado
{

template<typename... Elements> class tuple;
template<typename Head, typename... Tail>
struct tuple<Head, Tail...> : private tuple<Tail...>
{

};
template<typename Head>
struct tuple<Head>{
  Head head_; 
};
/*
template<typename... Types>
class tuple_size<tuple<Types...>>
: public integral_constant<size_t, sizeof...(Types)>{};
*/
template<typename... Types>
tuple<Types...> make_tuple(Types... types)
{
    return tuple<Types...>(types...);
}
}
