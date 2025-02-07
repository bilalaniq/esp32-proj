## ESP32-S3 WIFI SCAN 


This project demonstrates how to scan wifi using the **ESP-IDF** framework on an **ESP32-S3** development board. 💻


## Requirements 📦

- **ESP32-S3** development board 🧑‍💻
- **ESP-IDF** development environment (follow the [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/)) 🌐
- **Serial Monitor** to view logs 📲

### 1. Configure the Project ⚙️

Run the following command to configure your ESP32-S3 project settings:

```bash
idf.py menuconfig
```

Open the project configuration menu (idf.py menuconfig).


### 2. Build the Project 🛠️

Compile the project using the following command:

```bash
idf.py build
```

### 3. Flash the ESP32-S3 🦸‍♂️

Once the build completes successfully, flash the firmware to your ESP32-S3 board:

```bash
idf.py -p (YOUR PORT) flash
```

### 4. Monitor the Logs 📡

After flashing, monitor the serial output to see the logs. Run:

```bash
idf.py -p (YOUR PORT) monitor
```

You should see the following output in your serial monitor:

```
I (1000) MAIN: LED Blink Example Initialized 🚀
```

## 📜 Project Structure

Here’s an overview of the project structure:

```
/project
   /main                # Contains the main application code
     CMakeLists.txt
     main.c             # Main application file
     idf_component.yml
     Kconfig.projbuild

     inc
        main.h             # Header file for the main application
   /components          # Custom components (if any)
   CMakeLists.txt       # CMake configuration for the project
   sdkconfig    # Configuration file created after setup
   README.md            # This file
```
---


