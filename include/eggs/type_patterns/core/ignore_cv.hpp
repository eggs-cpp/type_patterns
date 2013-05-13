/**
 * Eggs.TypePatterns <eggs/type_patterns/core/ignore_cv.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_CORE_IGNORE_CV_HPP
#define EGGS_TYPE_PATTERNS_CORE_IGNORE_CV_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/match_fwd.hpp>
#include <eggs/type_patterns/metafunction.hpp>

namespace eggs { namespace type_patterns {
    
    template< typename Pattern >
    struct ignore_const;
    
    template< typename P, typename T, typename S >
    struct call<
        ignore_const< P >, match_context< T, S >
    > : detail::match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct call<
        ignore_const< P >, match_context< T const, S >
    > : detail::match< P, T, S >
    {};
    
    template< typename Pattern >
    struct ignore_volatile;
    
    template< typename P, typename T, typename S >
    struct call<
        ignore_volatile< P >, match_context< T, S >
    > : detail::match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct call<
        ignore_volatile< P >, match_context< T volatile, S >
    > : detail::match< P, T, S >
    {};
    
    template< typename Pattern >
    struct ignore_cv;
    
    template< typename P, typename T, typename S >
    struct call<
        ignore_cv< P >, match_context< T, S >
    > : detail::match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct call<
        ignore_cv< P >, match_context< T const, S >
    > : detail::match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct call<
        ignore_cv< P >, match_context< T volatile, S >
    > : detail::match< P, T, S >
    {};
    template< typename P, typename T, typename S >
    struct call<
        ignore_cv< P >, match_context< T const volatile, S >
    > : detail::match< P, T, S >
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_CORE_IGNORE_CV_HPP*/
