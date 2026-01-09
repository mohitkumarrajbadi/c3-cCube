#include "../core/prune/prune.h"
#include <cassert>

using namespace c3;

int main() {
    Pruner pruner;
    std::vector<CausalRule> rules;

    rules.push_back({1, 0.8f, 3, 100});

    rules.push_back({2, 0.01f, 1, 100});

    rules.push_back({3, -0.9f, 5, 0});

    pruner.prune(rules, 200);

    assert(rules.size() == 2);

    bool has1 = false, has3 = false;
    for (const auto& r : rules) {
        if (r.action == 1) has1 = true;
        if (r.action == 3) has3 = true;
    }

    assert(has1);
    assert(has3);

    return 0;
}
