/**
 * Eggs.TypePatterns <eggs/type_patterns/placeholders.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_PLACEHOLDERS_HPP
#define EGGS_TYPE_PATTERNS_PLACEHOLDERS_HPP

#ifndef EGGS_TYPE_PATTERNS_MAX_ARITY
#   define EGGS_TYPE_PATTERNS_MAX_ARITY 10
#endif

#include <boost/preprocessor/repeat_from_to.hpp>

#include <climits>

namespace eggs { namespace type_patterns {

    template< int Index >
    struct placeholder {};

    namespace placeholders {
        
        typedef placeholder< 0 > _;

#       define EGGS_TYPE_PATTERNS_decl_placeholder( z, n, text )             \
        typedef placeholder< n > _##n;

        BOOST_PP_REPEAT_FROM_TO(
            1, EGGS_TYPE_PATTERNS_MAX_ARITY
          , EGGS_TYPE_PATTERNS_decl_placeholder, ~
        )

#       undef EGGS_TYPE_PATTERNS_decl_placeholder

        struct varargs {};

        static int const N = INT_MAX;

    } // namespace placeholders

    using namespace placeholders;

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_PLACEHOLDERS_HPP*/
