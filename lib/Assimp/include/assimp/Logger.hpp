
/** @file Logger.hpp
 *  @brief Abstract base class 'Logger', base of the logging system. 
 */
#ifndef INCLUDED_AI_LOGGER_H
#define INCLUDED_AI_LOGGER_H

#include "types.h"
namespace Assimp	{
class LogStream;

// Maximum length of a log message. Longer messages are rejected.
#define MAX_LOG_MESSAGE_LENGTH 1024u

// ----------------------------------------------------------------------------------
/**	@brief CPP-API: Abstract interface for logger implementations.
 *  Assimp provides a default implementation and uses it for almost all 
 *  logging stuff ('DefaultLogger'). This class defines just basic logging
 *  behaviour and is not of interest for you. Instead, take a look at #DefaultLogger. */
class ASSIMP_API Logger 
	: public Intern::AllocateFromAssimpHeap	{
public:

	// ----------------------------------------------------------------------
	/**	@enum	LogSeverity
	 *	@brief	Log severity to describe the granularity of logging.
	 */
	enum LogSeverity
	{
		NORMAL,		//!< Normal granularity of logging
		VERBOSE		//!< Debug infos will be logged, too
	};

	// ----------------------------------------------------------------------
	/**	@enum	ErrorSeverity
	 *	@brief	Description for severity of a log message.
	 *
	 *  Every LogStream has a bitwise combination of these flags.
	 *  A LogStream doesn't receive any messages of a specific type
	 *  if it doesn't specify the corresponding ErrorSeverity flag.
	 */
	enum ErrorSeverity
	{
		Debugging	= 1,	//!< Debug log message
		Info		= 2, 	//!< Info log message
		Warn		= 4,	//!< Warn log message
		Err			= 8		//!< Error log message
	};

public:

	/** @brief	Virtual destructor */
	virtual ~Logger();

	// ----------------------------------------------------------------------
	/** @brief	Writes a debug message
	 *	 @param	message	Debug message*/
	void debug(const char* message);
	inline void debug(const std::string &message);

	// ----------------------------------------------------------------------
	/** @brief	Writes a info message
	 *	@param	message Info message*/
	void info(const char* message);
	inline void info(const std::string &message);

	// ----------------------------------------------------------------------
	/** @brief	Writes a warning message
	 *	@param	message Warn message*/
	void warn(const char* message);
	inline void warn(const std::string &message);

	// ----------------------------------------------------------------------
	/** @brief	Writes an error message
	 *	@param	message	Error message*/
	void error(const char* message);
	inline void error(const std::string &message);

	// ----------------------------------------------------------------------
	/** @brief	Set a new log severity.
	 *	@param	log_severity New severity for logging*/
	void setLogSeverity(LogSeverity log_severity);

	// ----------------------------------------------------------------------
	/** @brief Get the current log severity*/
	LogSeverity getLogSeverity() const;

	// ----------------------------------------------------------------------
	/** @brief	Attach a new log-stream
	 *
	 *  The logger takes ownership of the stream and is responsible
	 *  for its destruction (which is done using ::delete when the logger
	 *  itself is destroyed). Call detachStream to detach a stream and to
	 *  gain ownership of it again.
	 *	 @param	pStream	 Log-stream to attach
	 *  @param severity  Message filter, specified which types of log
	 *    messages are dispatched to the stream. Provide a bitwise
	 *    combination of the ErrorSeverity flags.
	 *  @return true if the stream has been attached, false otherwise.*/
	virtual bool attachStream(LogStream *pStream, 
		unsigned int severity = Debugging | Err | Warn | Info) = 0;

	// ----------------------------------------------------------------------
	/** @brief	Detach a still attached stream from the logger (or 
	 *          modify the filter flags bits)
	 *	 @param	pStream	Log-stream instance for detaching
	 *  @param severity Provide a bitwise combination of the ErrorSeverity
	 *    flags. This value is &~ed with the current flags of the stream,
	 *    if the result is 0 the stream is detached from the Logger and
	 *    the caller retakes the possession of the stream.
	 *  @return true if the stream has been detached, false otherwise.*/
	virtual bool detatchStream(LogStream *pStream, 
		unsigned int severity = Debugging | Err | Warn | Info) = 0;

protected:

	/** Default constructor */
	Logger();

	/** Construction with a given log severity */
	Logger(LogSeverity severity);

	// ----------------------------------------------------------------------
	/** @brief Called as a request to write a specific debug message
	 *	@param	message	Debug message. Never longer than
	 *    MAX_LOG_MESSAGE_LENGTH characters (excluding the '0').
	 *  @note  The message string is only valid until the scope of
	 *    the function is left.
	 */
	virtual void OnDebug(const char* message)= 0;

	// ----------------------------------------------------------------------
	/** @brief Called as a request to write a specific info message
	 *	@param	message	Info message. Never longer than
	 *    MAX_LOG_MESSAGE_LENGTH characters (ecxluding the '0').
	 *  @note  The message string is only valid until the scope of
	 *    the function is left.
	 */
	virtual void OnInfo(const char* message) = 0;

	// ----------------------------------------------------------------------
	/** @brief Called as a request to write a specific warn message
	 *	@param	message	Warn message. Never longer than
	 *    MAX_LOG_MESSAGE_LENGTH characters (exluding the '0').
	 *  @note  The message string is only valid until the scope of
	 *    the function is left.
	 */
	virtual void OnWarn(const char* essage) = 0;

	// ----------------------------------------------------------------------
	/** @brief Called as a request to write a specific error message
	 *	@param	message Error message. Never longer than
	 *    MAX_LOG_MESSAGE_LENGTH characters (exluding the '0').
	 *  @note  The message string is only valid until the scope of
	 *    the function is left.
	 */
	virtual void OnError(const char* message) = 0;

protected:

	//!	Logger severity
	LogSeverity m_Severity;
};

// ----------------------------------------------------------------------------------
//	Default constructor
inline Logger::Logger()	{
	setLogSeverity(NORMAL);
}

// ----------------------------------------------------------------------------------
//	Virtual destructor
inline  Logger::~Logger()
{
}

// ----------------------------------------------------------------------------------
// Construction with given logging severity
inline Logger::Logger(LogSeverity severity)	{
	setLogSeverity(severity);
}

// ----------------------------------------------------------------------------------
// Log severity setter
inline void Logger::setLogSeverity(LogSeverity log_severity){
	m_Severity = log_severity;
}

// ----------------------------------------------------------------------------------
// Log severity getter
inline Logger::LogSeverity Logger::getLogSeverity() const {
	return m_Severity;
}

// ----------------------------------------------------------------------------------
inline void Logger::debug(const std::string &message)
{
	return debug(message.c_str());
}

// ----------------------------------------------------------------------------------
inline void Logger::error(const std::string &message)
{
	return error(message.c_str());
}

// ----------------------------------------------------------------------------------
inline void Logger::warn(const std::string &message)
{
	return warn(message.c_str());
}

// ----------------------------------------------------------------------------------
inline void Logger::info(const std::string &message)
{
	return info(message.c_str());
}

// ----------------------------------------------------------------------------------

} // Namespace Assimp

#endif // !! INCLUDED_AI_LOGGER_H
