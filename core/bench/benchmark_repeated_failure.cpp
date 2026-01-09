#include "../memory/memory.h"
#include <iostream>
#include <iomanip>

using namespace c3;

/*
  Benchmark: Repeated Failure Suppression

  Environment:
  - Action 1 always fails
  - Action 2 always succeeds

  Policy:
  - Stateless: always chooses action 1
  - C³: chooses action 1 unless memory says avoid
*/

int main()
{
    constexpr int TIMESTEPS = 50;

    Memory memory;

    ContextFeatures ctx;
    ctx.intent = INTENT_FACTUAL;
    ctx.domain = DOMAIN_QA;
    ctx.tool   = TOOL_SEARCH;
    ctx.retry  = 0;

    int failures_stateless = 0;
    int failures_c3 = 0;

    // CSV header (paper-friendly)
    std::cout << "t,stateless_failures,c3_failures\n";

    for (int t = 1; t <= TIMESTEPS; ++t)
    {
        /* ---------- Stateless agent ---------- */
        {
            int action = 1;        // always bad
            float outcome = -1.0f;
            failures_stateless++;
        }

        /* ---------- C³-enabled agent ---------- */
        {
            Bias bias = memory.recall(ctx);

            int action = 1; // default bad action

            // Respect causal memory
            for (auto a : bias.avoid)
            {
                if (a == 1)
                {
                    action = 2;
                    break;
                }
            }

            float outcome;
            if (action == 1)
            {
                outcome = -1.0f;
                failures_c3++;
            }
            else
            {
                outcome = +1.0f;
            }

            memory.update(ctx, action, outcome, t);
        }

        // Emit metrics
        std::cout << t << ","
                  << failures_stateless << ","
                  << failures_c3 << "\n";
    }

    // Final summary (human-readable)
    std::cout << "\n# Final Summary\n";
    std::cout << "# Stateless failures: " << failures_stateless << "\n";
    std::cout << "# C3 failures:        " << failures_c3 << "\n";

    return 0;
}
