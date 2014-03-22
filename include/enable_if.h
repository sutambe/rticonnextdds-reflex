/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative works
of the Software.  Licensee has the right to distribute object form only for use with RTI
products.  The Software is provided �as is�, with no warranty of any type, including
any warranty for fitness for any purpose. RTI is under no obligation to maintain or
support the Software.  RTI shall not be liable for any incidental or consequential
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef RTIREFLEX_ENABLE_IF_H
#define RTIREFLEX_ENABLE_IF_H

#include <tuple>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <array>
#include <type_traits>
#include <boost/range.hpp>
#include <boost/range/any_range.hpp>

#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/include/size.hpp>

#ifdef RTI_WIN32
#include <stdint.h>
#endif

struct DefaultBase;
typedef unsigned char octet_t;

template <class TagType, class... Cases>
struct Union;

template <class... T>
struct Sparse;

#ifdef RTI_WIN32

template <class T>
struct Range
  : boost::any_range <T,
                      boost::forward_traversal_tag,
                      T, std::ptrdiff_t >
{
  template <class... U>
  Range(U && ... u)
    : boost::any_range <T,
                        boost::forward_traversal_tag,
                        T, std::ptrdiff_t > (std::forward<U>(u)...)
  {}
};

#else

template <class T>
using Range = 
  boost::any_range<T, 
                   boost::forward_traversal_tag, 
                   T, std::ptrdiff_t>;

#endif

template <class T, size_t Bound>
struct BoundedRange : Range<T>
{
  template <class... U>
  BoundedRange(U&&... u)
    : Range<T>(std::forward<U>(u)...)
  {}
};

typedef unsigned char octet_t;

struct true_type {
  enum { value = true };
};

struct false_type {
  enum { value = false };
};

template <class T>
struct is_bool : false_type {};

template <>
struct is_bool<bool> : true_type {};

template <class T>
struct is_primitive : false_type {}; // enum

template <> struct is_primitive<octet_t>            : true_type {};
template <> struct is_primitive<bool>               : true_type {};
template <> struct is_primitive<char>               : true_type {};

#ifndef RTI_WIN32
template <> struct is_primitive<char32_t>           : true_type {};
#endif

template <> struct is_primitive<int16_t>            : true_type {};
template <> struct is_primitive<uint16_t>           : true_type {};
template <> struct is_primitive<int32_t>            : true_type {};
template <> struct is_primitive<uint32_t>           : true_type {};
template <> struct is_primitive<int64_t>            : true_type {};
template <> struct is_primitive<uint64_t>           : true_type {};
template <> struct is_primitive<float>              : true_type {};
template <> struct is_primitive<double>             : true_type {};
#if __x86_64__
template <> struct is_primitive<long long>          : true_type {};
template <> struct is_primitive<unsigned long long> : true_type {};
#endif 
template <> struct is_primitive<long double>        : true_type {};

template <class... Args>
struct is_primitive<std::tuple<Args...>> : false_type {};

template <>
struct is_primitive<std::string> : false_type {};

template <class T>
struct is_primitive<std::vector<T>> : false_type {};

template <class TagType, class... Cases>
struct is_primitive<Union<TagType, Cases...>> : false_type {};

template <class T>
struct is_primitive_or_enum
{
  enum { value = is_primitive<T>::value || std::is_enum<T>::value };
};

template <class T>
struct is_bool_or_enum
{
  enum { value = is_bool<T>::value || std::is_enum<T>::value };
};

template <class T>
struct is_primitive_and_not_bool
{
  enum { value = is_primitive<T>::value && !is_bool<T>::value  };
};

template <class T>
struct is_vector : false_type {};

template <class T>
struct is_vector<std::vector<T>> : true_type {};

template <class T>
struct is_vector<const std::vector<T>> : true_type {};

template <class T>
struct is_string : false_type {};

template <>
struct is_string<std::string> : true_type {};

template <>
struct is_string<const std::string> : true_type {};

template <class T>
struct is_tuple : false_type {};

template <typename... Args>
struct is_tuple<std::tuple<Args...>> : true_type {};

template <typename... Args>
struct is_tuple<const std::tuple<Args...>> : true_type {};

template <typename T>
struct is_stdarray : false_type {};

template <typename T, size_t N>
struct is_stdarray<std::array<T, N>> : true_type {};

template <typename T, size_t N>
struct is_stdarray<const std::array<T, N>> : true_type {};

template <class C>
struct is_stdset : false_type {};

template <class T, class Comp, class Alloc>
struct is_stdset<std::set<T, Comp, Alloc>> : true_type {};

