/**
 * Eggs.TypePatterns <eggs/type_patterns/metafunction.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_METAFUNCTION_HPP
#define EGGS_TYPE_PATTERNS_METAFUNCTION_HPP

#include <boost/mpl/bool.hpp>

namespace eggs { namespace type_patterns {
    
    template< template< typename ... > class T >
    struct is_metafunction
      : boost::mpl::false_
    {};

    template<
        typename Metafunction
      , typename Type, typename State
      , typename Enable = void
    >
    struct call;

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_METAFUNCTION_HPP*/
