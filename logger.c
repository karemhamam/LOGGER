/**
 * @file logger.c
 * @brief Implementation of the dynamically configurable logger.
 *
 * This logger provides four logging levels (ERROR, WARNING, INFO, DEBUG)
 * and allows dynamic configuration via signals.
 *
 * @author Mohamed Hamam
 * @date 30-01-2025
 */

#include "logger.h"

/** Global log level variable */
volatile sig_atomic_t current_log_level = LOG_DEBUG;

/**
 * @brief Signal handler to update log level dynamically.
 * @param signum Signal number (SIGUSR1)
 */
void signal_handler(int signum) {
    FILE *file = fopen("/tmp/log_level.txt", "r");
    if (!file) {
        perror("Failed to open log level file");
        return;
    }

    char level[16];
    if (fgets(level, sizeof(level), file)) {
        if (strcmp(level, "disable\n") == 0) current_log_level = LOG_DISABLED;
        else if (strcmp(level, "error\n") == 0) current_log_level = LOG_ERROR;
        else if (strcmp(level, "warning\n") == 0) current_log_level = LOG_WARNING;
        else if (strcmp(level, "info\n") == 0) current_log_level = LOG_INFO;
        else if (strcmp(level, "debug\n") == 0) current_log_level = LOG_DEBUG;
    }
    fclose(file);
}

/**
 * @brief Logs a message if the current level allows it.
 * @param level The log level of the message.
 * @param fmt The format string (like printf).
 */
void log_message(log_level_t level, const char *fmt, ...) {
    if (level > current_log_level) return;

    const char *level_str[] = {"DISABLED", "ERROR", "WARNING", "INFO", "DEBUG"};
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buf[20];

    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);

    printf("[%s] [%s] ", time_buf, level_str[level]);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}

/**
 * @brief Sets up the signal handler.
 */
void setup_signal_handler() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Main function of the logger.
 */
int main() {
    setup_signal_handler();
    
    while (1) {
        LOG_ERROR("This is an error message");
        LOG_WARNING("This is a warning message");
        LOG_INFO("This is an info message");
        LOG_DEBUG("This is a debug message");

        sleep(5); // Simulate activity
    }

    return 0;
}
