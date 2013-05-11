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

#include <eggs/type_patterns/metafunction.hpp>
#include <eggs/type_patterns/placeholders.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/utility/enable_if.hpp>

namespace eggs { namespace type_patterns { namespace detail {

    template< typename ...T > struct linear;

    template< typename Pattern, typename Type, typename State >
    struct match;

    // templates
    template< typename P, typename T, typename S, typename E = void >
    struct match_template
      : match_false< S >
    {};
    template< template< typename... > class P, typename ...PA, typename T, typename S >
    struct match_template<
        P< PA... >, T, S
      , typename boost::enable_if<
            is_metafunction< P >
        >::type
    > : call< P< PA... >, T, S >
    {};
    template< template< typename... > class U, typename ...P, typename ...T, typename S >
    struct match_template<
        U< P... >, U< T... >, S
      , typename boost::disable_if<
            is_metafunction< U >
        >::type
    > : match< linear< P... >, linear< T... >, S >
    {};

    // functions
    template< typename P, typename T, typename S, typename E = void >
    struct match_function
      : match_template< P, T, S >
    {};
    template< typename PR, typename ...PA, typename TR, typename ...TA, typename S >
    struct match_function<
        PR( PA... ), TR( TA... ), S
    > : match< linear< PR, PA... >, linear< TR, TA... >, S >
    {};
    template< typename PR, typename ...PA, typename TR, typename ...TA, typename S >
    struct match_function<
        PR( PA..., ... ), TR( TA..., ... ), S
    > : match< linear< PR, PA... >, linear< TR, TA... >, S >
    {};

    // arrays
    template< typename P, typename T, typename S >
    struct match_array
      : match_function< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_array< P[], T[], S >
      : match< P, T, S >
    {};
    template< typename P, typename T, int Size, typename S >
    struct match_array< P[ Size ], T[ Size ], S >
      : match< P, T, S >
    {};
    template< typename P, typename T, int Size, typename S >
    struct match_array< P[ N ], T[ Size ], S >
      : match< P, T, S >
    {};

    // references
    template< typename P, typename T, typename S >
    struct match_reference
      : match_array< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_reference<
        P&, T&, S
    > : match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_reference<
        P&&, T&&, S
    > : match< P, T, S >
    {};

    // pointers
    template< typename P, typename T, typename S >
    struct match_pointer
      : match_reference< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_pointer<
        P*, T*, S
    > : match< P, T, S >
    {};
    template< typename P, typename PO, typename T, typename TO, typename S >
    struct match_pointer<
        P PO::*, T TO::*, S
    > : match< linear< P, PO >, linear< T, TO >, S >
    {};

    // cv-qualifiers
    template< typename P, typename T, typename S >
    struct match_cv
      : match_pointer< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_cv<
        P const, T const, S
    > : match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_cv<
        P volatile, T volatile, S
    > : match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct match_cv<
        P const volatile, T const volatile, S
    > : match< P, T, S >
    {};

    // placeholders
    template< typename P, typename T, typename S, typename E = void >
    struct match_placeholder
      : match_cv< P, T, S >
    {};
    template< typename T, typename S >
    struct match_placeholder<
        _, T, S
    > : match_true< S >
    {};
    template< int P, typename T, typename S >
    struct match_placeholder<
        placeholder< P >, T, S
      , typename boost::enable_if_c<
            P != 0 && !boost::mpl::has_key< S, placeholder< P > >::type::value
        >::type
    > : match_true<
            typename boost::mpl::insert<
                S
              , boost::mpl::pair< placeholder< P >, T >
            >::type
        >
    {};
    template< int P, typename T, typename S >
    struct match_placeholder<
        placeholder< P >, T, S
      , typename boost::enable_if_c<
            P != 0 && boost::mpl::has_key< S, placeholder< P > >::type::value
        >::type
    > : match_bool<
            boost::is_same<
                typename boost::mpl::at< S, placeholder< P > >::type
              , T
            >
          , S
        >
    {};

    // terminal
    template< typename P, typename T, typename S >
    struct match_terminal
      : match_placeholder< P, T, S >
    {};
    template< typename T, typename S >
    struct match_terminal<
        T, T, S
    > : match_true< S >
    {};

    // ...finally
    template< typename P, typename T, typename S >
    struct match
      : match_terminal< P, T, S >
    {};

    // linear match
    template< typename P, typename T, typename S >
    struct match<
        linear< P >, linear< T >, S
    > : match< P, T, S >
    {};
    template< typename ...T, typename S >
    struct match<
        linear< varargs >, linear< T... >, S
    > : match_true< S >
    {};
    template< typename P, typename ...PT, typename T, typename ...TT, typename S >
    struct match<
        linear< P, PT... >, linear< T, TT... >, S
    > : boost::mpl::if_<
            match< P, T, S >
          , match< linear< PT... >, linear< TT... >, typename match< P, T, S >::state >
          , match_false< S >
        >::type
    {};

} } } // namespace eggs::type_patterns::detail

#endif /*EGGS_TYPE_PATTERNS_DETAIL_MATCH_HPP*/
