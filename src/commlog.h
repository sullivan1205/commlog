#ifndef _COMMONLOG_COMMMONLOG_H_
#define _COMMONLOG_COMMMONLOG_H_

#include <iostream>
#include <stdint.h>
#include <memory>

namespace cmlg {

enum SEVERITY {
    SEVERITY_TRACE = 0,
    SEVERITY_DEBUG,
    SEVERITY_INFO,
    SEVERITY_WARNING,
    SEVERITY_ERROR,
    SEVERITY_FATAL,
    SEVERITY_OFF
};

class Logger {
public:
  struct Location {
    Location(const char* file, int line)
      : file_(file), line_(line) {}
    const char* file_ = nullptr;
    int line_ = 0;
  };
  Logger(SEVERITY severity): severity_(severity) {}
  virtual ~Logger() {}
  virtual SEVERITY GetSeverity() { return severity_; }
  virtual void SetSeveriy(SEVERITY severity) { severity_ =  severity; }
  virtual void Trace(Location& loc, const char* message) = 0;
  virtual void Debug(Location& loc, const char* message) = 0;
  virtual void Info(Location& loc, const char* message) = 0;
  virtual void Warning(Location& loc, const char* message) = 0;
  virtual void Error(Location& loc, const char* message) = 0;
  virtual void Fatal(Location& loc, const char* message) = 0;
  virtual void Off(Location& loc, const char* message) = 0;
private:
  SEVERITY severity_;
};

class LogMessageVoidify {
  public:
    LogMessageVoidify() {}
    void operator&(std::ostream&) {}
};

class LogStreamBuf : public std::streambuf {
 public:
  LogStreamBuf(char *buf, int len) { setp(buf, buf + len - 2); }
  int_type overflow(int_type ch) { return ch; }
  size_t pcount() const { return static_cast<size_t>(pptr() - pbase()); }
  char* pbase() const { return std::streambuf::pbase(); }
};

class LogStream : public std::ostream {
  public:
    LogStream(char *buf, int len, int64_t ctr)
        : std::ostream(NULL),
          streambuf_(buf, len),
          ctr_(ctr),
          self_(this) {
      rdbuf(&streambuf_);
    }
    int64_t ctr() const { return ctr_; }
    void set_ctr(int64_t ctr) { ctr_ = ctr; }
    LogStream* self() const { return self_; }
    size_t pcount() const { return streambuf_.pcount(); }
    char* pbase() const { return streambuf_.pbase(); }
    char* str() const { return pbase(); }
  private:
    LogStream(const LogStream&);
    LogStream& operator=(const LogStream&);
    LogStreamBuf streambuf_;
    int64_t ctr_ = 0;
    LogStream *self_ = nullptr;
};

class LogMessage {
  public:
    static const int kMaxLogMessageLen = 30000;
    LogMessage(const char *file, int line, SEVERITY severity)
      : loc_(file, line), severity_(severity)
      , stream_(message_text_, kMaxLogMessageLen, 0) {}
    std::ostream& stream() { return stream_; }
    ~LogMessage() { flush(); }
  private:
    void flush();
  private:
    Logger::Location loc_;
    SEVERITY severity_;
    char message_text_[kMaxLogMessageLen+1] = {0};
    LogStream stream_;
};

class Global {
  public:
    static Global& Instance() {
      static Global glb;
      return glb;
    }
    Global() {}
    void SetLogger(std::shared_ptr<Logger> logger) { logger_ = logger; }
    std::shared_ptr<Logger> GetLogger() { assert(logger_); return logger_; }
  private:
    SEVERITY severity_ = SEVERITY_OFF;
    std::shared_ptr<Logger> logger_;
};

#define SET_COMMON_LOGGER(logger)                                                 \
  cmlg::Global::Instance().SetLogger(logger)
#define GET_COMMON_LOGGER()                                                       \
  cmlg::Global::Instance().GetLogger()
#define IS_NEED_LOGGING(severity)                                                 \
  (GET_COMMON_LOGGER()->GetSeverity() <= cmlg::SEVERITY_ ## severity)
#define LOG_MESSAGE_STREAM(severity)                                              \
  cmlg::LogMessageVoidify() &                                                     \
  cmlg::LogMessage(__FILE__, __LINE__, cmlg::SEVERITY_ ## severity).stream()
#define COMMON_LOG(severity)                                                      \
  static_cast<void>(0),                                                           \
  !IS_NEED_LOGGING(severity)? (void) 0 : LOG_MESSAGE_STREAM(severity)

} // end namespace cmlg

#endif