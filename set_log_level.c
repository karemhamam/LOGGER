/**
 * @file set_log_level.c
 * @brief A program to dynamically change the logger's log level.
 *
 * This program writes the desired log level to a file and sends SIGUSR1
 * to the logger process to update its log level.
 *
 * @author Mohamed
 * @date 2025-02-01
 */

#include "set_log_level.h"


/**
 * @brief Prints usage instructions.
 * @param prog_name The name of the program.
 */
void usage(const char *prog_name) {
    printf("Usage: %s <disable|error|warning|info|debug> <logger_pid>\n", prog_name);
    exit(EXIT_FAILURE);
}

/**
 * @brief Main function to update log level.
 */
int main(int argc, char *argv[]) {
    if (argc != 3) usage(argv[0]);

    const char *level = argv[1];
    pid_t logger_pid = atoi(argv[2]);

    FILE *file = fopen(LOG_FILE, "w");
    if (!file) {
        perror("Failed to open log file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s\n", level);
    fclose(file);

    // Send signal to logger process
    if (kill(logger_pid, SIGUSR1) == -1) {
        perror("Failed to send signal");
        return EXIT_FAILURE;
    }

    printf("Log level changed to %s\n", level);
    return 0;
}
