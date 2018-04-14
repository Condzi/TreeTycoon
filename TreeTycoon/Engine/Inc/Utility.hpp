/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "EnginePCH.hpp"

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
	if constexpr ( std::is_same_v<bool, TSrc> )
		return src ? "true" : "false";
	else {
		std::stringstream ss;
		ss << +src;
		return ss.str();
	}
}

// Argument is a copy because it has to work on a copy of the string to do the transform.
inline std::string ToLower( std::string str )
{
	std::transform( str.begin(), str.end(), str.begin(), []( auto c ) {
		return ConvertTo<char>( std::tolower( c ) );
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
		return ( priv::ConvertToString( src ) +=  ... += priv::ConvertToString( args ) );
	else if constexpr ( std::is_same_v<std::string, TSrc> )
		return priv::ConvertFromString<TTarget>( src );
	else
		return static_cast<TTarget>( src );
}
}