#include <eggs/type_patterns.hpp>

using namespace eggs::type_patterns;

/** 20.9.4.1 primary type categories **/

// checks if a type is void
template< typename T >
struct is_void
  : match<
        T
      , ignore_cv< void >
    >
{};

// checks if a type is integral type
template< typename T >
struct is_integral
  : match<
        T
      , ignore_cv< ignore_sign< any_of< bool, char, char16_t, char32_t, wchar_t, short, int, long, long long > > >
    >
{};

// checks if a type is floating-point type
template< typename T >
struct is_floating_point
  : match<
        T
      , ignore_cv< any_of< float, double, long double > >
    >
{};

// checks if a type is an array type
template< typename T >
struct is_array
  : match<
        T
      , any_of< _[], _[N] >
    >
{};

// checks if a type is a function type
template< typename T >
struct is_function
  : match<
        T
      , _( varargs )
    >
{};

// checks if a type is a pointer type
template< typename T >
struct is_pointer
  : match<
        T
      , ignore_cv< _* >
    >
{};

// checks if a type is lvalue reference
template< typename T >
struct is_lvalue_reference
  : match<
        T
      , _&
    >
{};

// checks if a type is rvalue reference
template< typename T >
struct is_rvalue_reference
  : match<
        T
      , _&&
    >
{};

// checks if a type is a pointer to a non-static member object
template< typename T >
struct is_member_object_pointer
  : match<
        T
      , not_< ignore_cv< _( varargs ) > > _::*
    >
{};

// checks if a type is a pointer to a non-static member function
template< typename T >
struct is_member_function_pointer
  : match<
        T
      , ignore_cv< _( varargs ) > _::*
    >
{};

/** 20.9.4.2, composite type categories **/

// checks if a type is either lvalue reference or rvalue reference
template< typename T >
struct is_reference
  : match<
        T
      , any_of< _&, _&& >
    >
{};

// checks if a type is a pointer to a non-static member function or object
template< typename T >
struct is_member_pointer
  : match<
        T
      , _ _::*
    >
{};

/** 20.9.4.3, type properties **/

// checks if a type is const-qualified
template< typename T >
struct is_const
  : match<
        T
      , _ const
    >
{};

// checks if a type is volatile-qualified
template< typename T >
struct is_volatile
  : match<
        T
      , _ volatile
    >
{};

/** 20.9.6, type relations **/

// checks if two types are the same
template< typename T, typename U >
struct is_same
  : match<
        T
      , U
    >
{};
