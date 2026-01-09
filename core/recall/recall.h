#pragma once

#include <vector>
#include <cstddef>
#include "../store/store.h"

namespace c3 {

    static constexpr float POS_THRESHOLD = 0.5f;
    static constexpr float NEG_THRESHOLD = -0.5f;

    struct Bias {
        std::vector<ActionId> prefer{};
        std::vector<ActionId> avoid{};
    };

    class RecallEngine {
    public:
        Bias recall(const std::vector<CausalRule>& rules) const noexcept;
    };

}
