/**
 * Eggs.TypePatterns <eggs/type_patterns/core/as.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_CORE_AS_HPP
#define EGGS_TYPE_PATTERNS_CORE_AS_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/metafunction.hpp>
#include <eggs/type_patterns/placeholders.hpp>

#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>

#include <boost/utility/enable_if.hpp>

namespace eggs { namespace type_patterns {
    
    template< typename Placeholder, typename Pattern >
    struct as;
    
    template< int I, typename P, typename T, typename S >
    struct call<
        as< placeholder< I >, P >, T, S
      , typename boost::enable_if<
            detail::match< P, T, S >
        >::type
    > : detail::match_true<
            typename boost::mpl::insert<
                S
              , boost::mpl::pair< placeholder< I >, T >
            >::type
        >
    {};
    template< int I, typename P, typename T, typename S >
    struct call<
        as< placeholder< I >, P >, T, S
      , typename boost::disable_if<
            detail::match< P, T, S >
        >::type
    > : detail::match_false< S >
    {};

    template<>
    struct is_metafunction< as >
      : boost::mpl::true_
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_CORE_AS_HPP*/
