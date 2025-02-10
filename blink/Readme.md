## ESP32-S3 Blink Example Log

## GPIO & Addressable LED Strip 🚀

This project demonstrates how to blink an LED using the **ESP-IDF** framework on an **ESP32-S3** development board. 💻

`note`: i will be writing this code to blink

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

In the Example Configuration menu:

Select the LED type in the Blink LED type option.
Use GPIO for regular LED
Use LED strip for addressable LED
If the LED type is LED strip, select the backend peripheral
RMT is only available for ESP targets with RMT peripheral supported
SPI is available for all ESP targets
Set the GPIO number used for the signal in the Blink GPIO number option.
Set the blinking period in the Blink period in ms option.

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

# GPIO pins

**GPIO** stands for **General Purpose Input/Output**. These are pins on a microcontroller (like the ESP32) that can be configured to either receive (input) or send (output) digital signals. These pins are versatile and allow you to interface with external devices like sensors, actuators (e.g., motors, LEDs), buttons, displays, etc.

In simpler terms, **GPIO pins** are the "communication interface" between the microcontroller and the outside world.

### General Features of GPIO

1. **Input Mode**:

   - When a GPIO pin is set to **input mode**, it reads signals from external devices, such as a button, a sensor, or other digital devices.
   - **Digital Input**: The pin can detect whether the external signal is **HIGH (1)** or **LOW (0)** (often referred to as logic levels 1 or 0).
   - **Analog Input**: Some GPIO pins on the ESP32 can also be used to read **analog signals** (though this is not the case for all GPIOs), such as voltage levels from sensors.

2. **Output Mode**:

   - When a GPIO pin is set to **output mode**, the pin can provide a **HIGH** (3.3V) or **LOW** (0V) signal to external devices, like turning an LED on/off or sending a signal to control a relay.
   - **Digital Output**: The output pin can drive a **HIGH** (3.3V) or **LOW** (0V) voltage to control devices. For example, sending a **HIGH** signal to an LED might turn it on, while **LOW** turns it off.

3. **Special Functions**:

   - Some GPIO pins have **special functions** such as:
     - **PWM (Pulse Width Modulation)**: Used for controlling devices like motors or dimming LEDs.
     - **I2C, SPI, UART**: Communication protocols that use GPIO pins for serial communication.
     - **ADC (Analog-to-Digital Converter)**: Some GPIO pins can read **analog values** (voltage).
     - **DAC (Digital-to-Analog Converter)**: Certain pins can output an analog signal.
     - **Interrupts**: GPIOs can trigger events based on external changes (e.g., pressing a button).

4. **High-Speed I/O**:
   - Some GPIO pins can be configured for high-speed communication protocols, like **SPI** or **I2C**, which are used for talking to sensors and external devices.

### ESP32 GPIO Overview

The **ESP32** is a powerful microcontroller with many GPIO pins (typically 34–39 available depending on the variant). Each GPIO pin can be configured in different ways based on your application needs.

Here's a breakdown of the features for GPIOs on the **ESP32** (and ESP32-S3):

#### 1. **GPIO Pin Configuration**:

Each GPIO pin can be configured for different modes:

- **GPIO_MODE_INPUT**: Pin is configured as an input.
- **GPIO_MODE_OUTPUT**: Pin is configured as an output.
- **GPIO_MODE_INPUT_PULLUP**: Input mode with a **pull-up resistor** (used to make sure the pin is HIGH unless actively pulled LOW).
- **GPIO_MODE_INPUT_PULLDOWN**: Input mode with a **pull-down resistor** (used to make sure the pin is LOW unless actively pulled HIGH).
- **GPIO_MODE_OUTPUT_OD**: Open-drain output mode (used in communication protocols like I2C).
- **GPIO_MODE_INPUT_PULLUP_PULLDOWN**: Some advanced modes for specific hardware needs.

#### 2. **Digital Input/Output**:

For digital signals, you can set a GPIO pin to either **HIGH (3.3V)** or **LOW (0V)**.

