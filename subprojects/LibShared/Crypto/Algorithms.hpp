#ifndef SHARED_CRYPTO_ALGORITHMS_H
#define SHARED_CRYPTO_ALGORITHMS_H 1

#ifdef __cplusplus
extern "C" {
#endif

#define CBC 1
#define ECB 1
#define CTR 1

#include "aes.h"
#include "hmac_sha256.h"
#include "sha1.h"
#include "sha256.h"
#include "md5.h"

#ifdef __cplusplus
}
#endif

#endif