#pragma once

#include <string>

#include "noncopyable.h"


#define LOG_INFO(logMsgFormat, ...) \
    do { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_ERROR(logMsgFormat, ...) \
    do { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_FATAL(logMsgFormat, ...) \
    do { \
        Logger &logger = Logger::instance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
        exit(-1); \
    } while(0)

#ifdef SILLYDEBUG
    #define LOG_DEBUG(logMsgFormat, ...) \
        do { \
            Logger &logger = Logger::instance(); \
            logger.setLogLevel(DEBUG); \
            char buf[1024] = {0}; \
            snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
            logger.log(buf); \
        } while(0)
#else
    #define LOG_DEBUG(logMsgFormat, ...)
#endif

enum LogLevel {
    INFO,
    ERROR,
    FATAL,
    DEBUG
};

class Logger : noncopyable {
public:
    static Logger& instance();

    void setLogLevel(int level);

    void log(std::string msg);

private:
    int logLevel_;
    Logger(){}
};

