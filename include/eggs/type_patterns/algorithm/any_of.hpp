/**
 * Eggs.TypePatterns <eggs/type_patterns/algorithm/any_of.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_ALGORITHM_ANY_OF_HPP
#define EGGS_TYPE_PATTERNS_ALGORITHM_ANY_OF_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/metafunction.hpp>

#include <boost/utility/enable_if.hpp>

namespace eggs { namespace type_patterns {
    
    template< typename ...Patterns >
    struct any_of;
    
    template< typename T, typename S >
    struct call<
        any_of<>, T, S
    > : detail::match_false< S >
    {};
    template< typename P, typename ...PT, typename T, typename S >
    struct call<
        any_of< P, PT... >, T, S
      , typename boost::enable_if<
            detail::match< P, T, S >
        >::type
    > : detail::match< P, T, S >
    {};
    template< typename P, typename ...PT, typename T, typename S >
    struct call<
        any_of< P, PT... >, T, S
      , typename boost::disable_if<
            detail::match< P, T, S >
        >::type
    > : call< any_of< PT... >, T, S >
    {};

    template<>
    struct is_metafunction< any_of >
      : boost::mpl::true_
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_ALGORITHM_ANY_OF_HPP*/