- To **read** a pin (input), use:
  ```c
  int pin_value = gpio_get_level(GPIO_PIN);  // Returns 0 (LOW) or 1 (HIGH)
  ```
- To **write** a pin (output), use:
  ```c
  gpio_set_level(GPIO_PIN, 1);  // Set GPIO to HIGH (3.3V)
  gpio_set_level(GPIO_PIN, 0);  // Set GPIO to LOW (0V)
  ```

#### 3. **Analog Input (ADC)**:

Some GPIO pins on the ESP32 are capable of reading **analog voltages** using the **ADC** (Analog-to-Digital Converter) functionality.

- **ADC Pins**: Pins like **GPIO 32**, **GPIO 33**, etc., can read analog values (0 to 3.3V). The ESP32 maps these voltages into digital values (0-4095 for a 12-bit ADC).

Example code for reading an analog signal:

```c
int analog_value = adc1_get_raw(ADC1_CHANNEL_0);  // Read analog value from GPIO 36 (ADC1_CHANNEL_0)
```

#### 4. **PWM (Pulse Width Modulation)**:

PWM is a technique for controlling the power supplied to devices like LEDs and motors by rapidly switching the GPIO pin on and off. The width of the "on" period controls the effective power.

- ESP32 has hardware support for generating PWM signals. You can use the **LEDC (LED Controller)** driver to generate PWM signals on any GPIO pin.

Example code for PWM on GPIO 13:

```c
ledc_timer_config_t timer = {
    .speed_mode       = LEDC_HIGH_SPEED_MODE,
    .timer_num        = LEDC_TIMER_0,
    .duty_resolution  = LEDC_TIMER_8_BIT,  // 8-bit resolution (0-255)
    .freq_hz          = 5000,              // Frequency of PWM signal
    .clk_cfg           = LEDC_AUTO_CLK,
};
ledc_timer_config(&timer);

ledc_channel_config_t channel = {
    .gpio_num       = GPIO_NUM_13,
    .speed_mode     = LEDC_HIGH_SPEED_MODE,
    .channel        = LEDC_CHANNEL_0,
    .intr_type      = LEDC_INTR_DISABLE,
    .timer_sel      = LEDC_TIMER_0,
    .duty           = 128,  // 50% duty cycle (out of 255)
    .hpoint         = 0,
};
ledc_channel_config(&channel);
```

#### 5. **Interrupts**:

You can configure GPIO pins to trigger an interrupt based on an event, like a rising or falling edge (e.g., when a button is pressed or released).

Example code for a button press on GPIO 14:

```c
void IRAM_ATTR gpio_isr_handler(void* arg) {
    // Interrupt handler
}

gpio_set_intr_type(GPIO_NUM_14, GPIO_INTR_NEGEDGE);  // Trigger on falling edge (button press)
gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);  // Install the ISR service
gpio_isr_handler_add(GPIO_NUM_14, gpio_isr_handler, NULL);  // Add the interrupt handler
```

#### 6. **Open-Drain Mode**:

In some situations, you might want the GPIO pin to act as an **open-drain**. This means the pin can only pull the signal **LOW**, and external pull-up resistors are required to pull it **HIGH** when not driven.

This is common in communication protocols like **I2C**.

### ESP32 GPIO Pinout and Special Functions

The ESP32 has several GPIO pins that have **special functions**, meaning they can be used for specific purposes (e.g., **UART**, **SPI**, **I2C**, etc.). Here's an overview of how these functions work:

- **GPIO 1 and 3**: Typically used for **UART0 TX and RX** (used for serial communication).
- **GPIO 21 and 22**: Commonly used for **I2C SDA and SCL** (used for I2C communication).
- **GPIO 23, 19, 18**: Often used for **SPI MOSI, MISO, and SCK**.
- **GPIO 34 to 39**: Often used for **ADC** (analog inputs).

Some of these functions can be remapped or configured in the ESP32 to suit your application.

By configuring the GPIOs properly, you can interface the ESP32 with virtually any external device, making it ideal for embedded applications.

