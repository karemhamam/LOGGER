# Logger Module

A dynamically configurable logging system that supports real-time signal-based log level control. The module provides four logging levels:

- **LOG\_ERROR**   → Critical errors that require immediate attention.
- **LOG\_WARNING** → Non-critical warnings.
- **LOG\_INFO**    → Informational messages.
- **LOG\_DEBUG**   → Detailed debugging messages.

The log level can be modified dynamically using a signal sent by another application.

---

## Features

✅ Supports dynamic log level updates using signals\
✅ Provides `LOG_ERROR`, `LOG_WARNING`, `LOG_INFO`, and `LOG_DEBUG` levels\
✅ Uses a separate application (`set_log_level`) to modify logging levels in real-time\
✅ Writes logs with timestamps and log levels\
✅ Implements real-time signaling for efficient log control

---

## Installation

### 1️⃣ Compile the Logger

```sh
gcc -o logger logger.c
```

### 2️⃣ Compile the Log Level Setter

```sh
gcc -o set_log_level set_log_level.c
```

---

## Usage

### **Start the Logger**

Run the logger in the background:

```sh
./logger &
echo $! > logger.pid  # Store the process ID (PID)
```

### **Modify the Log Level**

Use the `set_log_level` application to dynamically change the logging level:

```sh
./set_log_level <level> $(cat logger.pid)
```

#### Example Usage:

```sh
./set_log_level error $(cat logger.pid)     # Show only ERROR logs
./set_log_level warning $(cat logger.pid)   # Show ERROR and WARNING logs
./set_log_level info $(cat logger.pid)      # Show ERROR, WARNING, and INFO logs
./set_log_level debug $(cat logger.pid)     # Show all logs
./set_log_level disable $(cat logger.pid)   # Disable logging
```

### **Stop the Logger**

To terminate the logger process:

```sh
kill $(cat logger.pid)
rm logger.pid
```

---

## Log Output Format

Each log entry follows this format:

```
[YYYY-MM-DD HH:MM:SS] [LOG_LEVEL] Message
```

Example output:

```
[2025-02-01 12:00:00] [ERROR] This is an error message
[2025-02-01 12:00:00] [WARNING] This is a warning message
[2025-02-01 12:00:00] [INFO] This is an info message
[2025-02-01 12:00:00] [DEBUG] This is a debug message
```

---

## Debugging & Troubleshooting

- **Check if the logger is running:**
  ```sh
  ps aux | grep logger
  ```
- **Verify the current log level:**
  ```sh
  cat /tmp/log_level.txt
  ```
- **Manually trigger the signal:**
  ```sh
  kill -SIGUSR1 $(cat logger.pid)
  ```

---

## Future Enhancements

🚀 Add support for logging to files\
🚀 Implement a configuration file for default settings\
🚀 Enable log rotation to manage file sizes

---

## Author

👨‍💻 **Mohamed Hamam**

This project is part of my journey into system programming, real-time signaling, and embedded systems. Feel free to contribute or provide feedback! 😊



