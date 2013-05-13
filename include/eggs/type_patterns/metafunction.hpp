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

    template< typename Type, typename Context >
    struct call
    {
        typedef void unspecified_tag;
    };
    
    template<
        typename Type, typename Context
      , typename Enable = void
    >
    struct is_metafunction
      : boost::mpl::true_
    {};
    template<
        typename Type, typename Context
    >
    struct is_metafunction<
        Type, Context
      , typename call< Type, Context >::unspecified_tag
    > : boost::mpl::false_
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_METAFUNCTION_HPP*/
