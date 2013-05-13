`Eggs.TypePatterns`
==============

# Introduction #

`Eggs.TypePatterns` is pattern matching for types. It uses a terse syntax 
to check for multiple type traits, and extract components of compound types.

The library is loosely based on [_Boost.Proto_][boost.proto] pattern matching 
for _proto expression grammars_. It makes extensive use of the _C++ Standard 
Library_ as well as the [_Boost C++ Libraries_][boost].

The library is in its early development stages, and currently provides no 
examples, tests nor documentation. Its use in a production environment is not 
recommended at the time.

[boost]: http://boost.org/ "Boost C++ Libraries"
[boost.proto]: http://www.boost.org/doc/libs/release/libs/proto/ "Boost.Proto"

# Motivation #

Given a type `T`, we need to check whether it is a _pointer-to-const `U`_ and 
if so we have to find the type `U`.

Using the _type traits_ components from the **C++11** standard library, we 
could do:

    using namespace std;

    bool matches =
      is_pointer< T >::value && 
      is_const< typename remove_pointer< T >::type >::value;

    typedef typename remove_const<
      typename remove_pointer< T >::type
    >::type U;

With the addition of _transformation traits redux_ to **C++14**, we can get 
ride of those `typename`s:

    using namespace std;

    bool matches =
      is_pointer< T >::value &&
      is_const< remove_pointer_t< T > >::value;

    typedef remove_const_t<
      remove_pointer_t< T >
    > U;

Using _TypePatterns_, we get a more expressive solution:

    using namespace eggs::type_patterns;

    bool matches = match< T, _1 const* >::value;

    typedef typename at< match< T, _1 const* >, _1 >::type U;

# Basic usage #

## Main components ##

Use the `match` template metafunction to match a type against a given 
_pattern_. Use _placeholders_ to build more complex _patterns_. _[ Example:_

    #include <eggs/type_patterns.hpp>
    using namespace eggs::type_patterns;

    template< typename T >
    struct is_member_pointer
      : match< T, _1 _2::* > //~> Pattern: _1 _2::*
    {
        typedef typename at<
                is_member_pointer, _
            >::type type; //~> type matched, T
        typedef typename at<
                is_member_pointer, _1
            >::type member_type; //~> type that matched _1
        typedef typename at<
                is_member_pointer, _2
            >::type class_type; //~> type that matched _2
    };

    struct X { int foo; };

    static_assert(
        is_member_pointer< decltype(&X::foo) >::value
      , "oops! &X::foo should be a member pointer" );
    static_assert(
        !is_member_pointer< decltype(X::foo) >::value
      , "oops! X::foo should be an int" );

_—end example ]_

### Placeholders ###

_Placeholders_ allow you to build more powerful _patterns_.

  - `_` is a wildcard placeholder, it matches any type.

  - `_1` .. `_9` are capture placeholders, they match any type the first 
time they are encountered. Afterwards, they only match the type that was 
initially matched.

  - `N` is a size placeholder, usable to match arrays of any size.

  - `varargs` is a variadic placeholder, it matches zero or more types, 
usable to match functions or templates with any number of trailing arguments.

### Metafunctions ###

_Metafunctions_ allow you to extend the matching functionality beyond 
the syntax of **C++** types.

  - `apply< Predicate >` matches a type when evaluating the _predicate_ for 
said type results in a true type. In this context, `_` resolves to the type 
being matched and `_1` .. `_9` resolve to already matched capture 
placeholders.

  - `as< Placeholder, Pattern >` performs a _pattern_ match against the 
type, and it captures it in the given capture _placeholder_ when it does match.

  - `not_< Pattern >` matches a type that does **not** match the given 
_pattern_.

  - `ignore_const< Pattern >`, `ignore_volatile< Pattern >`, `ignore_cv< Pattern >` 
perform a _pattern_ match that ignores `const` and/or `volatile` qualifiers.

  - `ignore_signed< Pattern >`, `ignore_unsigned< Pattern >`, `ignore_sign< Pattern >` 
perform a _pattern_ match that ignores `signed` and/or `unsigned` modifiers.

  - `all_of< ...Patterns >` matches a type that matches **all** of the 
_patterns_.

  - `any_of< ...Patterns >` matches a type that matches **any** of the 
_patterns_.

  - `none_of< ...Patterns >` matches a type that matches **none** of the 
_patterns_.

---

> Copyright _Agustín Bergé_, _Fusion Fenix_ 2013
> 
> Distributed under the Boost Software License, Version 1.0. (See accompanying
> file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