template <class T, class Comp, class Alloc>
struct is_stdset<const std::set<T, Comp, Alloc>> : true_type {};

template <class T>
struct is_builtin_array : false_type {};

template <class T, size_t Dim>
struct is_builtin_array<T[Dim]> : true_type {};

template <class T, size_t Dim>
struct is_builtin_array<const T[Dim]> : true_type {};

template <class T>
struct is_builtin_array<T[]> : true_type {};

template <class T>
struct is_builtin_array<const T[]> : true_type {};

template <class T>
struct is_pointer : false_type {};

template <class T>
struct is_pointer<T *> : true_type {};

template <class T>
struct is_pointer<const T *> : true_type {};

template <class T>
struct is_container : false_type {};

template <class T, class Alloc>
struct is_container<std::vector<T, Alloc>> : true_type {};

template <class T, class Alloc>
struct is_container<const std::vector<T, Alloc>> : true_type {};

template <class T, class Alloc>
struct is_container<std::list<T, Alloc>> : true_type {};

template <class T, class Alloc>
struct is_container<const std::list<T, Alloc>> : true_type {};

template <class Key, class Comp, class Alloc>
struct is_container<std::set<Key, Comp, Alloc>> : true_type {};

template <class Key, class Comp, class Alloc>
struct is_container<const std::set<Key, Comp, Alloc>> : true_type {};

template <class Key, class T, class Comp, class Alloc>
struct is_container<std::map<Key, T, Comp, Alloc>> : true_type {};

template <class Key, class T, class Comp, class Alloc>
struct is_container<const std::map<Key, T, Comp, Alloc>> : true_type {};

template <class TagType, class... Cases>
struct Union;

template <class T>
struct is_union : false_type {};

template <class TagType, class... Args>
struct is_union<Union<TagType, Args...>> : true_type {};

template <class TagType, class... Args>
struct is_union<const Union<TagType, Args...>> : true_type {};

template <class T>
struct is_sparse : false_type {};

template <class... Args>
struct is_sparse<Sparse<Args...>> : true_type {};

template <class... Args>
struct is_sparse<const Sparse<Args...>> : true_type {};

template <class T>
struct is_range : false_type {};

template <class T>
struct is_range<Range<T>> : true_type {};

template <class T>
struct is_range<const Range<T>> : true_type {};

template <class T, size_t N>
struct is_range<BoundedRange<T, N>> : true_type {};

template <class T, size_t N>
struct is_range<const BoundedRange<T, N>> : true_type {};

template <class T>
struct is_default_member_names {
  enum { value = std::is_base_of<DefaultBase, T>::value };
};

template <bool, class T = void>
struct enable_if {
  typedef T type;
};

template <class T>
struct enable_if<false, T> {
};

template <bool, class T = void>
struct disable_if {
  typedef T type;
};

template <class T>
struct disable_if<true, T> {};

template <bool, class T = void>
struct disable_if_lazy {
  typedef typename T::type type;
};

template <class T>
struct disable_if_lazy<true, T> {};

template <size_t... Dims>
struct dim_list {
  enum { size = sizeof...(Dims) };
};

template <size_t Arg, class DimList>
struct dim_cat;

template <size_t Head, size_t... Args>
struct dim_cat<Head, dim_list<Args...>> {
  typedef dim_list<Head, Args...> type;
};

template <size_t Head>
struct dim_cat<Head, dim_list<0>> {
  typedef dim_list<Head> type;
};

template <class>
struct make_dim_list {
  typedef dim_list<0> type;
};

template <class T>
struct make_dim_list<T[]>;

struct Array_Dimensions_Must_Be_Greater_Than_Zero {};

template <class T>
struct make_dim_list<T[0]> {
 typedef Array_Dimensions_Must_Be_Greater_Than_Zero type;
};

template <class T>
struct make_dim_list<std::array<T, 0>> {
 typedef Array_Dimensions_Must_Be_Greater_Than_Zero type;
};

template <class T, size_t Dim>
struct make_dim_list<T[Dim]> {
  typedef typename dim_cat<Dim, typename make_dim_list<T>::type>::type type;
};

template <class T, size_t Dim>
struct make_dim_list<std::array<T, Dim>> {
  typedef typename dim_cat<Dim, typename make_dim_list<T>::type>::type type;
};

template <class T>
struct remove_reference {
  typedef T type;
};

template <class T>
struct remove_reference<T &> {
  typedef T type;
};

template<class T>
struct remove_all_extents { 
  typedef T type;
};
 
template<class T>
struct remove_all_extents<T[]> {
  typedef typename remove_all_extents<T>::type type;
};
 
