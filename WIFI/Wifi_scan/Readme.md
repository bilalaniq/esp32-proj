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



# configuring the project

- ##  Kconfig.projbuild

```projbuild

menu "Wi-Fi Configuration"

    config SCAN_LIST_SIZE
        int "Max size of scan list"
        range 0 20
        default 10
        help
            The size of array that will be used to retrieve the list of access points.

    config SCAN_CHANNEL_BITMAP
        bool "Scan only non overlapping channels using Channel bitmap"
        default 0
        help
            Enable this to scan only the non overlapping channels i.e 1,6,11 by mentioning a channel bitmap
            in scan config. If you wish to scan a different set of specific channels, please edit the channel_list
endmenu

```


- ## CMAKE (inside the main dir)

```cmake
idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES freertos esp_common driver esp_wifi nvs_flash)

# we need esp_wifi so we could intract with wifi 
# we also need nvs_flash to store the wifi credentials or other data

```


The NVS (Non-Volatile Storage) is a part of the ESP32 system that allows you to store data persistently, even after the device is powered off or reset. It’s often used to store configuration parameters, Wi-Fi credentials, device settings, or other important data that should persist across reboots.



- ## CMAKE (outside the main dir)



```cmake
# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(wifi_scan)

```

---
<br>
<br>
<br>

# **CODE**

## main.c

- ## libraries

```c
#include <string.h> // Provides functions for manipulating C-style strings and memory (e.g., memset, strcpy, strlen).
#include "freertos/FreeRTOS.h" // Provides FreeRTOS kernel functionality for managing tasks, time, memory, and synchronization.
#include "freertos/event_groups.h" // Provides functionality to create and manage event groups for task synchronization in FreeRTOS.
#include "esp_wifi.h" // Wi-Fi driver for ESP32, allows configuration and management of Wi-Fi features like scanning, connecting, etc.
#include "esp_log.h" // Provides logging functionality for outputting log messages (INFO, WARN, ERROR, DEBUG).
#include "esp_event.h" // Provides event loop management for handling asynchronous events and dispatching event handlers.
#include "nvs_flash.h" // Provides APIs for using Non-Volatile Storage (NVS) to persist data across device resets.
#include "regex.h" // Provides functions for working with regular expressions (matching, parsing, and validating string patterns).

```

- ## global veriables


```c
#define DEFAULT_SCAN_LIST_SIZE CONFIG_SCAN_LIST_SIZE  //10

#ifdef CONFIG_SCAN_CHANNEL_BITMAP   //if bitmap is enabled
#define USE_CHANNEL_BITMAP 1
#define CHANNEL_LIST_SIZE 3
static uint8_t channel_list[CHANNEL_LIST_SIZE] = {1, 6, 11};
//array consisting of channels to scan if bitmap is enabbled
#endif /*CONFIG_EXAMPLE_USE_SCAN_CHANNEL_BITMAP*/

static const char *TAG = "scan";

```



- ## app_main()

```c
void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // ESP_ERR_NVS_NO_FREE_PAGES: This error occurs when there is no available space left in the NVS storage.
        // ESP_ERR_NVS_NEW_VERSION_FOUND: This error occurs when there is a mismatch between the version of the NVS storage and the
        // version that your application expects.

        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_scan();
}
```

here we have to initilize the nvs flash because of the following reasons

In your code, the `nvs_flash_init()` and related calls to `nvs_flash_erase()` are required to initialize and manage the **NVS Flash** memory for the ESP32. This step is particularly important because the ESP32 uses NVS to store configuration settings like Wi-Fi credentials, which are critical for the Wi-Fi connection process.

### Why is **nvs_flash** Needed?

1. **Storing Wi-Fi Credentials**:
   - When the ESP32 connects to a Wi-Fi network, the device often stores the Wi-Fi credentials (SSID, password) in NVS, so it doesn't have to be re-entered each time the device is powered on.
   
2. **Persistent Configuration**:
   - If you have any settings or parameters you need to keep across restarts (e.g., device preferences, last connected network, calibration data), NVS is used to save this information.
   
