# List of source files for the IXWebSocket library
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

# Register the component
# We use "." to allow #include <ixwebsocket/IXWebSocket.h>
# We include "compat" for our POSIX fixes
# We use REQUIRES (public) for mbedtls and esp_tls because your headers 
# include their files, and any project using your library needs them too.
idf_component_register(SRCS ${ixwebsocket_sources}
                       INCLUDE_DIRS "." "compat"
                       REQUIRES mbedtls esp_tls
                       PRIV_REQUIRES lwip esp_event)

# Configuration flags for ESP32 environment
target_compile_definitions(${COMPONENT_LIB} PUBLIC 
    IXWEBSOCKET_USE_MBED_TLS
    IXWEBSOCKET_USE_ESP32 
)

# Explicitly add the include directory to the target to ensure the example sees it
target_include_directories(${COMPONENT_LIB} INTERFACE ".")
