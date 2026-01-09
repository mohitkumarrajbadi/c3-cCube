#include "../core/memory/memory.h"
#include <cassert>

using namespace c3;

int main()
{
    Memory mem;

    ContextFeatures ctx{
        INTENT_FACTUAL,
        DOMAIN_QA,
        TOOL_SEARCH,
        0};

    Bias b0 = mem.recall(ctx);
    assert(b0.prefer.empty());
    assert(b0.avoid.empty());

    mem.update(ctx, 1, -1.0f, 1);

    Bias b1 = mem.recall(ctx);
    assert(b1.avoid.size() == 1);
    assert(b1.avoid[0] == 1);

    mem.update(ctx, 2, +1.0f, 2);

    Bias b2 = mem.recall(ctx);
    assert(b2.prefer.size() == 1);
    assert(b2.prefer[0] == 2);

    ContextFeatures other{
        INTENT_FACTUAL,
        DOMAIN_QA,
        TOOL_SEARCH,
        1};

    Bias b3 = mem.recall(other);
    assert(b3.prefer.empty());
    assert(b3.avoid.empty());

    return 0;
}
