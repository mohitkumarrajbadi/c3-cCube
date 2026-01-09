#include "../memory/memory.h"
#include <iostream>

using namespace c3;

int main(){
    Memory memory;

    ContextFeatures ctx{
        INTENT_FACTUAL,
        DOMAIN_QA,
        TOOL_SEARCH,
        0
    };

    for (int t = 0; t < 5; ++t){
        memory.update(ctx,42,-1.0f,t);
    }

    Bias b = memory.recall(ctx);

    std::cout << "Avoid actions: ";
    for (auto a: b.avoid) std::cout << a << " ";
    std::cout << "\n";

    return 0;

}
