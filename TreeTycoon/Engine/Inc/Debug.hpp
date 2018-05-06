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

enum class LogPriority
{
	Info, Warning, Error
};

class ILogger
{
protected:
	virtual std::string loggerName() const = 0;

	template <typename ...TArgs>
	void log( LogPriority priority, TArgs&& ...args )
	{
		auto message = ConvertTo<std::string>( "[", logPriorityToString( priority ), "] ", loggerName(), ": ", std::forward<TArgs>( args )... );
		LogFile::append( message );
		std::puts( message.c_str() );
	}

	template <typename ...TArgs>
	void debugLog( LogPriority priority, TArgs&& ...args )
	{
		if constexpr (IS_DEBUG)
			log( priority, std::forward<TArgs>( args )... );
	}

private:
	class LogFile
	{
	private:
		static constexpr const char* LOG_FILE_PATH = "log.txt";
		std::vector<std::string> content;

		~LogFile();

	public:
		static void append( const std::string& message );
	};

	const char* logPriorityToString( LogPriority priority ) const noexcept;
};
}