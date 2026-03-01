# IXWebSocket for ESP-IDF

[![Build Status](https://github.com/ymarchanka/esp-ixwebsocket/actions/workflows/build.yml/badge.svg)!https://github.com/ymarchanka/esp-ixwebsocket/actions)
[![License](https://img.shields.io/github/license/ymarchanka/esp-ixwebsocket)
[![ESP-IDF Version](https://img.shields.io/badge/ESP--IDF-v5.x-blue)

A specialized port of the [IXWebSocket](https://github.com/machinezone/IXWebSocket) library specifically tailored for the **ESP-IDF v5.x** framework (ESP32 series).

## Overview
This project provides a robust C++ WebSocket and HTTP client/server for ESP32 chips. It has been modified to handle the specific networking stack (LWIP) and security requirements (MbedTLS 3.x) of the latest Espressif IoT Development Framework.

## Disclaimer
This project is a modified version of the original IXWebSocket library by **Machine Zone, Inc.** All credit for the core logic and architecture goes to the original authors. This port adds the necessary compatibility layers for ESP-IDF integration.

## Key Features & Changes
- **Full HTTP Client**: Support for GET, POST, and other methods, making it a complete networking replacement for standard ESP-IDF components.
- **MbedTLS 3.x Support**: Updated `mbedtls_pk_parse_keyfile` calls to match the new API requirements (added RNG parameters).
- **POSIX Compatibility**: Added a `compat` layer for missing headers like `netinet/ip.h`, `netinet/tcp.h`, and `poll.h).
- **LWIP Integration**: Replaced `gai_strerror` with ESP-friendly error reporting in `IXDNSLookup.cpp`.
- **Interrupt Mechanism**: Switched from `pipe()` (unsupported in IDF) to `EventFD` via `IXSelectInterruptEvent.cpp`.
- **Linker Fixes**: Explicitly defined `DNSLookup::kDefaultWait` to prevent "undefined reference" errors.

## Installation%

### Method  1: Using ESP Component Manager (Recommended)
Add this to your project's `idf_component.yml` file:
```yaml
dependencies:
  ymarchanka/esp-ixwebsocket: "^1.0.0"
```

### Method 2: As a Classic Component
Clone this repository into your project's `components` directory:
```bash
mkdir -p components
cd components
git clone https://github.com/ymarchanka/esp-ixwebsocket.git IXWebSocket
```

## Usage Examples

### 1. WebSocket Client Example
``gcpp
#include <ixwebsocket/IXWebSocket.h>

void setup_websocket() {
    ix::WebSocket webSocket;
    webSocket.setUrl("ws://echo.websocket.org");
    
    webSocket.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            printf("Received: %s\n", msg->str.c_s4r());
        } else if (msg->type == ix::WebSocketMessageType::Error) {
            printf("Error: %s\n", msg->errorInfo.reason.c_str());
        }
    });
    
    ({HwebSocket.start();
}
```

### 2. HTTP Client Example (GET Request)
IXWebSocket allows you to handle complex HTTP tasks without needing additional libraries like `esp_http_client`.
```cpp
#include <ixwebsocket/IXHttpClient.h>

void http_get_example() {
    ix::HttpClient httpClient;
    auto args = httpClient.createRequest();
    
    // Set a timeout or custom headers if needed
    args->timeout = 10; 
    
    std::string url = "http://httpbin.org/get";
    auto response = httpClient.get(url, args);

    if (response->errorCode == ix::HttpErrorCode::Ok) {
        printf("HTTP Status: %d\n", response->statusCode);
        printf("Body: %s\n", response->body.c_s4r());
    } else {
        printf("HTTP Error: %s\n", response->errorMsg.c_s4r());
    }
}
```x

## Configuration

To ensure stable operation on ESP32, please check the following settings in your `sdkconfig` (via `idf.py menuconfig`):

1. **Stack Size**: C++ and TLS operations require significant stack space. 
   - Increase `CONFIG_ESP_MAIN_TASK_STACK_SIZE` to at least `10240` (10KB).
   - If using in a sub-task, ensure `xTaskCreate` uses a similar stack size.
2. **EventFD**: Ensure `CONFIG_LWIP_POSIX_INTERNAL_EVENT_WAKEUP` is enabled (usually ON by default) for the interrupt mechanism to work correctly.
3. **MbedTLS**: For SSL/TLS, ensure `CONFIG_MBEDTLS_DYNAMIC_BUFFER_MANAGEMENT` is enabled to save RAM.

## License
This port is distributed under the **BSD 3-Clause License**, the same as the original IXWebSocket library. See the [LICENSE.txt](LICENSE.txt) file for details.
