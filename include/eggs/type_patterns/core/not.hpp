/**
 * Eggs.TypePatterns <eggs/type_patterns/core/not.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_CORE_NOT_HPP
#define EGGS_TYPE_PATTERNS_CORE_NOT_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/metafunction.hpp>

#include <boost/mpl/not.hpp>

namespace eggs { namespace type_patterns {
    
    template< typename Pattern >
    struct not_;

    template<>
    struct is_metafunction< not_ >
      : boost::mpl::true_
    {};

    template< typename P, typename T, typename S >
    struct call<
        not_< P >, T, S
    > : detail::match_bool<
            boost::mpl::not_< detail::match< P, T, S > >
          , S
        >
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_CORE_NOT_HPP*/
