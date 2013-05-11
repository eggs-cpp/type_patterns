/**
 * Eggs.TypePatterns <eggs/type_patterns/core/apply.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_CORE_APPLY_HPP
#define EGGS_TYPE_PATTERNS_CORE_APPLY_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/metafunction.hpp>
#include <eggs/type_patterns/placeholders.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>

namespace eggs { namespace type_patterns {

    template< typename Predicate >
    struct apply;

    template<>
    struct is_metafunction< apply >
      : boost::mpl::true_
    {};

    namespace detail {

        template< typename P, typename T, typename S >
        struct apply_eval
          : boost::mpl::identity< P >
        {};
        template< typename T, typename S >
        struct apply_eval<
            _, T, S
        > : boost::mpl::identity< T >
        {};
        template< int P, typename T, typename S >
        struct apply_eval<
            placeholder< P >, T, S
        > : boost::mpl::at< S, placeholder< P > >
        {};
        template< template< typename... > class F, typename ...FP, typename T, typename S >
        struct apply_eval<
            F< FP... >, T, S
        > : boost::mpl::identity<
                F< typename apply_eval< FP, T, S >::type... >
            >
        {};

    } // namespace detail

    template< template< typename... > class F, typename ...FP, typename T, typename S >
    struct call<
        apply< F< FP... > >, T, S
    > : detail::match_bool<
            typename detail::apply_eval< F< FP... >, T, S >::type
          , S
        >
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_CORE_APPLY_HPP*/
