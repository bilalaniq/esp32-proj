# ESP32 Project 🚀

Welcome to the ESP32-S3 project! This repository contains code and configuration for building applications on the ESP32-S3 using the ESP-IDF framework.

## 🔧 Requirements

Before you begin, make sure you have the following installed:

- [ESP-IDF Framework](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/) 🛠️
- [CMake](https://cmake.org/install/) 💻
- [Git](https://git-scm.com/) 🔄

## 📦 Setup Instructions

### 1. Clone the Repository

First, clone this repository to your local machine:

```bash
git clone https://github.com/bilalaniq/esp32-proj.git
cd esp32s3-project
```

### 2. Set up ESP-IDF

Set up the ESP-IDF environment:

```bash
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh  # For Linux/macOS
install.bat   # For Windows
source export.sh  # For Linux/macOS
export.bat    # For Windows
```

### 3. Configure the Project

To configure your project you need to use `ESP-IDF TERMINAL`
because `powershel` is unable to do

before configuring you also need to set the target by default it is esp32 so do accordingly but for me it is esp32s3

```bash
idf.py set-target esp32s3
```

confirm the target again because mostlly it is not set properly

```bash
echo $env:IDF_TARGET
```

if the target is still esp32

```bash
$env:IDF_TARGET = "esp32s3"
```

Use `menuconfig` to configure your project settings:

```bash
idf.py menuconfig
```

Make sure to configure the appropriate options for your ESP32-S3 or any other ESP.

### 4. Build the Project

Once you're ready, build the project:

```bash
idf.py build
```

### 5. Flash the Firmware

Connect your ESP32-S3 to your PC via USB and flash the firmware:

```bash
idf.py -p COMx flash  # Replace with your COM port
```

### 6. Monitor the Output

To monitor the output of the ESP32-S3:

```bash
idf.py -p COMx monitor
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
---
# VSCODE 

if you are working in windows add the esp-idf path in the envoirement variable and name it as `IDF_PATH`
To work in vscode you also need to edit the `.vscode`

## c_cpp_properties.json

```json
{
    "configurations": [
        {
            "name": "ESP-IDF",
            "compilerPath": "${config:idf.toolsPathWin}\\tools\\xtensa-esp-elf\\esp-14.2.0_20241119\\xtensa-esp-elf\\bin\\xtensa-esp32-elf-gcc.exe",
            "compileCommands": "${config:idf.buildPath}/compile_commands.json",
            "includePath": [
                "${config:idf.espIdfPath}/components/**",
                "${config:idf.espIdfPathWin}/components/**",
                "${workspaceFolder}/**"
            ],
            "browse": {
                "path": [
                    "${config:idf.espIdfPath}/components",
                    "${config:idf.espIdfPathWin}/components",
                    "${workspaceFolder}"
                ],
                "limitSymbolsToIncludedHeaders": true
            }
        }
    ],
    "version": 4
}

```

## launch.json

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "type": "gdbtarget",
      "request": "attach",
      "name": "Eclipse CDT GDB Adapter"
    },
    {
      "type": "espidf",
      "name": "Launch",
      "request": "launch"
    }
  ]
}
```

## settings.json

```json
{
    "C_Cpp.intelliSenseEngine": "default",
    "idf.espIdfPathWin": "c:\\esp\\esp-idf\\v5.4\\esp-idf",  //path to your esp-idf
    "idf.openOcdConfigs": [
        "board/esp32-wrover-kit-3.3v.cfg"
    ],
    "idf.portWin": "COM3",
    "idf.toolsPathWin": "c:\\esp\\esp-tools"  //path to you esp tools
}
```

---
# CMakeLists.txt

## CMakeLists.txt (in the project root directory):

- This is the primary CMake configuration file for your project. It includes general project configuration, such as setting the project name, specifying the build options, and including additional CMake modules or libraries if necessary.
- This file is responsible for managing the overall build process and can also contain settings for the ESP-IDF framework itself


```cmake
# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
#Including project.cmake essentially sets up your project to follow the ESP-IDF's build system conventions.
project(project_name)

```

## CMakeLists.txt (inside the component directories):

- Each component of the ESP-IDF (like libraries or application-specific code) has its own CMake file. These files are used to define how individual components should be compiled and linked together.
- If you're adding custom components or working with a library, each component will have its own CMakeLists.txt to specify how that component should be built and linked.


```cmake
idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES freertos esp_common)
#The build system will ensure that the required components (freertos and esp_common) are correctly included and linked when building this component.
#If your component requires any other components (e.g., for hardware-specific functionality), you can list them here as well.

```


## 💡 Features

- **ESP32-S3 support**: Leverage the powerful features of the ESP32-S3, including advanced peripherals and increased processing power.
- **FreeRTOS**: The project is built using FreeRTOS for multitasking and real-time application support.
- **ESP-IDF framework**: Using the robust ESP-IDF environment for reliable and scalable firmware development.

## ⚙️ Customization

You can easily customize this project to fit your needs by:

- Modifying the configuration in `menuconfig`
- Adding your own components to the `/components` directory
- Editing the `main.c` and `main.h` files to implement your custom application logic

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to adjust the repository name, add any relevant links, and modify project features to match your specific project. Let me know if you'd like any more additions!
