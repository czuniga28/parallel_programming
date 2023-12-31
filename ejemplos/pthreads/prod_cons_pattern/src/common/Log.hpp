// Copyright 2021,2023 Jeisson Hidalgo-Cespedes. ECCI-UCR. CC BY 4.0

#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

#include "common.hpp"

/**
 * @brief Singleton thread-safe log manager
 *
 * In some programming contexts printing messages to error or standard output is
 * not always useful. For example, for servers running in background, there is
 * not a terminal connected to the process and a user monitoring its messages.
 *
 * In these cases, messages are sent to a log file. Users can study the logs
 * at any moment, to see what messages are being generated by the server. Logs
 * are very convenient for data analysis. Statistical or data mining software
 * can generate tables, graphs, or more sophisticated information from the logs.
 *
 * If these aggregated data is generated in real time from logs coming from
 * distributed sources located in a network of computers, it allow people to
 * monitor the behavior of a complex system. Usually this is the preferred way
 * to feedback people in distributed systems, where traditional debugging
 * methods are unfeasible.
 * 
 * This class implements a minimalist log manager that is able to write messages
 * coming from several execution threads. Messages are automatically serialized
 * by a mutex, avoiding corrupting the log file. The class implements the
 * singleton software pattern. In order to use it, just include the header file,
 * and append messages to the log:
 * 
 * @code {.cpp}
 * #include "Log.hpp"
 * 
 * int main() {
 *   Log::append(Log::INFO, "session", "Server started");
 *   Server myServer;
 *   myServer.run();
 *   Log::append(Log::INFO, "session", "Server finished");
 * }
 * @endcode
 *
 * The first argument of Log::append() is the type of message. Some constants
 * are provided. Log::INFO is used for providing normal information to the user
 * such as the progress of an operation. You can inform about problematic
 * situations that prevented the software to reach its goals at all (Log::ERROR)
 * or it continued but may have generated invalid results (Log::WARNING). You
 * can report messages to the development team instead of users using
 * Log::DEBUG.
 * 
 * The second argument of Log::append() is a category. This is usually a single
 * word that you use to classify messages. You may use identifiers for the big
 * modules of your system. For example, "gui", "database", "user". Think you
 * can use these words to filter messages later when you analyze the logs.
 * 
 * Finally the third argument of Log::append() is a text. Use the shortest text
 * that provides a meaningful description of what happened.
 * 
 * Do not use tabulator characters inside any of the arguments of Log::append().
 * Internally messages are stored in TSV (tab-separated values) format. By
 * default messages are sent to standard output. If you want to preserve them
 * to a file (recommended) start the Log manager providing a filename. Remember
 * to call stop() method to close you log file. For example:
 * 
 * @code {.cpp}
 * #include "Log.hpp"
 * 
 * int main() {
 *   Log::getInstance().start("myserver.tsv");
 *   Log::append(Log::INFO, "session", "Server started");
 *   Server myServer;
 *   myServer.run();
 *   Log::append(Log::INFO, "session", "Server finished");
 *   Log::getInstance().stop();
 * }
 * @endcode
*/
class Log {
  DISABLE_COPY(Log);

 public:
  /// The types of records/messages to be written to the log
  enum MessageType {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
  };
  /// The respective texts for the message types
  static const char* const MESSAGE_TYPE_TEXT[];

 private:
  /// All write operations are mutually exclusive.
  std::mutex mutex;
  /// The output stream where all output will be sent.
  /// This can point to file or std::cout.
  std::ostream output;
  /// The log filename. If empty, std::cout will be used.
  std::string filename;
  /// The log file if using named files.
  std::ofstream file;

 public:
  /// Get access to the unique instance of this Singleton class.
  static Log& getInstance();
  /// Open the log file for appending.
  /// @param logFilename If no filename is given, standard output is used.
  /// @throw std::runtime_error if file could not be open.
  void start(const std::string& logFilename = std::string());
  /// Closes the log file.
  void stop();
  /// Appends a record to the log file.
  /// @throw std::runtime_error if record could not be written.
  /// @see append
  void write(MessageType type, const std::string& category
    , const std::string& text);
  /// Appends a record to the log file.
  /// This is a convenience static method that calls write.
  /// @param type A constant: DEBUG, INFO, WARNING, ERROR.
  /// @param category Any text that is useful for distinguishing messages, such
  /// as the name of the module or class, e.g: producer or socket
  /// @param text Text should not contain tab characters ('\\t')
  /// @throw std::runtime_error if record could not be written
  static inline void append(MessageType type, const std::string& category
      , const std::string& text) {
    return Log::getInstance().write(type, category, text);
  }

 private:
  /// Singleton. Implement code in start() method instead.
  Log();
  /// Singleton. Implement code in stop() method instead.
  ~Log() = default;
};

#endif  // LOG_HPP
