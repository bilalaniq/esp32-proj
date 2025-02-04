## ESP32-S3 Blink Example Log   
## GPIO & Addressable LED Strip  🚀

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

     inc
        main.h             # Header file for the main application
   /components          # Custom components (if any)
   CMakeLists.txt       # CMake configuration for the project
   sdkconfig    # Configuration file created after setup
   README.md            # This file
```

## Code Explanation 💡

### `main.c` – Blinking the LED

This file contains the logic to blink an LED connected to a GPIO pin. We'll be using GPIO 13 for the example (you can change this to any other GPIO pin).





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




## Conclusion 🌟

Once you upload this code to your ESP32-S3, your LED should blink on and off every second, and you'll see a log message indicating that the LED blink example is initialized. You can modify the delay or pin number to suit your project needs.
