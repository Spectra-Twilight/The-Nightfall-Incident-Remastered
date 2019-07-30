#ifndef LOG_HPP
#define LOG_HPP

#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

#define LOG(level) \
if (level <= Log::getReportingLevel() && Log::isOpen()) \
    Log().write(level)

class Log
{
    public:
    enum Level
    {
        ERROR,
        INFO,
        DEBUG
    };

    private:
    static std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> startTime;
    static Level reportLevel;
    static std::ofstream logFile;
    std::stringstream msgBuffer;

    static std::string reportToString(Level reportingLevel);
    static std::string getElapsedTime();

    public:
    ~Log();
    static void closeLog();
    static bool openLog(const std::string& logDir, Level reportingLevel);
    std::stringstream& write(Level msgLevel);

    inline static bool isOpen() { return logFile.is_open(); }
    inline static Level getReportingLevel() { return reportLevel; }
};

#endif // LOG_HPP