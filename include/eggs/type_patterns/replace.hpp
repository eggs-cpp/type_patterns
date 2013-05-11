/**
 * Eggs.TypePatterns <eggs/type_patterns/replace.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_REPLACE_HPP
#define EGGS_TYPE_PATTERNS_REPLACE_HPP

#include <eggs/type_patterns/detail/replace.hpp>

#include <eggs/type_patterns/placeholders.hpp>

#include <boost/mpl/void.hpp>

namespace eggs { namespace type_patterns {

    template< typename Match, typename Pattern >
    struct replace
      : detail::replace< Pattern, boost::mpl::void_, typename Match::state >
    {
        typedef Pattern pattern_type;
    };

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_REPLACE_HPP*/
