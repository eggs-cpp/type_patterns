/**
 * Eggs.TypePatterns <eggs/type_patterns/detail/match_bool.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_DETAIL_MATCH_BOOL_HPP
#define EGGS_TYPE_PATTERNS_DETAIL_MATCH_BOOL_HPP

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

    template< typename State >
    struct match_false
      : boost::mpl::false_
    {
        typedef boost::mpl::map<> state;
    };
    template< typename State >
    struct match_true
      : boost::mpl::true_
    {
        typedef State state;
    };
    template< typename Bool, typename State >
    struct match_bool
      : boost::mpl::if_<
            Bool
          , match_true< State >
          , match_false< State >
        >::type
    {};

} } } // namespace eggs::type_patterns::detail

#endif /*EGGS_TYPE_PATTERNS_DETAIL_MATCH_BOOL_HPP*/
