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