/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "EnginePCH.hpp"
#include "Debug.hpp"

#include <random>

#define RULE_OF_FIVE_NO_CTOR( classname )			\
classname( const classname& ) = default;			\
classname( classname&& ) = default;					\
classname& operator=( const classname& ) = default; \
classname& operator=( classname&& ) = default; 

#define RULE_OF_FIVE( classname )	\
classname() = default;				\
RULE_OF_FIVE_NO_CTOR( classname )

namespace con
{

// Forward declaration for priv functions.

template <typename TTarget, typename TSrc, typename ...TArgs>
inline TTarget ConvertTo( const TSrc& src, TArgs&& ...args );

namespace priv
{
template <typename TSrc>
inline std::string ConvertToString( const TSrc& src )
{
	if constexpr ( std::is_same_v<std::string, TSrc> )
		return src;
	else if constexpr ( std::is_same_v<bool, TSrc> )
		return src ? "true" : "false";
	else {
		std::stringstream ss;
		// it's typedef for signed / unsigned char, so it has to be converted to number
		if constexpr ( std::is_same_v<int8_t, TSrc> || std::is_same_v<uint8_t, TSrc> )
			ss << +src;
		else
			ss << src;
		return ss.str();
	}
}

// Argument is a copy because it has to work on a copy of the string to do the transform.
inline std::string ToLower( std::string str )
{
	std::transform( str.begin(), str.end(), str.begin(), []( auto c ) {
		return ConvertTo<decltype( c )>( std::tolower( c ) );
	} );
	return str;
}

template <typename TTarget>
inline TTarget ConvertFromString( const std::string& src )
{
	if constexpr ( std::is_same_v<int8_t, TTarget> )
		return ConvertTo<int8_t>( std::stoi( src ) );
	else if constexpr ( std::is_same_v<uint8_t, TTarget> )
		return ConvertTo<uint8_t>( std::stoull( src ) );
	else if constexpr ( std::is_same_v<int16_t, TTarget> )
		return ConvertTo<int16_t>( std::stoi( src ) );
	else if constexpr ( std::is_same_v<uint16_t, TTarget> )
		return ConvertTo<uint16_t>( std::stoull( src ) );
	else if constexpr ( std::is_same_v<int32_t, TTarget> )
		return std::stoi( src );
	else if constexpr ( std::is_same_v<uint32_t, TTarget> )
		return ConvertTo<uint32_t>( std::stoull( src ) );
	else if constexpr ( std::is_same_v<int64_t, TTarget> )
		return std::stoll( src );
	else if constexpr ( std::is_same_v<uint64_t, TTarget> )
		return std::stoull( src );
	else if constexpr ( std::is_same_v<float32_t, TTarget> )
		return std::stof( src );
	else if constexpr ( std::is_same_v<float64_t, TTarget> )
		return std::stod( src );
	else if constexpr ( std::is_same_v<bool, TTarget> )
		return !( src == "0" || ToLower( src ) == "false" );
	else
		static_assert( false, __FUNCTION__ ": invalid from string conversion parameter" );
}

}
template <typename TTarget, typename TSrc, typename ...TArgs>
inline TTarget ConvertTo( const TSrc& src, TArgs&& ...args )
{
	if constexpr ( std::is_same_v<std::string, TTarget> )
		return ( priv::ConvertToString( src ) += ... += priv::ConvertToString( args ) );
	else if constexpr ( std::is_same_v<std::string, TSrc> )
		return priv::ConvertFromString<TTarget>( src );
	else
		return static_cast<TTarget>( src );
}

namespace priv
{
inline static std::mt19937
rng( ConvertTo<uint32_t>( std::chrono::steady_clock::now().time_since_epoch().count() ) );
}

template <typename T, typename Y>
T Random( const T& min, const Y& max )
{
	static_assert( std::is_integral_v<T> || std::is_floating_point_v<T> );
	T maxCasted = ConvertTo<T>( max );

	if ( min > maxCasted )
		throw std::range_error( "min > max" );

	if constexpr ( std::is_integral_v<T> )
	{
		std::uniform_int_distribution<T> dist( min, maxCasted );
		return dist( priv::rng );
	} else if constexpr ( std::is_floating_point_v<T> )
	{
		std::uniform_real_distribution<T> dist( min, maxCasted );
		return dist( priv::rng );
	}
}

template <typename TIteratorA, typename TIteratorB, typename TLambda>
void iteratePararell( TIteratorA beginA, TIteratorA endA, TIteratorB beginB, TIteratorB endB, TLambda&& lambda )
{
	if ( std::distance( beginA, endA ) != std::distance( beginB, endB ) )
		throw std::range_error( "wrong ranges (first range size is not equal to the second range)" );

	while ( beginA != endA )
		lambda( *(beginA++), *(beginB++) );
}
}