3. **Required for Wi-Fi Operations**:
   - The ESP32 Wi-Fi stack relies on NVS for storing the configuration of the Wi-Fi network interface. If you use features like **Wi-Fi Station mode** (STA) or **Access Point mode** (AP), the system needs to be able to load these settings after a reset.


   Wi-Fi stack refers to the software and protocols that manage all aspects of Wi-Fi communication on the device. Specifically, it's the collection of functions, libraries, and internal components that ESP32 uses to connect, scan, and interact with Wi-Fi networks.

### What the Code Does:

1. **nvs_flash_init()**: Initializes the NVS flash. It prepares the storage area and makes sure that the ESP32 is ready to read and write to NVS. This is a required step before using the Wi-Fi APIs and other services that might rely on NVS for persistent data storage.

2. **nvs_flash_erase()**: This clears any previously stored data in the NVS. It’s used here to handle cases where the NVS has an issue (e.g., no free pages or a version mismatch). This might happen when upgrading or changing your application.

3. **Error Handling**: If there’s an issue with NVS initialization, like insufficient free space (`ESP_ERR_NVS_NO_FREE_PAGES`) or a version mismatch (`ESP_ERR_NVS_NEW_VERSION_FOUND`), the NVS is erased and reinitialized to ensure that the system can continue functioning properly.


---

<br>


- ## wifi_scan()


```c
/* Initialize Wi-Fi as sta and set scan method */
static void wifi_scan(void)
{
    ESP_ERROR_CHECK(esp_netif_init()); // This function initializes the internal networking system of the ESP32, which is necessary for
    // enabling Wi-Fi and Ethernet support.

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    // esp_event_loop_create_default() is a function used to create the default event loop in an ESP32 application. The event loop is a
    // core part of handling asynchronous events in your program, such as network events, sensor data, or system notifications.

    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    // This line creates a default network interface for Wi-Fi Station (STA) mode. The ESP32 can either operate in Station mode (STA)
    // (connecting to a router) or Access Point mode (AP) (acting as a router). This code sets up the ESP32 to scan as a Wi-Fi station (STA).
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // Purpose: This prepares the Wi-Fi initialization configuration (wifi_init_config_t). WIFI_INIT_CONFIG_DEFAULT() is a macro
    // that provides a default Wi-Fi configuration structure.
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    // This function initializes the Wi-Fi driver with the provided configuration. It’s required before starting any Wi-Fi operations
    // (like scanning or connecting).

    // uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

#ifdef USE_CHANNEL_BITMAP
    wifi_scan_config_t *scan_config = (wifi_scan_config_t *)calloc(1, sizeof(wifi_scan_config_t));
    if (!scan_config)
    {
        ESP_LOGE(TAG, "Memory Allocation for scan config failed!");
        return;
    }
    array_2_channel_bitmap(channel_list, CHANNEL_LIST_SIZE, scan_config);

    //     array_2_channel_bitmap(): This function likely converts a list of channel numbers (channel_list) into a channel bitmap format.
    // A channel bitmap is a representation of the channels you want to scan, where each bit in the bitmap represents whether a
    // specific channel should be included in the scan. For example, if you want to scan only channels 1, 6, and 11, the bitmap would
    // be set to include only those channels.

    esp_wifi_scan_start(scan_config, true);
    free(scan_config);

    // In Wi-Fi networks, a channel bitmap is used to represent the availability or usage of frequency channels within the wireless
    //  spectrum. Wi-Fi operates in specific frequency bands, such as 2.4 GHz and 5 GHz, which are divided into multiple channels.
    //  The channel bitmap helps manage and optimize the use of these channels to avoid interference and improve network performance.

    // Frequency Bands and Channels:
    // 2.4 GHz Band: Divided into 14 channels (each 20 MHz wide), but only channels 1, 6, and 11 are non-overlapping in most regions.
    // 5 GHz Band: Offers more channels (e.g., 25 non-overlapping 20 MHz channels in the U.S.), providing greater flexibility and less
    // interference.

    // when scanning with a channel bitmap, the Wi-Fi device (e.g., an Access Point or client device) can be configured to scan
    // specific channels rather than scanning all available channels in the frequency band.

#else
    esp_wifi_scan_start(NULL, true);

    // This is the first parameter, which is of type wifi_scan_config_t *. It is a pointer to a structure that contains configuration
    // settings for the Wi-Fi scan.
    // NULL means no custom configuration is provided for the scan. So, by passing NULL, the function will use the default scan settings.

    // The second parameter is a bool (boolean) value, which controls whether the scan should be blocking or non-blocking.
    // true indicates that the scan is blocking, meaning the program will wait for the scan to complete before continuing to the next
    // line of code. The function will not return control to the program until the scan finishes.
    // If false were passed, the scan would be non-blocking, meaning the scan would start in the background, and the program would continue
    // executing other code while the scan is still in progress.

#endif /*USE_CHANNEL_BITMAP*/

    ESP_LOGI(TAG, "Max AP number ap_info can hold = %u", number);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    // is used to retrieve the number of access points (APs) found during a Wi-Fi scan on the ESP32 and check for errors in the process.
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    // is used to retrieve detailed information about the access points (APs) that were found during a Wi-Fi scan and check for any errors in the process.

    ESP_LOGI(TAG, "Total APs scanned = %u, actual AP number ap_info holds = %u", ap_count, number);
    for (int i = 0; i < number; i++)
    {
        ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
        ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
        // RSSI stands for Received Signal Strength Indicator. It is a measurement of the power level that an RF (radio frequency) device
        print_auth_mode(ap_info[i].authmode);
        if (ap_info[i].authmode != WIFI_AUTH_WEP)
        {
            print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);

            // Pairwise cipher → Encrypts unicast traffic (communication between a client and the AP). This uses the PTK.
            // Group cipher → Encrypts multicast or broadcast traffic (communication from the AP to multiple clients). This uses the GTK.
        }
        ESP_LOGI(TAG, "Channel \t\t%d", ap_info[i].primary);
        // This refers to the primary channel that the Access Point (AP) is operating on.
    }
}

```


