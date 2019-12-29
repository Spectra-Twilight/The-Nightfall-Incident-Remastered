#ifndef LOG_HPP
#define LOG_HPP

#include <chrono>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>

// If NOLOG is true, then all log calls will resolve to false at compile time,
// thus allowing for logging to be completely optimized out if desired.
#ifndef NOLOG
	#define NOLOG false
#endif

////////////////////////////////////////////////////////////////////////////////
/// Convenience macros, to keep invoking the log from being too tedious/verbose.
////////////////////////////////////////////////////////////////////////////////
#define LOGE LOG(Log::Level::error)
#define LOGW LOG(Log::Level::warning)
#define LOGI LOG(Log::Level::info)
#define LOGD LOG(Log::Level::debug)

////////////////////////////////////////////////////////////////////////////////
/// Convenience macro which checks if the log should be written before calling get().
////////////////////////////////////////////////////////////////////////////////
#define LOG(level) \
if (!(NOLOG) && Log::is_open() && level <= Log::get_report_level()) \
	Log().get(level, __FILE__, __FUNCTION__, __LINE__)

////////////////////////////////////////////////////////////////////////////////
/// \brief A class that creates and manages logfiles.
////////////////////////////////////////////////////////////////////////////////
class Log
{
public:
	////////////////////////////////////////////////////////////////////////////
	/// \brief Type representative of the different reporting levels for log entries.
	///
	/// The levels are ordered from most urgent to least urgent. The Log 
	/// may be set to a single reporting level at a time, which will allow 
	/// for logging of log messages marked as its current reporting level, 
	/// as well as all more urgent levels. Levels that are less urgent 
	/// than the current reporting level are not written to the logfile.
	////////////////////////////////////////////////////////////////////////////
	enum Level: uint8_t
	{
		error,
		warning,
		info,
		debug
	};

	////////////////////////////////////////////////////////////////////////////
	/// \brief Destructs Log instance and saves its buffer to the logfile.
	////////////////////////////////////////////////////////////////////////////
	~Log();

	////////////////////////////////////////////////////////////////////////////
	/// \brief Closes the currently open logfile, if one exists.
	/// 
	/// If no logfile is open at the time of the call to this function, 
	/// then it does nothing.
	////////////////////////////////////////////////////////////////////////////
	static void close();

	////////////////////////////////////////////////////////////////////////////
	/// \brief Prepares a new line to insert into the logfile, then returns the line's buffer.
	///
	///	The line is timestamped with the time since progream execution began, 
	///	accurate to the millisecond, followed by the report level of the message, 
	///	then the file, function, and line from which the message is being 
	///	written. Then the function returns this buffered line so that the 
	///	message itself may be inserted.
	///
	///	This function is not intended to be called directly, and does not perform 
	///	validity checking on arguments. Use the provided logging macros instead, 
	///	which ensures validity.
	///
	///	Calling this function with invalid file or function arguments, or 
	///	when no logfile is open results in undefined behavior.
	///
	///	\param msglvl	Level of the message being written.
	///	\param file	Name of the file which called this function.
	///	\param function	Name of the function which called this function.
	///	\param line	Line at which this function was called.
	///
	///	\return The buffered line, ready for the custom log message.
	////////////////////////////////////////////////////////////////////////////
	std::stringstream& get(Level msglvl, const char* file, const char* function, uint32_t line);

	////////////////////////////////////////////////////////////////////////////
	///	\brief Returns the current maximum report level for the Log.
	///
	///	\return The Log's current maximum reporting level.
	////////////////////////////////////////////////////////////////////////////
	inline static Level get_report_level() { return report_level; }
	
	////////////////////////////////////////////////////////////////////////////
	/// \brief Checks if the Log currently has a logfile open.
	///
	///	\return True if a logfile is open, or false otherwise.
	////////////////////////////////////////////////////////////////////////////
	inline static bool is_open() { return logfile.is_open(); }

