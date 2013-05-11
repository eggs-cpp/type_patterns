/**
 * Eggs.TypePatterns <eggs/type_patterns/detail/replace_type.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_DETAIL_REPLACE_TYPE_HPP
#define EGGS_TYPE_PATTERNS_DETAIL_REPLACE_TYPE_HPP

#include <boost/mpl/identity.hpp>

namespace eggs { namespace type_patterns { namespace detail {
    
    template< typename Type, typename State >
    struct replace_type
      : boost::mpl::identity< Type >
    {
        typedef State state;
    };

} } } // namespace eggs::type_patterns::detail

#endif /*EGGS_TYPE_PATTERNS_DETAIL_REPLACE_TYPE_HPP*/
