idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "inc"
                       REQUIRES freertos esp_common driver esp_wifi nvs_flash)
