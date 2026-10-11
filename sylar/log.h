#ifndef MYSYLAR_LOG_H
#define MYSYLAR_LOG_H
#include <stdint.h>

#include <fstream>
#include <list>
#include <memory>
#include <string>

namespace sylar {
// 日志事件
class LogEvent {
 public:
  typedef std::shared_ptr<LogEvent> ptr;
  LogEvent();

 private:
  const char *m_file = nullptr;
  int32_t m_line = 0;
  int32_t m_elapse = 0;  // 程序启动开始到现在的毫秒数
  uint32_t m_threadId = 0;
  uint32_t m_fiberId = 0;  // 携程id
  uint64_t m_time = 0;     // 时间戳
  std::string m_content;
};

// 日志级别
class LogLevel {
 public:
  enum Level { DEBUG = 1, INFO = 2, WARN = 3, ERROR = 4, FATAL = 5 };
};

// 日志格式器
class LogFormatter {
 public:
  typedef std::shared_ptr<LogFormatter> ptr;
  std::string format(LogEvent::ptr event);

 private:
};

class LogAppender {
 public:
  typedef std::shared_ptr<LogAppender> ptr;
  virtual ~LogAppender() {};
  virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;   // 纯虚类，子类必须实现父类的方法

  void setFormatter(LogFormatter::ptr val) { m_formatter = val;}
  LogFormatter::ptr getFormatter() const { return m_formatter;}

 private:
  LogLevel::Level m_level;
  LogFormatter::ptr m_formatter;
};

class StdOutLogAppender : public LogAppender {
 public:
  typedef std::shared_ptr<StdOutLogAppender> ptr;
  void log(LogLevel::Level level, LogEvent::ptr event) override;

 private:
};

class FileLogAppender : public LogAppender {
public:
  typedef std::shared_ptr<FileLogAppender> ptr;
  FileLogAppender(const std::string& filename);
  void log(LogLevel::Level level, LogEvent::ptr event) override;
  bool reopen(); // 重新打开
private:
  std::string m_filename;
  std::ofstream m_filestream;
};

// 日志器
class Logger {
 public:
  typedef std::shared_ptr<Logger> ptr;
  Logger(const std::string name = "root");
  void log(LogLevel::Level level, LogEvent::ptr event);

  void debug(LogEvent::ptr event);
  void info(LogEvent::ptr event);
  void warn(LogEvent::ptr event);
  void error(LogEvent::ptr event);
  void fatal(LogEvent::ptr event);

  void addAppender(LogAppender::ptr appender);
  void delAppender(LogAppender::ptr appender);

  void setLevel(LogLevel::Level level) { m_level = level; };
  LogLevel::Level getLevel() const { return m_level; };

 private:
  std::string m_name;
  LogLevel::Level m_level;
  std::pmr::list<LogAppender::ptr> m_appenders;
};

}  // namespace sylar
#endif  // MYSYLAR_LOG_H
