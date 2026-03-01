# IXWebSocket for ESP-IDF

[![Build Status](https://github.com/YauheniMarchanka/esp-ixwebsocket/actions/workflows/build.yml/badge.svg)](https://github.com/YauheniMarchanka/esp-ixwebsocket/actions)
![License](https://img.shields.io/github/license/YauheniMarchanka/esp-ixwebsocket)
![ESP-IDF Version](https://img.shields.io/badge/ESP--IDF-v5.x-blue)

A specialized port of the [IXWebSocket](https://github.com/machinezone/IXWebSocket) library specifically tailored for the **ESP-IDF v5.x** framework (ESP32 series).

## Overview
This project provides a robust C++ WebSocket client and server for ESP32 chips. It has been modified to handle the specific networking stack (LWIP) and security requirements (MbedTLS 3.x) of the latest Espressif IoT Development Framework.

## Disclaimer
This project is a modified version of the original IXWebSocket library by **Machine Zone, Inc.** All credit for the core logic and architecture goes to the original authors. This port adds the necessary compatibility layers for ESP-IDF integration.

## Key Changes in this Port
- **MbedTLS 3.x Support**: Fixed `mbedtls_pk_parse_keyfile` calls to match the new API requirements (added RNG parameters).
- **POSIX Compatibility**: Added a `compat` layer for missing headers like `netinet/ip.h` and `poll.h`.
- **LWIP Integration**: Replaced `gai_strerror` with ESP-friendly error reporting in `IXDNSLookup.cpp`.
- **Interrupt Mechanism**: Switched from `pipe()` (unsupported in IDF) to `EventFD` via `IXSelectInterruptEvent.cpp`.
- **Linker Fixes**: Explicitly defined `DNSLookup::kDefaultWait` to prevent "undefined reference" errors during linking.

## Installation

### Using Git Submodules (Recommended)
Add this repository to your project's `components` folder:

```bash
mkdir -p components
cd components
git clone [https://github.com/YauheniMarchanka/esp-ixwebsocket.git](https://github.com/YauheniMarchanka/esp-ixwebsocket.git) IXWebSocket
