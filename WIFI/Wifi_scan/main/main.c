#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "regex.h"

#define DEFAULT_SCAN_LIST_SIZE CONFIG_SCAN_LIST_SIZE

#ifdef CONFIG_SCAN_CHANNEL_BITMAP
#define USE_CHANNEL_BITMAP 1
#define CHANNEL_LIST_SIZE 3
static uint8_t channel_list[CHANNEL_LIST_SIZE] = {1, 6, 11};
#endif

static const char *TAG = "scan";

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