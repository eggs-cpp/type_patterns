/**
 * Eggs.TypePatterns <eggs/type_patterns/algorithm/all_of.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_ALGORITHM_ALL_OF_HPP
#define EGGS_TYPE_PATTERNS_ALGORITHM_ALL_OF_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/metafunction.hpp>

#include <boost/mpl/if.hpp>

namespace eggs { namespace type_patterns {

    template< typename ...Patterns >
    struct all_of;

    template<>
    struct is_metafunction< all_of >
      : boost::mpl::true_
    {};

    template< typename T, typename S >
    struct call<
        all_of<>, T, S
    > : detail::match_true< S >
    {};
    template< typename P, typename ...PT, typename T, typename S >
    struct call<
        all_of< P, PT... >, T, S
    > : boost::mpl::if_<
            detail::match< P, T, S >
          , call< all_of< PT... >, T, S >
          , detail::match_false< S >
        >::type
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_ALGORITHM_ALL_OF_HPP*/
