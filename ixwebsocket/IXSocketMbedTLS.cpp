#include "IXSocketMbedTLS.h"
#include <algorithm>
#include <string.h>

/* MbedTLS headers for networking and versioning */
#include <mbedtls/net_sockets.h>
#include <mbedtls/version.h>

namespace ix
{
    SocketMbedTLS::SocketMbedTLS(const SocketTLSOptions& tlsOptions, int fd)
        : Socket(fd)
        , _tlsOptions(tlsOptions)
    {
        mbedtls_ssl_init(&_ssl);
        mbedtls_ssl_config_init(&_conf);
        mbedtls_ctr_drbg_init(&_ctr_drbg);
        mbedtls_entropy_init(&_entropy);
        mbedtls_x509_crt_init(&_cacert);
        mbedtls_x509_crt_init(&_cert);
        mbedtls_pk_init(&_pkey);
    }

    SocketMbedTLS::~SocketMbedTLS()
    {
        mbedtls_x509_crt_free(&_cacert);
        mbedtls_x509_crt_free(&_cert);
        mbedtls_pk_free(&_pkey);
        mbedtls_ssl_free(&_ssl);
        mbedtls_ssl_config_free(&_conf);
        mbedtls_ctr_drbg_free(&_ctr_drbg);
        mbedtls_entropy_free(&_entropy);
    }

    bool SocketMbedTLS::init(const std::string& host, bool isServer, std::string& errorMsg)
    {
        int ret;

        if ((ret = mbedtls_ctr_drbg_seed(&_ctr_drbg, mbedtls_entropy_func, &_entropy, nullptr, 0)) != 0)
        {
            errorMsg = "mbedtls_ctr_drbg_seed failed";
            return false;
        }

        if ((ret = mbedtls_ssl_config_defaults(&_conf,
                                               isServer ? MBEDTLS_SSL_IS_SERVER : MBEDTLS_SSL_IS_CLIENT,
                                               MBEDTLS_SSL_TRANSPORT_STREAM,
                                               MBEDTLS_SSL_PRESET_DEFAULT)) != 0)
        {
            errorMsg = "mbedtls_ssl_config_defaults failed";
            return false;
        }

        /* Set authentication mode based on provided options */
        mbedtls_ssl_conf_authmode(&_conf, MBEDTLS_SSL_VERIFY_NONE);
        mbedtls_ssl_conf_rng(&_conf, mbedtls_ctr_drbg_random, &_ctr_drbg);

        if (!_tlsOptions.caFile.empty())
        {
            if (mbedtls_x509_crt_parse_file(&_cacert, _tlsOptions.caFile.c_str()) != 0)
            {
                errorMsg = "mbedtls_x509_crt_parse_file failed for CA";
                return false;
            }
            mbedtls_ssl_conf_ca_chain(&_conf, &_cacert, nullptr);
            mbedtls_ssl_conf_authmode(&_conf, MBEDTLS_SSL_VERIFY_REQUIRED);
        }

        if (!_tlsOptions.certFile.empty())
        {
            if (mbedtls_x509_crt_parse_file(&_cert, _tlsOptions.certFile.c_str()) != 0)
            {
                errorMsg = "mbedtls_x509_crt_parse_file failed for certificate";
                return false;
            }
        }

        if (!_tlsOptions.keyFile.empty())
        {
            /* API Change in MbedTLS 3.x: added RNG parameters */
#if MBEDTLS_VERSION_NUMBER >= 0x03000000
            if (mbedtls_pk_parse_keyfile(&_pkey, _tlsOptions.keyFile.c_str(), "", mbedtls_ctr_drbg_random, &_ctr_drbg) != 0)
#else
            if (mbedtls_pk_parse_keyfile(&_pkey, _tlsOptions.keyFile.c_str(), "") != 0)
#endif
            {
                errorMsg = "mbedtls_pk_parse_keyfile failed";
                return false;
            }
        }

        if (!_tlsOptions.certFile.empty() && !_tlsOptions.keyFile.empty())
        {
            if (mbedtls_ssl_conf_own_cert(&_conf, &_cert, &_pkey) != 0)
            {
                errorMsg = "mbedtls_ssl_conf_own_cert failed";
                return false;
            }
        }

        if ((ret = mbedtls_ssl_setup(&_ssl, &_conf)) != 0)
        {
            errorMsg = "mbedtls_ssl_setup failed";
            return false;
        }

        if (!isServer)
        {
            mbedtls_ssl_set_hostname(&_ssl, host.c_str());
        }

        /* Use the socket descriptor from the base class */
        mbedtls_ssl_set_bio(&_ssl, (void*) (intptr_t) _sockfd, mbedtls_net_send, mbedtls_net_recv, nullptr);

        return true;
    }
    
    /* ... rest of the methods (accept, connect, close, send, recv) ... */
    /* Ensure they use mbedtls_ssl_write and mbedtls_ssl_read with correct casting */

} // namespace ix
