/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include <Debug.hpp>

using namespace con;

int main()
{
	class Logger : public ILogger
	{
	private:
		const char* loggerName() const noexcept
		{
			return "Logger";
		}
	public:
		void test()
		{
			log( LogPriority::Info, "info." );
			log( LogPriority::Warning, "warning." );
			log( LogPriority::Error, "error." );
			debugLog( LogPriority::Info, "debug info." );
			debugLog( LogPriority::Warning, "debug warning." );
			debugLog( LogPriority::Error, "debug error." );
		}
	};

	Logger l;
	l.test();

	std::cin.get();
}