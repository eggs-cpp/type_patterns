/**
 * Eggs.TypePatterns <eggs/type_patterns/match.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_MATCH_HPP
#define EGGS_TYPE_PATTERNS_MATCH_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/placeholders.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_key.hpp>

#include <boost/utility/enable_if.hpp>

namespace eggs { namespace type_patterns {

    template< typename Type, typename Pattern >
    struct match
      : detail::match< Pattern, Type, boost::mpl::map<> >
    {
        typedef Type source_type;
        typedef Pattern pattern_type;
    };

    template< typename Match, typename Placeholder, typename Enable = void >
    struct at;
    
    template< typename Match >
    struct at<
        Match, _
    >
    {
        typedef typename Match::type matched;
        typedef typename Match::source_type type;
    };
    template< typename Match, int Placeholder >
    struct at<
        Match, placeholder< Placeholder >
      , typename boost::enable_if_c<
            Placeholder != 0
         && !boost::mpl::has_key<
                    typename Match::state
                  , placeholder< Placeholder >
                >::type::value
        >::type
    >
    {
        typedef boost::mpl::false_ matched;
        typedef struct invalid {} type;
    };
    template< typename Match, int Placeholder >
    struct at<
        Match, placeholder< Placeholder >
      , typename boost::enable_if_c<
            Placeholder != 0
         && boost::mpl::has_key<
                    typename Match::state
                  , placeholder< Placeholder >
                >::type::value
        >::type
    >
    {
        typedef boost::mpl::true_ matched;
        typedef typename boost::mpl::at<
                typename Match::state
              , placeholder< Placeholder >
            >::type type;
    };

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_MATCH_HPP*/
