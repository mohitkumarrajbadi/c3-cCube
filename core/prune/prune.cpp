#include "prune.h"
#include <algorithm>
#include <cmath>

namespace c3 {

    void Pruner::prune(
        std::vector<CausalRule>& rules,
        Tick now
    ) const noexcept
    {
        rules.erase(
            std::remove_if(
                rules.begin(),
                rules.end(),
                [&](const CausalRule& r)
                {
                    bool stale =
                        (now > r.last_seen) &&
                        ((now - r.last_seen) > MAX_AGE);

                    bool weak =
                        std::fabs(r.confidence) < MIN_CONFIDENCE;

                    return stale || weak;
                }),
            rules.end());
    }

}
