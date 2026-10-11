//
// Created by wanglong on 2026/10/11.
//

#include "log.h"

#include <iostream>
std::string sylar::LogFormatter::format(LogEvent::ptr event) {

}
void sylar::LogFormatter::init() {
  
}
void sylar::StdOutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
  if (level >= m_level) {
    std::cout << m_formatter->format(event);
  }

}
sylar::FileLogAppender::FileLogAppender(const std::string& filename) {

}
void sylar::FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
if (level >= m_level) {
  m_filestream << m_formatter->format(event);
}
}
bool sylar::FileLogAppender::reopen() {
  if (m_filestream) {
    m_filestream.close();
  }
  m_filestream.open(m_filename);
  return !m_filestream;
}
void sylar::Logger::log(LogLevel::Level level, LogEvent::ptr event) {
  if (level >= m_level) {
    for (auto &it : m_appenders) {
      it->log(level,event);
    }
  }

}
void sylar::Logger::debug(LogEvent::ptr event) {
  log(LogLevel::DEBUG,event);
}
void sylar::Logger::info(LogEvent::ptr event) {
  log(LogLevel::INFO,event);
}
void sylar::Logger::warn(LogEvent::ptr event) {

  log(LogLevel::WARN,event);
}
void sylar::Logger::error(LogEvent::ptr event) {

  log(LogLevel::ERROR,event);
}
void sylar::Logger::fatal(LogEvent::ptr event) {
  log(LogLevel::FATAL,event);
}
void sylar::Logger::addAppender(LogAppender::ptr appender) {
  m_appenders.push_back(appender);
}
void sylar::Logger::delAppender(LogAppender::ptr appender) {
  for (auto it = m_appenders.begin(); it != m_appenders.end(); it++) {
    if (*it == appender) {
      m_appenders.erase(it);
      break;
    }
  }
}