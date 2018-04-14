/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "EnginePCH.hpp"
#include "Utility.hpp"

namespace con
{
#if _DEBUG
constexpr bool IS_DEBUG = true;
#else
constexpr bool IS_DEBUG = false;
#endif

// Priority is also console text color.
enum class LogPriority 
{
	Info, Warning, Error
};

class ILogger
{
public:
	RULE_OF_FIVE( ILogger );
	~ILogger();

protected:
	virtual const char* loggerName() const = 0;

	template <typename ...TArgs>
	void log( LogPriority priority, TArgs&& ...args )
	{
		auto message = ConvertTo<std::string>( "[", logPriorityToString( priority ), "]: ", std::forward<TArgs>( args )... );
		logData.emplace_back( message );
		std::cout << message << '\n';
	}

	template <typename ...TArgs>
	void debugLog( LogPriority priority, TArgs&& ...args )
	{
		if constexpr ( IS_DEBUG )
			log( priority, std::forward<TArgs>( args )... );
	}

private:
	inline static std::vector<std::string> logData{};

	const char* logPriorityToString( LogPriority priority ) const noexcept;
};
}