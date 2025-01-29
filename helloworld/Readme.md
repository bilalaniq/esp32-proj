# ESP32-S3 Hello World Log 🚀

This is a simple ESP32-S3 project that demonstrates how to write a "Hello World" log message using the **ESP-IDF** framework. 💻

## Requirements 📦

- **ESP32-S3** development board 🧑‍💻
- **ESP-IDF** development environment (follow the [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/)) 🌐
- **Serial Monitor** to view logs 📲

### 3. Configure the Project ⚙️

Run the following command to configure your ESP32-S3 project settings:

```bash
idf.py menuconfig
```

### 4. Build the Project 🛠️

Compile the project using the following command:

```bash
idf.py build
```

### 5. Flash the ESP32-S3 🦸‍♂️

Once the build completes successfully, flash the firmware to your ESP32-S3 board:

```bash
idf.py -p (YOUR PORT) flash
```

### 6. Monitor the Logs 📡

After flashing, monitor the serial output to see the "Hello World" log message. Run:

```bash
idf.py -p (YOUR PORT) monitor
```

You should see the following output in your serial monitor:

```
I (1000) MAIN: Hello, World! 🌍
```

## 📜 Project Structure

Here’s an overview of the project structure:

```
/project
   /main                # Contains the main application code
     CMakeLists.txt
     main.c             # Main application file

     inc
        main.h             # Header file for the main application
   /components          # Custom components (if any)
   CMakeLists.txt       # CMake configuration for the project
   sdkconfig    #file created after configrasion
   README.md            # This file
```

## Code Explanation 💡

In `main.c`, we use the ESP-IDF logging library to print a simple "Hello World" message:

```c
#include "inc/main.h"

#define LOG_LEVEL_LOCAL ESP_LOG_VERBOSE
#include "esp_log.h"
#define LOG_TAG "MAIN"

void app_main(void)
{
    while (1)
    {
        ESP_LOGI(LOG_TAG, "hello world");
        vTaskDelay(pdsec);
    }
}
```

In the main.h we are using freeRTOS for functions such as
`vTaskDelay()` and `pdMS_TO_TICKS()`

```c
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define pdsec pdMS_TO_TICKS(1000)
```
