/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Debug.hpp"

namespace con
{
const char* con::ILogger::logPriorityToString( LogPriority priority ) const noexcept
{
	switch ( priority ) {
	case LogPriority::Info:	return "INFO";
	case LogPriority::Warning: return "WARN";
	case LogPriority::Error: return " ERR";
	}

	return "";
}

ILogger::LogFile::~LogFile()
{
	std::experimental::filesystem::remove( { LOG_FILE_PATH } );
	
	std::ofstream logFile( LOG_FILE_PATH );
	std::move( content.begin(), content.end(), std::ostream_iterator<std::string>( logFile, "\n" ) );
	content.clear();
}

void ILogger::LogFile::append( const std::string& message )
{
	static LogFile file;
	file.content.emplace_back( message );
}
}
