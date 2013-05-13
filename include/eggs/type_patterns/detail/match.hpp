/**
 * Eggs.TypePatterns <eggs/type_patterns/detail/match.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_DETAIL_MATCH_HPP
#define EGGS_TYPE_PATTERNS_DETAIL_MATCH_HPP

#include <eggs/type_patterns/detail/match_bool.hpp>

#include <eggs/type_patterns/match_fwd.hpp>
#include <eggs/type_patterns/metafunction.hpp>
#include <eggs/type_patterns/placeholders.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>

#include <boost/type_traits/is_same.hpp>

namespace eggs { namespace type_patterns { namespace detail {

    template< typename Pattern, typename Type, typename State >
    struct match;

    template< typename ...T > struct linear;
    
    // terminal
    template< typename P, typename T, typename S >
    struct match
      : boost::mpl::if_<
            is_metafunction< P, match_context< T, S > >
          , call< P, match_context< T, S > >
          , match_bool<
                boost::is_same< P, T >
              , S
            >
        >::type
    {};

    // placeholders
    template< typename T, typename S >
    struct match<
        _, T, S
    > : match_true< S >
    {};    
    template< int P, typename T, typename S >
    struct match<
        placeholder< P >, T, S
    > : boost::mpl::if_<
            boost::mpl::has_key< S, placeholder< P > >
          , match_bool<
                boost::is_same<
                    typename boost::mpl::at< S, placeholder< P > >::type
                  , T
                >
              , S
            >
          , match_true<
                typename boost::mpl::insert<
                    S
                  , boost::mpl::pair< placeholder< P >, T >
                >::type
            >
        >::type
    {};

    // cv-qualifiers
    template< typename P, typename T, typename S >
    struct match<
        P const, T const, S
    > : match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match<
        P volatile, T volatile, S
    > : match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match<
        P const volatile, T const volatile, S
    > : match< P, T, S >
    {};

    // pointers
    template< typename P, typename T, typename S >
    struct match<
        P*, T*, S
    > : match< P, T, S >
    {};
    template< typename P, typename PO, typename T, typename TO, typename S >
    struct match<
        P PO::*, T TO::*, S
    > : match< linear< P, PO >, linear< T, TO >, S >
    {};

    // references
    template< typename P, typename T, typename S >
    struct match<
        P&, T&, S
    > : match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match<
        P&&, T&&, S
    > : match< P, T, S >
    {};

    // arrays
    template< typename P, typename T, typename S >
    struct match<
        P[], T[], S
    > : match< P, T, S >
    {};
    template< typename P, typename T, int Size, typename S >
    struct match<
        P[ Size ], T[ Size ], S
    > : match< P, T, S >
    {};
    template< typename P, typename T, int Size, typename S >
    struct match<
        P[ N ], T[ Size ], S
    > : match< P, T, S >
    {};

    // functions
    template< typename PR, typename ...PA, typename TR, typename ...TA, typename S >
    struct match<
        PR( PA... ), TR( TA... ), S
    > : match< linear< PR, PA... >, linear< TR, TA... >, S >
    {};
    template< typename PR, typename ...PA, typename TR, typename ...TA, typename S >
    struct match<
        PR( PA... ), TR( TA..., ... ), S
    > : match< linear< PR, PA... >, linear< TR, TA..., ellipsis >, S >
    {};
    template< typename PR, typename ...PA, typename TR, typename ...TA, typename S >
    struct match<
        PR( PA..., ... ), TR( TA..., ... ), S
    > : match< linear< PR, PA..., ellipsis >, linear< TR, TA..., ellipsis >, S >
    {};

    // templates
    template< template< typename... > class U, typename ...P, typename ...T, typename S >
    struct match<
        U< P... >, U< T... >, S
    > : boost::mpl::if_<
            is_metafunction< U< P... >, match_context< T, S > >
          , call< U< P... >, match_context< T, S > >
          , match< linear< P... >, linear< T... >, S >
        >::type
    {};
    template< template< typename... > class U, typename ...P, typename T, typename S >
    struct match<
        U< P... >, T, S
    > : boost::mpl::if_<
            is_metafunction< U< P... >, match_context< T, S > >
          , call< U< P... >, match_context< T, S > >
          , match_false< S >
        >::type
    {};

    // linear match
    template< typename P, typename T, typename S >
    struct linear_match;

    template< typename P, typename T, typename S >
    struct linear_match<
        linear< P >, linear< T >, S
    > : match< P, T, S >
    {};
    template< typename T, typename S >
    struct linear_match<
        linear< varargs >, linear< T >, S
    > : match_true< S >
    {};
    template< typename P, typename ...PT, typename T, typename ...TT, typename S >
    struct linear_match<
        linear< P, PT... >, linear< T, TT... >, S
    > : boost::mpl::if_<
            match< P, T, S >
          , linear_match<
                linear< PT... >, linear< TT... >
              , typename match< P, T, S >::state
            >
          , match_false< S >
        >::type
    {};
    template< typename ...T, typename S >
    struct linear_match<
        linear< varargs >, linear< T... >, S
    > : match_true< S >
    {};
    //~ we need this specialization or MSVC gets confused
    template< typename ...P, typename ...T, typename S >
    struct match<
        linear< P... >, linear< T... >, S
    > : linear_match< linear< P... >, linear< T... >, S >
    {};

} } } // namespace eggs::type_patterns::detail

#endif /*EGGS_TYPE_PATTERNS_DETAIL_MATCH_HPP*/
