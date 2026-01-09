#pragma once

#include <vector>
#include <cstddef>
#include "../store/store.h"

namespace c3 {

    static constexpr float LEARNING_RATE = 0.1f;
    static constexpr size_t MAX_RULES_PER_CONTEXT = 8;

    class UpdateEngine {
    public:
        void update(
            std::vector<CausalRule>& rules,
            ActionId action,
            float outcome,
            Tick now
        ) const noexcept;
    };

}
