#include "../core/update/update.h"
#include <cassert>

using namespace c3;

int main() {
    UpdateEngine update;
    std::vector<CausalRule> rules;

    // Insert new rule (confidence = outcome)
    update.update(rules, 42, +1.0f, 1);
    assert(rules.size() == 1);
    assert(rules[0].confidence == 1.0f);

    // Reinforce same rule (confidence stays clamped)
    float before = rules[0].confidence;
    update.update(rules, 42, +1.0f, 2);
    assert(rules[0].confidence == before);
    assert(rules[0].hits == 2);

    // Negative update reduces confidence
    update.update(rules, 42, -1.0f, 3);
    assert(rules[0].confidence < before);

    return 0;
}