- ## array_2_channel_bitmap()

```c
#ifdef USE_CHANNEL_BITMAP
static void array_2_channel_bitmap(const uint8_t channel_list[], const uint8_t channel_list_size, wifi_scan_config_t *scan_config)
{
    for (uint8_t i = 0; i < channel_list_size; i++)
    {
        uint8_t channel = channel_list[i];
        scan_config->channel_bitmap.ghz_2_channels |= (1 << channel);

        // The bitwise shift operation (1 << channel) shifts the value 1 by the number of positions specified by channel. This means:
        // If channel is 1, it shifts 1 to 0b10 (binary representation of 2).
        // If channel is 6, it shifts 1 to 0b1000000 (binary representation of 64), and so on.
    }
}
#endif /*USE_CHANNEL_BITMAP*/
```



- ## AP info functions


```c
static void print_auth_mode(int authmode)
{
    switch (authmode)
    {
    case WIFI_AUTH_OPEN:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OPEN");
        break;
    case WIFI_AUTH_OWE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OWE");
        break;
    case WIFI_AUTH_WEP:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WEP");
        break;
    case WIFI_AUTH_WPA_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_PSK");
        break;
    case WIFI_AUTH_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
        break;
    case WIFI_AUTH_ENTERPRISE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_ENTERPRISE");
        break;
    case WIFI_AUTH_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_PSK");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
        break;
    case WIFI_AUTH_WPA3_ENTERPRISE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_ENTERPRISE");
        break;
    case WIFI_AUTH_WPA2_WPA3_ENTERPRISE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_ENTERPRISE");
        break;
    case WIFI_AUTH_WPA3_ENT_192:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_ENT_192");
        break;
    default:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_UNKNOWN");
        break;
    }
}

static void print_cipher_type(int pairwise_cipher, int group_cipher)
{

    // pairwise_cipher :
    // WIFI_CIPHER_TYPE_NONE: No cipher type (no encryption).
    // WIFI_CIPHER_TYPE_WEP40: WEP (Wired Equivalent Privacy) with 40-bit encryption.
    // WIFI_CIPHER_TYPE_WEP104: WEP with 104-bit encryption (older, less secure).
    // WIFI_CIPHER_TYPE_TKIP: TKIP (Temporal Key Integrity Protocol), an older encryption standard.
    // WIFI_CIPHER_TYPE_CCMP: AES-based encryption (used in WPA2).
    // WIFI_CIPHER_TYPE_TKIP_CCMP: Both TKIP and AES encryption used together (WPA2 mixed mode).
    // WIFI_CIPHER_TYPE_AES_CMAC128: AES with 128-bit CMAC (Cipher-based Message Authentication Code).
    // WIFI_CIPHER_TYPE_SMS4: An encryption algorithm used in some Chinese standards (WAPI).
    // WIFI_CIPHER_TYPE_GCMP: Galois/Counter Mode Protocol, another modern encryption method.
    // WIFI_CIPHER_TYPE_GCMP256: A stronger version of GCMP with a 256-bit key used in wpa3.

    switch (pairwise_cipher)
    {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    case WIFI_CIPHER_TYPE_AES_CMAC128:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_AES_CMAC128");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_SMS4");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP256");
        break;
    default:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }

    // group_cipher:
    // WIFI_CIPHER_TYPE_NONE: No encryption used for group communication.
    // WIFI_CIPHER_TYPE_WEP40: WEP with 40-bit encryption (insecure and outdated).
    // WIFI_CIPHER_TYPE_WEP104: WEP with 104-bit encryption (also insecure and outdated).
    // WIFI_CIPHER_TYPE_TKIP: TKIP (Temporal Key Integrity Protocol), an older encryption standard.
    // WIFI_CIPHER_TYPE_CCMP: AES-based encryption (used in WPA2).
    // WIFI_CIPHER_TYPE_TKIP_CCMP: A mix of TKIP and AES (used in WPA2 mixed mode).
    // WIFI_CIPHER_TYPE_SMS4: Encryption algorithm used in some Chinese standards (WAPI).
    // WIFI_CIPHER_TYPE_GCMP: AES-based encryption using Galois/Counter Mode (GCMP), more modern and secure than CCMP.
    // WIFI_CIPHER_TYPE_GCMP256: AES-based encryption using Galois/Counter Mode with a 256-bit key (used in WPA3 for stronger security).

    switch (group_cipher)
    {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_SMS4");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP256");
        break;
    default:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }
}

```

