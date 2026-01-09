#include "context/context.h"
#include <cassert>

using namespace c3;

int main() {
    ContextFeatures a {INTENT_FACTUAL, DOMAIN_QA, TOOL_SEARCH, 0};
    ContextFeatures b {INTENT_FACTUAL, DOMAIN_QA, TOOL_SEARCH, 0};

    // Different intent
    ContextFeatures c {INTENT_DEBUGGING, DOMAIN_QA, TOOL_SEARCH, 0};

    // Different domain
    ContextFeatures d {INTENT_FACTUAL, DOMAIN_CODE, TOOL_SEARCH, 0};

    // Different tool
    ContextFeatures e {INTENT_FACTUAL, DOMAIN_QA, TOOL_RAG, 0};

    // Different retry bucket
    ContextFeatures f {INTENT_FACTUAL, DOMAIN_QA, TOOL_SEARCH, 1};

    // Same inputs → same hash
    assert(ContextEncoder::encode(a) == ContextEncoder::encode(b));

    // One semantic difference → different hash
    assert(ContextEncoder::encode(a) != ContextEncoder::encode(c));
    assert(ContextEncoder::encode(a) != ContextEncoder::encode(d));
    assert(ContextEncoder::encode(a) != ContextEncoder::encode(e));
    assert(ContextEncoder::encode(a) != ContextEncoder::encode(f));

    return 0;
}
