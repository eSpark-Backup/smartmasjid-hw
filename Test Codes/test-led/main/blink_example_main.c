/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
/* 
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

// static const char *TAG = "example";

//  Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
//    or you can edit the following line and set a number here.

#define BLINK_GPIO 18
#define SW3 26

// static uint8_t s_led_state = 0;


void app_main(void)
{
    gpio_reset_pin(BLINK_GPIO);
    gpio_reset_pin(SW3);
    gpio_set_direction(SW3, GPIO_MODE_INPUT);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    
    while(1){
        if(gpio_get_level(SW3) == 1){
            ESP_LOGI("Blink", "Button Pressed");
            gpio_set_level(BLINK_GPIO, 0);//LED on

        }
        else{
            ESP_LOGI("Blink", "Button Not Pressed");
            gpio_set_level(BLINK_GPIO, 1);//LED off
        }
        vTaskDelay(1);//1 TICK MEANS 10MS
    }
}    
    
    while (1) {
        ESP_LOGI("Blink", "Example configure to blink GPIO LED!");

        gpio_reset_pin(BLINK_GPIO);
        gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
        while(1){
        //  Toggle the LED state 
        ESP_LOGI("Blink", "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        gpio_set_level(BLINK_GPIO, s_led_state);

        s_led_state = !s_led_state;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

}*/


/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/*HAD TO CHANGE NANO SECONDS FOR LED WS2812 IN managed_components\espressif > src > led_strip_rmt_dev_idf4.c*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
// #include <projdefs.h>
// #include <portmacro.h>

// GPIO assignment
#define Button 26
#define LED_STRIP_BLINK_GPIO  25
// Numbers of the LED in the strip
#define LED_STRIP_LED_NUMBERS 25
// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)

static const char *TAG = "example";

led_strip_handle_t configure_led(void)
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_BLINK_GPIO,   // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_LED_NUMBERS,        // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812,            // LED strip model
        .flags.invert_out = false,                // whether to invert the output signal
    };

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
        .rmt_channel = 0,
#else
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .flags.with_dma = false,               // DMA feature is available on ESP target like ESP32-S3
#endif
    };

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    // ESP_LOGI(TAG, "Created LED strip object with RMT backend");
    return led_strip;
}

void app_main(void)
{
    int count = 0;
    gpio_reset_pin(Button);
    gpio_set_direction(Button, GPIO_MODE_INPUT);
    
    
    /*
    int count = 1;
    gpio_reset_pin(Button);
    gpio_set_direction(Button, GPIO_MODE_INPUT);

    bool led_on_off = false;
    led_strip_handle_t led_strip;// = configure_led();

    led_strip_handle_t led_strip = configure_led();
    bool led_on_off = false;

    ESP_LOGI(TAG, "Start blinking LED strip");
while(1){
    
    if(gpio_get_level(Button) == 0){//BUTTON PRESSED

        while(count == 1){
            led_strip = configure_led();
            // bool led_on_off = false;

            ESP_LOGI(TAG, "Start blinking LED strip");
            count=0;
        }
        // while (1) {
            if (led_on_off) {
                //  Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color 
                for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
                    ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, 5, 5, 5));
                }
                //  Refresh the strip to send data 
                ESP_ERROR_CHECK(led_strip_refresh(led_strip));
                // ESP_LOGI(TAG, "LED ON!");
            } else {
                //  Set all LED off to clear all pixels 
                ESP_ERROR_CHECK(led_strip_clear(led_strip));
                // ESP_LOGI(TAG, "LED OFF!");
            }

            led_on_off = !led_on_off;
            vTaskDelay(10 / portTICK_PERIOD_MS);
        // }
    }
    else{//BUTTON NOT PRESSED
        gpio_set_level(Button, 0);
        vTaskDelay(1000);
    }
count = 0;
}
*/
    #if 1
    led_strip_handle_t led_strip = configure_led();
    bool led_on_off = false;

    ESP_LOGI(TAG, "Start blinking LED strip");
    while (1) {
        if(gpio_get_level(Button) == 0)
        {
            count++;  
        }
        // else
        // {
        //     led_on_off = false;
        // }
        if(count % 2 == 1){
            led_on_off = true;
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        if(count % 2 == 0){
            led_on_off = false;
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }


        //////DO NOT TOUCH THIS ANYTHING BELOW THIS LINE *** EXCEPT LED BRIGHTNESS//////
        if (led_on_off) {
            //  Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color 
            for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
                ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, 100, 50, 60));
            }
            //  Refresh the strip to send data 
            ESP_ERROR_CHECK(led_strip_refresh(led_strip));
            // ESP_LOGI(TAG, "LED ON!");
        } 
        else {
            //  Set all LED off to clear all pixels 
            ESP_ERROR_CHECK(led_strip_clear(led_strip));
            // ESP_LOGI(TAG, "LED OFF!");
        }

        led_on_off = !led_on_off;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    #endif
}