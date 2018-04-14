/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Debug.hpp"

namespace con
{
ILogger::~ILogger()
{
	constexpr const char* LOG_FILE_PATH = "log.txt";

	if ( static bool firstSave = true; firstSave ) {
		firstSave = false;
		std::experimental::filesystem::remove( { LOG_FILE_PATH } );
	}

	// Flush every time the logger is destroyed and there is some content.
	// May be a bottleneck.
	if ( !logData.empty() ) {
		std::ofstream logFile( LOG_FILE_PATH, std::ios::app );
		std::move( logData.begin(), logData.end(), std::ostream_iterator<std::string>( logFile, "\n" ) );
		logData.clear();
	}
}

const char* con::ILogger::logPriorityToString( LogPriority priority ) const noexcept
{
	switch ( priority ) {
	case LogPriority::Info:	return "INFO";
	case LogPriority::Warning: return "WARN";
	case LogPriority::Error: return " ERR";
	}

	return "";
}
}
