/**
 * Eggs.TypePatterns <eggs/type_patterns/detail/replace.hpp>
 * 
 * Copyright Agust�n Berg�, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_DETAIL_REPLACE_HPP
#define EGGS_TYPE_PATTERNS_DETAIL_REPLACE_HPP

#include <eggs/type_patterns/detail/replace_type.hpp>

#include <eggs/type_patterns/metafunction.hpp>
#include <eggs/type_patterns/placeholders.hpp>
#include <eggs/type_patterns/replace_fwd.hpp>

#include <boost/mpl/at.hpp>

namespace eggs { namespace type_patterns { namespace detail {

    template< typename Pattern, typename Type, typename State >
    struct replace;
    
    // terminal
    template< typename P, typename T, typename S >
    struct replace
      : boost::mpl::if_<
            is_metafunction< P, replace_context< T, S > >
          , call< P, replace_context< T, S > >
          , replace_type< P, S >
        >::type
    {};

    // placeholders
    template< int P, typename T, typename S >
    struct replace<
        placeholder< P >, T, S
    > : replace_type<
            typename boost::mpl::at< S, placeholder< P > >::type
          , S
        >
    {};

    // cv-qualifiers
    template< typename P, typename T, typename S >
    struct replace<
        P const, T, S
    > : replace_type<
            typename replace< P, T, S >::type const
          , S
        >
    {};
    template< typename P, typename T, typename S >
    struct replace<
        P volatile, T volatile, S
    > : replace_type<
            typename replace< P, T, S >::type volatile
          , S
        >
    {};
    template< typename P, typename T, typename S >
    struct replace<
        P const volatile, T const volatile, S
    > : replace_type<
            typename replace< P, T, S >::type const volatile
          , S
        >
    {};

    // pointers
    template< typename P, typename T, typename S >
    struct replace<
        P*, T, S
    > : replace_type<
            typename replace< P, T, S >::type*
          , S
        >
    {};
    template< typename P, typename PO, typename T, typename S >
    struct replace<
        P PO::*, T, S
    > : replace_type<
            typename replace< P, T, S >::type
            typename replace< PO, T, S >::type::*
          , S
        >
    {};

    // references
    template< typename P, typename T, typename S >
    struct replace<
        P&, T, S
    > : replace_type<
            typename replace< P, T, S >::type&
          , S
        >
    {};
    template< typename P, typename T, typename S >
    struct replace<
        P&&, T, S
    > : replace_type<
            typename replace< P, T, S >::type&&
          , S
        >
    {};

    // arrays
    template< typename P, typename T, typename S >
    struct replace<
        P[], T, S
    > : replace_type<
            typename replace< P, T, S >::type[]
          , S
        >
    {};
    template< typename P, typename T, int Size, typename S >
    struct replace<
        P[ Size ], T, S
    > : replace_type<
            typename replace< P, T, S >::type[ Size ]
          , S
        >
    {};

    // functions
    template< typename PR, typename ...PA, typename T, typename S >
    struct replace<
        PR( PA... ), T, S
    > : replace_type<
            typename replace< PR, T, S >::type(
                typename replace< PA, T, S >::type...
            )
          , S
        >
    {};
    template< typename PR, typename ...PA, typename T, typename S >
    struct replace<
        PR( PA..., ... ), T, S
    > : replace_type<
            typename replace< PR, T, S >::type(
                typename replace< PA, T, S >::type...
              , ...
            )
          , S
        >
    {};
    template< typename PR, typename ...PA, typename T, typename S >
    struct replace<
        PR( PA..., ellipsis ), T, S
    > : replace_type<
            typename replace< PR, T, S >::type(
                typename replace< PA, T, S >::type...
              , ...
            )
          , S
        >
    {};
    
    // templates
    template< template< typename... > class U, typename ...P, typename T, typename S >
    struct replace<
        U< P... >, T, S
    > : boost::mpl::if_<
            is_metafunction< U< P... >, replace_context< T, S > >
          , call< U< P... >, replace_context< T, S > >
          , replace_type< U< typename replace< P, T, S >::type... >, S >
        >::type
    {};

} } } // namespace eggs::type_patterns::detail

#endif /*EGGS_TYPE_PATTERNS_DETAIL_REPLACE_HPP*/
