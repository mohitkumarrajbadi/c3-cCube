#include "memory.h"

namespace c3 {

    Bias Memory::recall(const ContextFeatures& ctx) const noexcept
    {
        ContextHash hash = ContextEncoder::encode(ctx);

        if (!store_.exists(hash))
        {
            return Bias{};
        }

        const auto& rules = store_.get(hash);
        return recall_engine_.recall(rules);
    }

    void Memory::update(
        const ContextFeatures& ctx,
        ActionId action,
        float outcome,
        Tick now
    ) noexcept
    {
        ContextHash hash = ContextEncoder::encode(ctx);

        auto& rules = store_.get(hash);
        update_engine_.update(rules, action, outcome, now);
        pruner_.prune(rules, now);
    }

    size_t Memory::num_contexts() const noexcept
    {
        return store_.size();
    }

    void Memory::clear() noexcept
    {
        store_.clear();
    }

}
