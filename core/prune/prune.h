#pragma once

#include <vector>
#include <cstddef>
#include "../store/store.h"

namespace c3 {

    static constexpr Tick MAX_AGE = 10'000;
    static constexpr float MIN_CONFIDENCE = 0.1f;

    class Pruner {
    public:
        void prune(
            std::vector<CausalRule>& rules,
            Tick now
        ) const noexcept;
    };

}