---


# monitoring 

after flashing you can monitor the esp32s3


you will get this output 


```bash
I (3020) scan: Max AP number ap_info can hold = 10
I (3020) scan: Total APs scanned = 5, actual AP number ap_info holds = 5
I (3020) scan: SSID             ali
I (3020) scan: RSSI             -50
I (3020) scan: Authmode         WIFI_AUTH_WPA_WPA2_PSK
I (3020) scan: Pairwise Cipher  WIFI_CIPHER_TYPE_TKIP_CCMP
I (3030) scan: Group Cipher     WIFI_CIPHER_TYPE_TKIP
I (3030) scan: Channel          3
I (3040) scan: SSID             Chris
I (3040) scan: RSSI             -51
I (3050) scan: Pairwise Cipher  WIFI_CIPHER_TYPE_TKIP_CCMP
I (3050) scan: Group Cipher     WIFI_CIPHER_TYPE_TKIP
I (3060) scan: Channel          9
I (3060) scan: SSID             AFNAN
I (3060) scan: RSSI             -74
I (3060) scan: Authmode         WIFI_AUTH_WPA_WPA2_PSK
I (3070) scan: Pairwise Cipher  WIFI_CIPHER_TYPE_TKIP_CCMP
I (3070) scan: Group Cipher     WIFI_CIPHER_TYPE_TKIP
I (3080) scan: Channel          11
I (3080) scan: SSID             c6342bb7
I (3080) scan: RSSI             -90
I (3080) scan: Authmode         WIFI_AUTH_WPA2_PSK
I (3090) scan: Pairwise Cipher  WIFI_CIPHER_TYPE_CCMP
I (3090) scan: Group Cipher     WIFI_CIPHER_TYPE_CCMP
I (3100) scan: Channel          1
I (3100) scan: SSID             5BrothersNet@03115539229
I (3100) scan: RSSI             -93
I (3110) scan: Authmode         WIFI_AUTH_WPA_WPA2_PSK
I (3110) scan: Pairwise Cipher  WIFI_CIPHER_TYPE_TKIP_CCMP
I (3120) scan: Group Cipher     WIFI_CIPHER_TYPE_TKIP
I (3120) scan: Channel          11
I (3120) main_task: Returned from app_main()
```

here you can see the scan result done by esp32s3