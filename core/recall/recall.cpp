#include "recall.h"

namespace c3 {

    Bias RecallEngine::recall(const std::vector<CausalRule>& rules) const noexcept
    {
        Bias bias;

        for (const auto& rule : rules)
        {
            if (rule.confidence >= POS_THRESHOLD)
            {
                bias.prefer.push_back(rule.action);
            }
            else if (rule.confidence <= NEG_THRESHOLD)
            {
                bias.avoid.push_back(rule.action);
            }
        }

        return bias;
    }

}
