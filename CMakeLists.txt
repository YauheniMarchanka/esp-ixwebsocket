# ==============================================================================
# IXWebSocket Component Configuration
# ==============================================================================

# List of source files
set(ixwebsocket_sources
    "ixwebsocket/IXBench.cpp"
    "ixwebsocket/IXCancellationRequest.cpp"
    "ixwebsocket/IXConnectionState.cpp"
    "ixwebsocket/IXDNSLookup.cpp"
    "ixwebsocket/IXExponentialBackoff.cpp"
    "ixwebsocket/IXGetFreePort.cpp"
    "ixwebsocket/IXGzipCodec.cpp"
    "ixwebsocket/IXHttp.cpp"
    "ixwebsocket/IXHttpClient.cpp"
    "ixwebsocket/IXHttpServer.cpp"
    "ixwebsocket/IXNetSystem.cpp"
    "ixwebsocket/IXSelectInterrupt.cpp"
    "ixwebsocket/IXSelectInterruptEvent.cpp"
    "ixwebsocket/IXSelectInterruptFactory.cpp"
    "ixwebsocket/IXSetThreadName.cpp"
    "ixwebsocket/IXSocket.cpp"
    "ixwebsocket/IXSocketAppleSSL.cpp"
    "ixwebsocket/IXSocketConnect.cpp"
    "ixwebsocket/IXSocketFactory.cpp"
    "ixwebsocket/IXSocketMbedTLS.cpp"
    "ixwebsocket/IXSocketOpenSSL.cpp"
    "ixwebsocket/IXSocketServer.cpp"
    "ixwebsocket/IXSocketTLSOptions.cpp"
    "ixwebsocket/IXStrCaseCompare.cpp"
    "ixwebsocket/IXUdpSocket.cpp"
    "ixwebsocket/IXUrlParser.cpp"
    "ixwebsocket/IXUserAgent.cpp"
    "ixwebsocket/IXUuid.cpp"
    "ixwebsocket/IXWebSocketCloseConstants.cpp"
    "ixwebsocket/IXWebSocket.cpp"
    "ixwebsocket/IXWebSocketHandshake.cpp"
    "ixwebsocket/IXWebSocketHttpHeaders.cpp"
    "ixwebsocket/IXWebSocketPerMessageDeflateCodec.cpp"
    "ixwebsocket/IXWebSocketPerMessageDeflate.cpp"
    "ixwebsocket/IXWebSocketPerMessageDeflateOptions.cpp"
    "ixwebsocket/IXWebSocketProxyServer.cpp"
    "ixwebsocket/IXWebSocketServer.cpp"
    "ixwebsocket/IXWebSocketTransport.cpp"
)

# --- Component Registration ---------------------------------------------------

# REQUIRES mbedtls and esp-tls are mandatory for SSL functionality in IDF v5
idf_component_register(
    SRCS "${ixwebsocket_sources}"
    INCLUDE_DIRS "." "compat"
    REQUIRES mbedtls esp-tls
    PRIV_REQUIRES lwip esp_event
)

# --- MbedTLS Header Path Fix --------------------------------------------------

# This is a workaround for ESP-IDF v5.x where internal mbedtls headers 
# (like ctr_drbg.h) are not automatically added to the include path.
idf_component_get_property(mbedtls_lib mbedtls COMPONENT_LIB)
target_include_directories(${COMPONENT_LIB} PRIVATE 
    $<TARGET_PROPERTY:${mbedtls_lib},INTERFACE_INCLUDE_DIRECTORIES>
)

# --- Compiler Definitions -----------------------------------------------------

target_compile_definitions(${COMPONENT_LIB} PUBLIC 
    IXWEBSOCKET_USE_MBED_TLS
    # Marks the build environment as ESP32 (LWIP/non-POSIX specific)
    IXWEBSOCKET_USE_ESP32 
)
