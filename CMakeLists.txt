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

# Добавляем папку compat в пути поиска заголовочных файлов
idf_component_register(SRCS ${ixwebsocket_sources}
                       INCLUDE_DIRS "." "compat"
                       PRIV_INCLUDE_DIRS "ixwebsocket"
                       REQUIRES mbedtls
                       PRIV_REQUIRES lwip esp_event)

# Флаги для корректной работы IXWebSocket на ESP32
target_compile_definitions(${COMPONENT_LIB} PUBLIC 
    IXWEBSOCKET_USE_MBED_TLS
    # Этот флаг часто помогает библиотеке понять, что мы в среде без полного POSIX
    IXWEBSOCKET_USE_ESP32 
)
