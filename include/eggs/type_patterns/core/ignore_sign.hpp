/**
 * Eggs.TypePatterns <eggs/type_patterns/core/ignore_sign.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2013
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: https://github.com/eggs-cpp/type_patterns
 */

#ifndef EGGS_TYPE_PATTERNS_CORE_IGNORE_SIGN_HPP
#define EGGS_TYPE_PATTERNS_CORE_IGNORE_SIGN_HPP

#include <eggs/type_patterns/detail/match.hpp>

#include <eggs/type_patterns/metafunction.hpp>

namespace eggs { namespace type_patterns {
    
    template< typename Pattern >
    struct ignore_signed;
    
    template< typename P, typename T, typename S >
    struct call<
        ignore_signed< P >, T, S
    > : detail::match< P, T, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_signed< P >, signed char, S
    > : detail::match< P, char, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_signed< P >, signed short, S
    > : detail::match< P, short, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_signed< P >, signed int, S
    > : detail::match< P, int, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_signed< P >, signed long, S
    > : detail::match< P, long, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_signed< P >, signed long long, S
    > : detail::match< P, long long, S >
    {};

    template<>
    struct is_metafunction< ignore_signed >
      : boost::mpl::true_
    {};
    
    template< typename Pattern >
    struct ignore_unsigned;
    
    template< typename P, typename T, typename S >
    struct call<
        ignore_unsigned< P >, T, S
    > : detail::match< P, T, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_unsigned< P >, unsigned char, S
    > : detail::match< P, char, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_unsigned< P >, unsigned short, S
    > : detail::match< P, short, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_unsigned< P >, unsigned int, S
    > : detail::match< P, int, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_unsigned< P >, unsigned long, S
    > : detail::match< P, long, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_unsigned< P >, unsigned long long, S
    > : detail::match< P, long long, S >
    {};

    template<>
    struct is_metafunction< ignore_unsigned >
      : boost::mpl::true_
    {};
    
    template< typename Pattern >
    struct ignore_sign;
    
    template< typename P, typename T, typename S >
    struct call<
        ignore_sign< P >, T, S
    > : detail::match< P, T, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, signed char, S
    > : detail::match< P, char, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, signed short, S
    > : detail::match< P, short, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, signed int, S
    > : detail::match< P, int, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, signed long, S
    > : detail::match< P, long, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, signed long long, S
    > : detail::match< P, long long, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, unsigned char, S
    > : detail::match< P, char, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, unsigned short, S
    > : detail::match< P, short, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, unsigned int, S
    > : detail::match< P, int, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, unsigned long, S
    > : detail::match< P, long, S >
    {};
    template< typename P, typename S >
    struct call<
        ignore_sign< P >, unsigned long long, S
    > : detail::match< P, long long, S >
    {};

    template<>
    struct is_metafunction< ignore_sign >
      : boost::mpl::true_
    {};

} } // namespace eggs::type_patterns

#endif /*EGGS_TYPE_PATTERNS_CORE_IGNORE_SIGN_HPP*/
