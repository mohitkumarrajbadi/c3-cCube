#include "../core/recall/recall.h"
#include <cassert>

using namespace c3;

int main(){
    RecallEngine recall;
    
    std::vector<CausalRule> rules = {
        {1, 0.9f,3,10},   // Positive confidence
        {2, -0.8f,2,11},  // Negative confidence
        {3, 0.1f,1,12}
    };

    Bias bias = recall.recall(rules);

    assert(bias.prefer.size() == 1);
    assert(bias.prefer[0] == 1);

    assert(bias.avoid.size() == 1);
    assert(bias.avoid[0] == 2);

    return 0;
}