	////////////////////////////////////////////////////////////////////////////
	/// \brief Opens a new logfile without a timestamp.
	///
	///	The new log file is created at the specified directory with a name 
	///	matching the following format:
	///		filename.log
	///
	///	The lack of timestamp allows the file to be overwritten by subsequent 
	///	logfiles of the same name, to prevent an accumulation of unimportant 
	///	logs.
	///
	///	This function closes the currently opened log file, if one exists.
	///
	///	\param directory	Directory in which to create the new logfile in.
	///	\param filename	The logfile's filename.
	///	\param max_report_level	The maximum level for reports to be written into this logfile.
	///
	///	\return True if the logfile was successfully created and opened, or false otherwise.
	////////////////////////////////////////////////////////////////////////////
	static bool open_nts(const std::string& directory, const std::string& filename, Level max_report_level);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Opens a new logfile timestamped with the time at which the program began executing.
	///
	/// The new log file is created at the specified directory with a name 
	/// matching the following format:
	///     filename_YYYY-mm-dd_hh;mm;ss.log
	/// 
	/// The timestamp ensures that the file will not be overwritten by 
	/// subsequently generated logfiles of the same filename.
	///
	/// This function closes the currently opened log file, if one exists.
	///
	/// \param directory	Directory which to create in the new logfile in.
	///	\param filename	Base filename to write before the timestamp in the final filename.
	///	\param max_report_level	The maximum level for reports to be written into this logfile.
	///	
	///	\return True if the timestamped logfile is successfully created and opened, or false otherwise.
	////////////////////////////////////////////////////////////////////////////
	static bool open_ts(const std::string& directory, const std::string& filename, Level max_report_level);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Sets the reporting level to the value of new_report_level.
	///
	///	\param new_report_level The new maximum report level.
	////////////////////////////////////////////////////////////////////////////
	inline static void set_report_level(Level new_report_level) { report_level = new_report_level; }

private:
	////////////////////////////////////////////////////////////////////////////
	///	\brief Generates and formats a timestamp for the time since the program began executing.
	///
	///	The returned timestamp string is formatted as follows:
	///		[hours:minutes:seconds.milliseconds]
	///
	///	This timestamp is NOT Windows filename-compatible (due to use of colons).
	///
	///	\return The formatted elapsed time.
	////////////////////////////////////////////////////////////////////////////
	static std::string format_elapsed_time();

	////////////////////////////////////////////////////////////////////////////
	///	\brief Generates and formats a timestamp of the time when the program began executing.
	///	
	///	The returned timestamp string is formatted as follows:
	///		Year-Month-Date_Hour;Minute;Second
	///	
	///	This timestamp is Windows filename-compatible.
	///
	///	\return The formatted start time.
	////////////////////////////////////////////////////////////////////////////
	static std::string format_start_time();

	////////////////////////////////////////////////////////////////////////////
	///	\brief Converts the provided logging level value into a human-readable string.
	///
	///	\param level	The level in which to convert to a string.
	///
	/// \return A constant C-string matching the provided level.
	////////////////////////////////////////////////////////////////////////////
	static const char* levelstr(Level level);

	////////////////////////////////////////////////////////////////////////////
	///	\brief Opens a new logfile at the provided filepath.
	///	
	///	This function closes the currently open logfile, if one exists.
	///	
	///	\param filepath	The full filepath, directory and filename combined, to the new logfile.
	///	\param max_report_level	The maximum level of reports to write to the new logfile.
	///
	///	\return True if the logfile is successfully created and opened, or false otherwise.
	////////////////////////////////////////////////////////////////////////////
	static bool open(const std::string& filepath, Level max_report_level);

	////////////////////////////////////////////////////////////////////////////
	///	Member Data
	////////////////////////////////////////////////////////////////////////////
	static const std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> start_time; ///< The time in which the program began running.
	static Level report_level; ///< Minimum urgency log types to write to the logfile.
	static std::ofstream logfile; ///< Program-wide logfile.
	std::stringstream msgbuf; ///< Instance-specific message buffer that moves to the logfile upon completion.
};

#endif // LOG_HPP