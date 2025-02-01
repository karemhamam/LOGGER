/**
 * @file set_log_level.h
 * @brief Header file for the log level setter program.
 *
 * This header provides function declarations for dynamically updating
 * the log level of the logger process.
 *
 * @author Mohamed
 * @date 2025-02-01
 */

#ifndef SET_LOG_LEVEL_H
#define SET_LOG_LEVEL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define LOG_FILE "/tmp/log_level.txt" /**< File storing log level */

/**
 * @brief Prints usage instructions.
 * @param prog_name The name of the program.
 */
void usage(const char *prog_name);

#endif // SET_LOG_LEVEL_H
