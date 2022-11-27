#include <iostream>
#include "../src/commlog.h"

class MyLogger: public cmlg::Logger {
  public:
    MyLogger(cmlg::SEVERITY severity): cmlg::Logger(severity) {}
    virtual void Trace(Location& loc, const char* message) override {
      std::cout << "[TRACE][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
    virtual void Debug(Location& loc, const char* message) override {
      std::cout << "[DEBUG][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
    virtual void Info(Location& loc, const char* message) override {
      std::cout << "[INFO][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
    virtual void Warning(Location& loc, const char* message) override {
      std::cout << "[WARNING][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
    virtual void Error(Location& loc, const char* message) override {
      std::cout << "[ERROR][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
    virtual void Fatal(Location& loc, const char* message) override {
      std::cout << "[FATAL][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
    virtual void Off(Location& loc, const char* message) override {
      std::cout << "[OFF][" << loc.file_ << ":" << loc.line_ << "] " << message << std::endl;
    }
};

int main() {
  SET_COMMON_LOGGER(std::make_shared<MyLogger>(cmlg::SEVERITY_INFO));
  COMMON_LOG(DEBUG) << "this is a test log message";
  COMMON_LOG(WARNING) << "this is a test log message";
  COMMON_LOG(ERROR) << "this is a test log message";
  COMMON_LOG(FATAL) << "this is a test log message";
  return 0;
}