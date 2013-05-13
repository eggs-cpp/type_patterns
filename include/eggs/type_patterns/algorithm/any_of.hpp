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

#include <eggs/type_patterns/match_fwd.hpp>
#include <eggs/type_patterns/metafunction.hpp>

#include <boost/mpl/if.hpp>

namespace eggs { namespace type_patterns {
    
    template< typename ...Patterns >
    struct any_of;
    
    template< typename T, typename S >
    struct call<
        any_of<>, match_context< T, S >
    > : detail::match_false< S >
    {};
    template< typename P, typename ...PT, typename T, typename S >
    struct call<
        any_of< P, PT... >, match_context< T, S >
    > : boost::mpl::if_<
            detail::match< P, T, S >
          , detail::match< P, T, S >
          , call< any_of< PT... >, match_context< T, S > >
        >::type
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_ALGORITHM_ANY_OF_HPP*/
