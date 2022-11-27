# CommLog Library

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/sullivan1205/commlog) ![GitHub](https://img.shields.io/github/license/sullivan1205/commlog?logo=MIT)

CommLog 主要解决第三方库的日志打印问题。比如 程序A依赖第三方库B，希望B也能够使用A的日志输出，而B是另一个团队开发的，最开始不知道A用什么日志库，不能对A进行适配。就算对A进行了适配，后面再出来C呢，还要对C进行适配吗？为了不让B的日志打印特性不跟A和C耦合，所以提出了 CommLog的方案。

***关于依赖注入设计模式?***

依赖注入（Dependency Injection，简称DI）是一种设计模式。当某个角色（调用者） 需要另一个角色（被调用者）的协助时，在 传统的程序设计过程中，通常由调用者来创建被调用者的实例。但是使用依赖注入设计模式，创建被调用者的工作不再由调用者来完成，因此称为控制反转；创建被调用者实例的工作通常由第三方来完成，然后注入调用者，因此也称为依赖注入。

依赖注入有两种：设值注入、构造注入。设置注入是指通过Setter成员函数来设置被调用者的实例；而构造注入是指在调用者实例构造函数时就通过参数将被调用者的实例传入调用者。

***为什么要使用依赖注入设计模式?***

程序A依赖第三方库B，A有自己的日志打印方式，那需要考虑的问题是怎么让B也适用A的日志打印方式？B完全不知道A和C是什么日志打印方式，此时B最想做的事情是：“A和C，你们告诉我如何打印日志，我就怎么打印日志。”。

好，目的明确了，就是B来适配A和C的日志打印，最好是把这部分工作交给A和C自己来做（生成实例），做好了再交给（注入）B即可。这不就是依赖注入设计模式吗？

所以，依赖注入设计模式是解耦第三方库日志打印的的最优雅的实现方式。

## 方案概要

### 1. 抽象一个 Logger 接口

```c++
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
```

### 2. 提供一个日志打印API

```c++
COMMON_LOG(DEBUG) << "this is a test log message";
```

### 3. 提供一个 Setter

```c++
SET_COMMON_LOGGER(logger)
```

> 注：开发者实现 Logger 接口。然后通过 SET_COMMON_LOGGER 设置到 CommLog中。这样就能通过 COMMON_LOG 接口来调用该logger进行日志打印。

请参考「 [example](./example)」。

## 编译安装

```bash
$ cd commlog
$ make clean
$ make
$ ls lib/libcommlog.a
$ ls example/example
```

# License

MIT（见「[这里](https://github.com/sullivan1205/commlog/blob/master/LICENSE)」）。

## 贡献

欢迎交流。

## 联系方式

sullivan_1205@126.com

## 参考方案

参考了 [glog](https://github.com/google/glog) 的流式打印实现。
