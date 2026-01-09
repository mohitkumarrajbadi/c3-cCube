#include "store/store.h"
#include <cassert>

using namespace c3;

int main() {
    MemoryStore store;

    ContextHash ctx1 = 123;
    ContextHash ctx2 = 456;

    assert(store.size() == 0);
    assert(!store.exists(ctx1));

    auto& rules1 = store.get(ctx1);
    assert(store.exists(ctx1));
    assert(store.size() == 1);
    assert(rules1.empty());

    auto& rules2 = store.get(ctx2);
    assert(store.size() == 2);
    assert(rules2.empty());

    rules1.push_back({42, 0.5f, 1, 10});
    assert(store.get(ctx1).size() == 1);
    assert(store.get(ctx2).empty());

    store.clear();
    assert(store.size() == 0);

    return 0;
}
