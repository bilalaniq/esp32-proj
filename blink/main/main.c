#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

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
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &Led_strip));

#elif CONFIG_BLINK_LED_STRIP_BACKEND_SPI

    led_strip_spi_config_t spi_config =
        {
            .spi_bus = SPI1_HOST,
            .flags.with_dma = false,
        };

    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &Led_strip));

#else
#error "unsupported LED backend"
#endif
}

static uint8_t select_col_Ran(void)
{
    // Generate a random number between 0 and 9
    return rand() % 10; // rand() % 10 gives values from 0 to 9
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

#elif CONFIG_BLINK_LED_GPIO

static void configure_led(void)
{
    ESP_LOGI(TAG, "configuring to blink GPIO LED");
    gpio_reset_pin(BLINK_GPIO_pin);
    gpio_set_direction(BLINK_GPIO_pin, GPIO_MODE_OUTPUT);
}

static void blink_led(void)
{
    gpio_set_level(BLINK_GPIO_pin, Led_State);
}

#else
#error "unsupported LED type"
#endif

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