---

# GPIO & Addressable LED Strip

Now here in our project we are going to use te buildin LED in the ESP32s3
to use that we should know the diffrence between

- Addressable LED Strip
- GPIO-based LED

### 1. **Addressable LED Strip (`CONFIG_BLINK_LED_STRIP`)**

- **Used when you are using an addressable LED strip** (such as WS2812, SK6812, or similar addressable LEDs).
- The `blink_led()` function sets the color of the LED at index 0 to a specific RGB value (16, 16, 16), meaning a dim white color (since it’s using the `led_strip_set_pixel` function).
- The `configure_led()` function initializes the addressable LED strip, either using the **RMT backend** or **SPI backend** based on the configuration (`CONFIG_BLINK_LED_STRIP_BACKEND_RMT` or `CONFIG_BLINK_LED_STRIP_BACKEND_SPI`).
- This checks for the proper backend and initializes the `led_strip` object accordingly.

**When this option is enabled**:

- This is to set up control **an addressable LED strip** connected to a specific GPIO (defined as `BLINK_GPIO`).
- The `led_strip_rmt_config_t` and `led_strip_spi_config_t` structures are used to configure the RMT or SPI peripherals for controlling the strip.


# RMT VS SPI

| **Aspect**                  | **SPI (Serial Peripheral Interface)**                                         | **RMT (Remote Control Transmitter)**                                      |
|-----------------------------|---------------------------------------------------------------------------------|---------------------------------------------------------------------------|
| **Definition**               | SPI is a synchronous serial communication protocol used to transfer data between a master and one or more peripheral devices. | RMT is a protocol designed for transmitting and receiving infrared (IR) remote control signals, often used in consumer electronics. |
| **Purpose**                  | Primarily used for communication between microcontrollers and peripherals like sensors, SD cards, displays, etc. | Specifically designed for transmitting IR signals (e.g., TV remotes, air conditioners). |
| **Data Transfer Type**       | Full-duplex data transfer (simultaneous two-way communication).                  | Half-duplex communication (transmits data, but doesn't receive while transmitting). |
| **Signal Type**              | Uses clock (SCK), master-out slave-in (MOSI), master-in slave-out (MISO), and chip select (CS) signals. | Encodes data into pulses of infrared light for remote control communication. |
| **Data Transmission Mode**   | Synchronous – relies on a clock signal to sync data transfer.                   | Asynchronous – uses timing and encoding schemes specific to IR signals. |
| **Speed**                    | Generally operates at higher speeds (up to tens of MHz).                         | Typically slower compared to SPI (up to 1-4 MHz). |
| **Connection**               | Requires at least 4 wires: SCK, MOSI, MISO, and CS.                             | Requires a single wire for transmitting infrared signals, with an additional one for receiving in some cases. |
| **Hardware Requirements**    | Requires SPI controller on both master and slave devices.                      | Requires an IR LED for transmission and an IR receiver for reception. |
| **Protocol Complexity**      | More complex with multiple data lines (MOSI, MISO, SCK, CS) and clock synchronization. | Less complex as it primarily encodes data into a pulse stream for transmission. |
| **Error Detection**          | Error detection can be implemented via checksums, CRC, etc.                     | Basic error detection via timing (e.g., invalid pulse sequence). |
| **Application Example**      | Used in sensors, ADCs, DACs, memory devices, and displays.                      | Used in TV remote controls, air conditioners, and other IR-based consumer electronics. |
| **Clocking**                 | Relies on a clock signal (SCK) for synchronization.                             | No clock signal; timing is encoded into the pulse width of the IR signal. |
| **Transmission Method**      | Data is transferred in parallel (multiple bits per clock cycle) over multiple wires. | Data is transferred in a serial, bit-by-bit manner over the IR channel. |
| **Error Handling**           | Can handle data errors with mechanisms like parity checks, CRCs, and retries.  | Limited error handling; generally depends on signal integrity and timeouts. |
| **Communication Range**      | Typically short distances (few cm to meters) depending on wire length and power. | Typically ranges from a few centimeters to several meters, depending on the IR transmitter's power. |
| **Power Consumption**        | Generally consumes more power due to continuous data transfer and clock signals. | Lower power consumption, especially in low-duty cycle applications. |
| **Multicast/Multiplexing**   | Supports multiple peripherals (slaves) connected to the same master device.     | Supports point-to-point communication; cannot directly support multiple devices unless managed by the remote protocol. |
| **Signal Integrity**         | Data integrity is ensured by clock synchronization and usually operates in a noise-resistant environment. | Signal integrity depends on IR signal strength, line-of-sight, and environmental factors (e.g., light interference). |

### Key Takeaways:
- **SPI** is designed for high-speed, multi-device communication in a wired configuration, supporting full-duplex data transfer and synchronization with a clock signal.
- **RMT**, on the other hand, is focused on the transmission of IR signals, often used in consumer electronics like remote controls, operating over simple, half-duplex communication without the need for clock synchronization.





### 2. **GPIO-based LED (`CONFIG_BLINK_LED_GPIO`)**

- **Used when you are using a regular, simple LED** connected to a GPIO pin (this could be an onboard LED or a basic external LED).
- The `blink_led()` function controls the state of the GPIO (turns it ON or OFF) depending on the `s_led_state` variable (which is toggled in the main loop).
- The `configure_led()` function sets the GPIO pin as an output to control the LED.

**When this option is enabled**:

- The code configures a regular GPIO pin (`BLINK_GPIO`) to act as an LED, toggling the LED on or off by setting the GPIO level to HIGH or LOW.

### Summary of Configuration:

- **For an addressable LED strip**: The code will use either **RMT** or **SPI** for controlling the LED strip based on your configuration (`CONFIG_BLINK_LED_STRIP_BACKEND_RMT` or `CONFIG_BLINK_LED_STRIP_BACKEND_SPI`).
- **For a GPIO-based LED**: The code simply controls a regular LED (connected to a GPIO) by toggling the GPIO state between HIGH (ON) and LOW (OFF).

### What is the built-in LED in esp32s3?

The build in LED in esp32s3 is an addressable LED strip

- **If you are using an addressable LED strip**, the code configures the strip using **RMT** or **SPI**, and the ESP32-S3 will control the strip with higher flexibility (such as setting individual LEDs to different colors).



## project config

- ### idf_component.yml

```yml
# Use the idf_component.yml manifest file to describe the component and its dependencies. The manifest file is
# located in the root directory of the component.

dependencies:
  espressif/led_strip: "^2.4.1"

```

or you could simply write this in the terminal and it will work the same 

```bash
idf.py add-dependency espressif/led_strip@^2.4.1
```

- ### Kconfig.projbuild

The Kconfig.projbuild file is used in ESP-IDF projects to configure project-specific settings that are used during the build process. It allows you to define custom configuration options specific to your project, and these settings can be accessed via the ESP-IDF configuration menu (menuconfig).

How it works: The contents of Kconfig.projbuild are processed by the ESP-IDF's build system. The file typically includes options that configure your project’s settings, such as enabling or disabling certain features or defining project-specific values.

Here's an example of what a Kconfig.projbuild might look like:

```kconfig
menuconfig MY_PROJECT_FEATURE
    bool "Enable My Custom Feature"
    default y
    help
      This option enables the custom feature specific to my project.
```

When to use it?
Custom Features: When your project introduces new features that require configuration parameters.
Project-Specific Settings: When you need to specify settings that are only relevant to your project and not to the global ESP-IDF settings.



we have used this `kconfig` file in our blink project

```kconfig
menu "blink Configuration"

    orsource "$IDF_PATH/examples/common_components/env_caps/$IDF_TARGET/Kconfig.env_caps"

    choice BLINK_LED
        prompt "Blink LED type"
        default BLINK_LED_GPIO
        help
            Select the LED type. A normal level controlled LED or an addressable LED strip.
            The default selection is based on the Espressif DevKit boards.
            You can change the default selection according to your board.

        config BLINK_LED_GPIO
            bool "GPIO"
        config BLINK_LED_STRIP
            bool "LED strip"
    endchoice

    choice BLINK_LED_STRIP_BACKEND
        depends on BLINK_LED_STRIP
        prompt "LED strip backend peripheral"
        default BLINK_LED_STRIP_BACKEND_RMT if SOC_RMT_SUPPORTED
        default BLINK_LED_STRIP_BACKEND_SPI
        help
            Select the backend peripheral to drive the LED strip.

        config BLINK_LED_STRIP_BACKEND_RMT
            depends on SOC_RMT_SUPPORTED
            bool "RMT"
        config BLINK_LED_STRIP_BACKEND_SPI
            bool "SPI"
    endchoice

    config BLINK_GPIO
        int "Blink GPIO number"
        range ENV_GPIO_RANGE_MIN ENV_GPIO_OUT_RANGE_MAX
        default 8
        help
            GPIO number (IOxx) to blink on and off the LED.
            Some GPIOs are used for other purposes (flash connections, etc.) and cannot be used to blink.

    config BLINK_PERIOD
        int "Blink period in ms"
        range 10 3600000
        default 1000
        help
            Define the blinking period in milliseconds.

endmenu

```



- ### CMAKE (inside main dir)

```cmake
idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES freertos esp_common driver led_strip)
```

we have included the `led_strip` which was included in the project by the `idf_component.yml` file


- ### CMAKE
```cmake
# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(blink)

```



- ## TO Blink the buildin LED strip in esp32s3 you also need to configure 
**stkconfig.defaults** or **stkconfig.defaults.esp32s3**  (specifically for esp32s3)

```bash
CONFIG_BLINK_LED_STRIP=y
CONFIG_BLINK_GPIO=48 
```

in esp32s3 the gpio pin which is used to blink the buildin led in esp32s3 is 48 so you need to change it form 8 to this



## Code Explanation 💡

### `main.h`

```c
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
```

### `main.c` – Blinking the LED

```c
#include <stdlib.h>  // For rand() and srand()
#include <time.h>    // For time()



#define LOG_LEVEL_LOCAL ESP_LOG_VERBOSE
#include "esp_log.h"
#define LOG_TAG "MAIN"
#include "main.h"

#define TAG "MAIN"

#define BLINK_GPIO_pin CONFIG_BLINK_GPIO

static uint8_t Led_State = 0;

#ifdef CONFIG_BLINK_LED_STRIP

static led_strip_handle_t Led_strip;

static void Toggle(void)
{
    Led_State = !Led_State;
}

```

This file contains the logic to blink an LED connected to a GPIO pin.
As we have learned that there are two types of LED so we need to cheak which is present and work according to it


- ### ADDRESSABLE LED

```c
#ifdef CONFIG_BLINK_LED_STRIP

static led_strip_handle_t Led_strip;

```

### configuring the led on the basis of its backend (RMT or SPI)

```c

static void configure_led(void)
{
    ESP_LOGI(TAG, "configuring to blink addressable LED");

    led_strip_config_t strip_config =
        {
            .strip_gpio_num = BLINK_GPIO_pin,
            .max_leds = 1,
        };

#if CONFIG_BLINK_LED_STRIP_BACKEND_RMT
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };
// .flags.with_dma = false:
// Purpose: This setting specifies whether DMA (Direct Memory Access) is used for transmitting data through the RMT peripheral.
// DMA (Direct Memory Access): Using DMA allows the ESP32 to send large amounts of data (such as a large array of LED color data) to the RMT peripheral without using the CPU. This reduces the CPU load.
// false: Setting .with_dma = false means DMA is not enabled. This could mean that the data transmission will be handled by the CPU instead of DMA, which might be fine for smaller data sets or simpler applications.

// If you're dealing with a large number of LEDs or need the system to handle other tasks concurrently, using DMA would be a good choice because it allows the data transfer for LEDs to happen in the background.

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &Led_strip));

#elif CONFIG_BLINK_LED_STRIP_BACKEND_SPI

    led_strip_spi_config_t spi_config =
        {
            .spi_bus = SPI1_HOST,
            .flags.with_dma = false,
        };

// spi_bus = SPI1_HOST:
// Purpose: Specifies the SPI bus to use for communication with the LED strip.
// The ESP32 has multiple SPI buses (usually SPI1_HOST, SPI2_HOST, and SPI3_HOST), but typically, you will use SPI1 or SPI2 for controlling peripherals like LED strips.
// SPI1_HOST is the SPI bus you are choosing to use here. This allows you to send data to the LED strip using the SPI interface.     

// flags.with_dma = false:
// false means that DMA is disabled

    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &Led_strip));

#else
#error "unsupported LED backend"
#endif
}
```

### now blinking the addressable LED

```c

static uint8_t select_col_Ran(void)
{
    // Generate a random number between 0 and 9
    return rand() % 10;  // rand() % 10 gives values from 0 to 9
}

static void blink_led(uint8_t c_choice)
{

    if (Led_State)
    {

        switch (c_choice)
        {

        case 0:
            led_strip_set_pixel(Led_strip, 0, 255, 105, 180); // Pink

            break;
        case 1:
            led_strip_set_pixel(Led_strip, 0, 255, 0, 0); // red

            break;

        case 2:
            led_strip_set_pixel(Led_strip, 0, 0, 255, 0); // Green

            break;

        case 3:
            led_strip_set_pixel(Led_strip, 0, 0, 0, 255); // Blue

            break;
        case 4:
            led_strip_set_pixel(Led_strip, 0, 255, 255, 255); // White (full intensity of all colors)
            break;
        case 5:
            led_strip_set_pixel(Led_strip, 0, 255, 255, 0); // Yellow (Red + Green)

            break;

        case 6:
            led_strip_set_pixel(Led_strip, 0, 0, 255, 255); // Cyan (Green + Blue)

            break;

        case 7:
            led_strip_set_pixel(Led_strip, 0, 255, 0, 255); // Magenta (Red + Blue)

            break;

        case 8:
            led_strip_set_pixel(Led_strip, 0, 128, 0, 128); // Purple (a mix of Red and Blue)

            break;

        case 9:
            led_strip_set_pixel(Led_strip, 0, 255, 165, 0); // Orange

            break;

        default:
            break;
        }

        led_strip_refresh(Led_strip);
    }
    else
    {
        led_strip_clear(Led_strip);
    }
}
```

- ### GPIO LED

```c
#elif CONFIG_BLINK_LED_GPIO
```

### configuring the led on the basis of its backend (GPIO pin input or output mode)

```c
static void configure_led(void)
{
    ESP_LOGI(TAG, "configuring to blink GPIO LED");
    gpio_reset_pin(BLINK_GPIO_pin);
    gpio_set_direction(BLINK_GPIO_pin, GPIO_MODE_OUTPUT);
}

```

### blinking the GPIO LED

```c
static void blink_led(void)
{
    gpio_set_level(BLINK_GPIO_pin, Led_State);
}

```

---


## if the LED is nor addressable nor GPIO than 
```c
#else
#error "unsupported LED type"
#endif
```


- ## app_main

```c
void app_main(void)
{
    configure_led();

    while (1)
    {
        ESP_LOGI(TAG, "Turning the LED %s!", Led_State == true ? "ON" : "OFF");

#ifdef CONFIG_BLINK_LED_STRIP
        blink_led(select_col_Ran());
#elif CONFIG_BLINK_LED_GPIO
        blink_led();
#endif

        Toggle();
        // vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);  //slow
        vTaskDelay(500 / portTICK_PERIOD_MS); // faster
    }
}
```



## Conclusion 🌟

Once you upload this code to your ESP32-S3, your LED should blink on and off every second, and you'll see a log message indicating that the LED blink example is initialized. You can modify the delay or pin number to suit your project needs.
