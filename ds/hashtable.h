#ifndef _CTEST_SHARED_HASHTABLE_H
#define _CTEST_SHARED_HASHTABLE_H

#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common.h"

#define GROW        0.6f
#define SHRINK      0.1f
#define HT_MIN_SIZE 50

enum HASH_FUNCTION { FNV_1A_32, FNV_1A_64 };

uint32_t fnv_hash_1a_32(void *key, int len);
uint64_t fnv_hash_1a_64(void *key, int len);

#endif // _CTEST_SHARED_HASHTABLE_H
