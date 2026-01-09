#pragma once

#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "../context/context.h"

namespace c3 {

    using ActionId = uint32_t;
    using Tick = uint32_t;

    struct CausalRule {
        ActionId action = 0;
        float confidence = 0.0f;
        uint32_t hits = 0;
        Tick last_seen = 0;
    };

    class MemoryStore {
    public:
        // Mutating access (used by update path)
        std::vector<CausalRule>& get(ContextHash context);

        // Read-only access (used by recall path)
        const std::vector<CausalRule>& get(ContextHash context) const;

        bool exists(ContextHash context) const;
        size_t size() const;
        void clear();

    private:
        std::unordered_map<ContextHash, std::vector<CausalRule>> data_;
    };

}
