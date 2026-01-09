#pragma once

#include <cstddef>
#include "../context/context.h"
#include "../store/store.h"
#include "../recall/recall.h"
#include "../update/update.h"
#include "../prune/prune.h"

namespace c3 {

    class Memory {
    public:
        Bias recall(const ContextFeatures& ctx) const noexcept;

        void update(
            const ContextFeatures& ctx,
            ActionId action,
            float outcome,
            Tick now
        ) noexcept;

        size_t num_contexts() const noexcept;
        void clear() noexcept;

    private:
        MemoryStore store_;
        RecallEngine recall_engine_;
        UpdateEngine update_engine_;
        Pruner pruner_;
    };

}
