#include "context.h"

namespace c3 {

    ContextHash ContextEncoder::encode(const ContextFeatures &ctx) {

        /* Packing the context into a 32-bit integer */
        uint32_t packed = 0;

        packed |= uint32_t(ctx.intent);
        packed |= uint32_t(ctx.domain) << 8;
        packed |= uint32_t(ctx.tool) << 16;
        packed |= uint32_t(ctx.retry) << 24;

        /* Hash Mixing (Mix int 64-bit hash) inspired by MurmurHash */
        uint64_t hash = packed;
        hash ^= hash >> 33;
        hash *= 0xff51afd7ed558ccdULL;
        hash ^= hash >> 33;

        return hash;
    }

}