/**
 * Eggs.TypePatterns <main.cpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#include <eggs/type_patterns.hpp>

using namespace eggs::type_patterns;

template< typename T >
struct is_member_object_pointer
  : match< T, _1 _2::* >
{
    typedef typename at<
            is_member_object_pointer, _
        >::type type;
    typedef typename at<
            is_member_object_pointer, _1
        >::type object_type;
    typedef typename at<
            is_member_object_pointer, _2
        >::type class_type;
};

#include <iostream>
#include <typeinfo>

struct X
{
    int foo;
};

int main()
{
    typedef is_member_object_pointer< decltype(&X::foo) > traits;
    
    std::cout
     << "is_member_object_pointer: " << std::boolalpha << traits() << "\n"
     << "  class_type: " << typeid(traits::class_type).name() << "\n"
     << "  object_type: " << typeid(traits::object_type).name() << "\n"
     << std::endl;

    static_assert(
        match<
            double
          , any_of< float, double, long double >
        >::value, "metafunction failed" );
    
    return 0;
}
