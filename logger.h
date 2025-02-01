/**
 * @file logger.h
 * @brief Header file for the dynamically configurable logger.
 *
 * This header defines the logging functions and signal handling for
 * dynamic log level control.
 *
 * @author Mohamed Hamam
 * @date 30-01-2025
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/**
 * @enum log_level_t
 * @brief Enumeration of log levels.
 */
typedef enum {
    LOG_DISABLED = 0, /**< Logging disabled */
    LOG_ERROR,        /**< Error messages */
    LOG_WARNING,      /**< Warning messages */
    LOG_INFO,         /**< Info messages */
    LOG_DEBUG         /**< Debug messages */
} log_level_t;

/** @brief Global log level variable */
extern volatile sig_atomic_t current_log_level;

/**
 * @brief Signal handler to update log level dynamically.
 * @param signum Signal number (SIGUSR1)
 */
void signal_handler(int signum);

/**
 * @brief Logs a message if the current level allows it.
 * @param level The log level of the message.
 * @param fmt The format string (like printf).
 */
void log_message(log_level_t level, const char *fmt, ...);

/**
 * @brief Sets up the signal handler.
 */
void setup_signal_handler();

/** @brief Macro for logging errors */
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR, fmt, ##__VA_ARGS__)

/** @brief Macro for logging warnings */
#define LOG_WARNING(fmt, ...) log_message(LOG_WARNING, fmt, ##__VA_ARGS__)

/** @brief Macro for logging info */
#define LOG_INFO(fmt, ...) log_message(LOG_INFO, fmt, ##__VA_ARGS__)

/** @brief Macro for logging debug messages */
#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG, fmt, ##__VA_ARGS__)

#endif // LOGGER_H
