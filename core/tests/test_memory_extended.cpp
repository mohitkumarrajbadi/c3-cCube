#include "../core/memory/memory.h"
#include <cassert>

using namespace c3;

void test_determinism()
{
    c3::Memory mem;

    c3::ContextFeatures ctx{
        c3::INTENT_FACTUAL,
        c3::DOMAIN_QA,
        c3::TOOL_SEARCH,
        0};

    mem.update(ctx, 10, +1.0f, 1);

    auto b1 = mem.recall(ctx);
    auto b2 = mem.recall(ctx);

    assert(b1.prefer == b2.prefer);
    assert(b1.avoid == b2.avoid);
}

void test_repeated_failure()
{
    c3::Memory mem;

    c3::ContextFeatures ctx{
        c3::INTENT_FACTUAL,
        c3::DOMAIN_SEARCH,
        c3::TOOL_RAG,
        0};

    // Repeated failures
    for (int i = 0; i < 3; ++i)
    {
        mem.update(ctx, 42, -1.0f, i);
    }

    auto bias = mem.recall(ctx);

    assert(bias.avoid.size() == 1);
    assert(bias.avoid[0] == 42);
}

void test_competing_actions()
{
    c3::Memory mem;

    c3::ContextFeatures ctx{
        c3::INTENT_INSTRUCTIONAL,
        c3::DOMAIN_AGENT,
        c3::TOOL_API,
        0};

    mem.update(ctx, 1, -1.0f, 1); // bad action
    mem.update(ctx, 2, +1.0f, 2); // good action

    auto bias = mem.recall(ctx);

    assert(bias.avoid.size() == 1);
    assert(bias.prefer.size() == 1);

    assert(bias.avoid[0] == 1);
    assert(bias.prefer[0] == 2);
}

void test_context_isolation()
{
    c3::Memory mem;

    c3::ContextFeatures ctx1{
        c3::INTENT_FACTUAL,
        c3::DOMAIN_QA,
        c3::TOOL_SEARCH,
        0};

    c3::ContextFeatures ctx2{
        c3::INTENT_FACTUAL,
        c3::DOMAIN_QA,
        c3::TOOL_SEARCH,
        1 // different retry bucket
    };

    mem.update(ctx1, 7, -1.0f, 1);

    auto b1 = mem.recall(ctx1);
    auto b2 = mem.recall(ctx2);

    assert(!b1.avoid.empty());
    assert(b2.avoid.empty());
}

void test_pruning_effect()
{
    c3::Memory mem;

    c3::ContextFeatures ctx{
        c3::INTENT_DEBUGGING,
        c3::DOMAIN_CODE,
        c3::TOOL_CODE_EXEC,
        0};

    // Old failure
    mem.update(ctx, 99, -1.0f, 1);

    // Advance time far beyond MAX_AGE
    mem.update(ctx, 100, +1.0f, 20000);

    auto bias = mem.recall(ctx);

    // Old failure should be pruned
    assert(bias.avoid.empty());
    assert(bias.prefer.size() == 1);
}

void test_clear()
{
    c3::Memory mem;

    c3::ContextFeatures ctx{
        c3::INTENT_FACTUAL,
        c3::DOMAIN_QA,
        c3::TOOL_SEARCH,
        0};

    mem.update(ctx, 1, +1.0f, 1);
    assert(mem.num_contexts() == 1);

    mem.clear();
    assert(mem.num_contexts() == 0);

    auto bias = mem.recall(ctx);
    assert(bias.prefer.empty());
}

int main()
{
    test_determinism();
    test_repeated_failure();
    test_competing_actions();
    test_context_isolation();
    test_pruning_effect();
    test_clear();

    return 0;
}