template<class T, size_t N>
struct remove_all_extents<T[N]> {
  typedef typename remove_all_extents<T>::type type;
};

template <class T, size_t N>
struct remove_all_extents<std::array<T, N>> {
  typedef typename remove_all_extents<T>::type type;
};

template <size_t Head, size_t... Tail>
struct multiply {
  static const size_t value = 
    Head * multiply<Tail...>::value;
};

template <size_t N>
struct multiply<N> {
  static const uint64_t value = N;
};

template <class>
struct dim_list_multiply;

template <size_t... Dims>
struct dim_list_multiply<dim_list<Dims...>> {
  static const uint64_t value = multiply<Dims...>::value;
};

template <class T, size_t I, size_t... J>
struct MultiDimArray
{
  // using Nested = typename MultiDimArray<T, J...>::type;
  typedef typename MultiDimArray<T, J...>::type Nested;
  // using type = std::array<Nested, I>;
  typedef std::array<Nested, I> type;
};
 
template <class T, size_t I>
struct MultiDimArray<T, I>
{
  // using type = std::array<T, I>;
  typedef std::array<T, I> type;
};

template <class FusionSeq, size_t I>
struct At
{
  typedef typename 
    boost::fusion::result_of::at_c<FusionSeq, I>::type type;
};

template <class... Args, size_t I>
struct At<std::tuple<Args...>, I>
{
  typedef typename std::tuple_element<I, std::tuple<Args...>>::type type;
};

template <class... Args, size_t I>
struct At<const std::tuple<Args...>, I>
{
  // This is crazy!: I can't pass const tuple to std::tuple_element.
  // I've to attach const to the result of tuple_element.
  // This is unlike Boost Fusion Sequences up above.
  //
  // I'm not sure if this will even work for references
  // because const references is redundant because references never change.
  typedef typename std::tuple_element<I, std::tuple<Args...>>::type const type;
};

template <class First, class Second, size_t I>
struct At<std::pair<First, Second>, I>
{
  typedef typename std::tuple_element<I, std::pair<First,Second>>::type type;
};

template <class First, class Second, size_t I>
struct At<const std::pair<First, Second>, I>
{
  typedef typename std::tuple_element<I, std::pair<First, Second>>::type const type;
};

template <class FusionSeq>
struct Size
{
  enum { value = boost::fusion::result_of::size<FusionSeq>::type::value };
};

template <class First, class Second>
struct Size<std::pair<First, Second>>
{
  enum { value = 2 };
};

template <class First, class Second>
struct Size<const std::pair<First, Second>>
{
  enum { value = 2 };
};

template <class... Args>
struct Size<std::tuple<Args...>>
{
  enum { value = std::tuple_size<std::tuple<Args...>>::value };
};

template <class... Args>
struct Size<const std::tuple<Args...>>
{
  enum { value = std::tuple_size<const std::tuple<Args...>>::value };
};

template <size_t I, class FusionSeq>
typename disable_if_lazy<is_tuple<FusionSeq>::value,
                         At<FusionSeq, I>>::type
Get(FusionSeq & seq)
{
  return boost::fusion::at_c<I>(seq);
}

template <size_t I, class FusionSeq>
typename disable_if_lazy<is_tuple<FusionSeq>::value,
                         At<const FusionSeq, I>>::type
Get(const FusionSeq & seq)
{
  return boost::fusion::at_c<I>(seq);
}

template <size_t I, class... Args>
// Note reference (ref) at the end.
typename At<std::tuple<Args...>, I>::type &
  Get(std::tuple<Args...> & tuple)
{
  return std::get<I>(tuple);
}

template <size_t I, class... Args>
// Note reference (ref) at the end.
typename At<const std::tuple<Args...>, I>::type &
  Get(const std::tuple<Args...> & tuple)
{
  return std::get<I>(tuple);
}

template <size_t I, class First, class Second>
// Note reference (ref) at the end.
typename At<std::pair<First, Second>, I>::type &
  Get(std::pair<First, Second> & pair)
{
  return std::get<I>(pair);
}

template <size_t I, class First, class Second>
// Note reference (ref) at the end.
typename At<const std::pair<First, Second>, I>::type &
  Get(const std::pair<First, Second> & pair)
{
  return std::get<I>(pair);
}

template <class T>
struct remove_refs
{
  typedef T type;
};

template <class... Args>
struct remove_refs<std::tuple<Args...>>
{
  typedef std::tuple<typename remove_reference<Args>::type...> type;
};

template <class... Args>
struct remove_refs<const std::tuple<Args...>>
{
  typedef const std::tuple<typename remove_reference<Args>::type...> type;
};

#endif // RTIREFLEX_ENABLE_IF_H
