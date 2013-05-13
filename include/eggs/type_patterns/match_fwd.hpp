/**
 * Eggs.TypePatterns <eggs/type_patterns/match_fwd.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_MATCH_FWD_HPP
#define EGGS_TYPE_PATTERNS_MATCH_FWD_HPP

namespace eggs { namespace type_patterns {

    template< typename Type, typename Pattern >
    struct match;

    template< typename Type, typename State >
    struct match_context;

    template< typename Match, typename Placeholder, typename Enable = void >
    struct at;

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_MATCH_FWD_HPP*/
