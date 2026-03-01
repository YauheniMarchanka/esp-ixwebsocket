#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

// IXWebSocket library headers
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXHttpClient.h>

static const char *TAG = "IXWS_EXAMPLE";

extern "C" void app_main(void)
{
    // 1. Initialize NVS (Required for the Wi-Fi stack and networking)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Starting IXWebSocket Example...");

    // 2. Initialize WebSocket object
    // This verifies the core library linking and EventFD functionality
    ix::WebSocket webSocket;
    webSocket.setUrl("ws://echo.websocket.org");

    // 3. Initialize HTTP Client object
    // This verifies the HTTP module linking and MbedTLS integration
    ix::HttpClient httpClient;
    auto args = httpClient.createRequest();
    
    ESP_LOGI(TAG, "IXWebSocket objects initialized successfully!");

    /* Note: In a production application, you would set up Wi-Fi connection here.
       For CI/CD build verification purposes, initializing these objects is sufficient 
       to ensure all symbols are correctly linked and the component is functional.
    */

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

