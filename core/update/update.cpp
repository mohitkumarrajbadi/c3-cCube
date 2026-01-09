#include "update.h"
#include <algorithm>

namespace c3 {

    void UpdateEngine::update(
        std::vector<CausalRule>& rules,
        ActionId action,
        float outcome,
        Tick now
    ) const noexcept
    {
        outcome = std::clamp(outcome, -1.0f, 1.0f);

        for (auto& rule : rules)
        {
            if (rule.action == action)
            {
                rule.confidence = std::clamp(
                    rule.confidence + LEARNING_RATE * outcome,
                    -1.0f,
                    1.0f);

                rule.hits++;
                rule.last_seen = now;
                return;
            }
        }

        if (rules.size() < MAX_RULES_PER_CONTEXT)
        {
            CausalRule rule;
            rule.action = action;
            rule.confidence = outcome;
            rule.hits = 1;
            rule.last_seen = now;
            rules.push_back(rule);
        }
    }

}
