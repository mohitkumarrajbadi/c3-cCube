# C³ — Causal Experience Memory

C³ is a lightweight, deterministic **memory layer for AI systems** that stores and recalls  
**causal experience (context → action → outcome)** so systems stop repeating the same mistakes  
over time — **without retraining models**.

C³ is **not**:
- RAG
- prompt engineering
- a vector database
- reinforcement learning

It is a **systems primitive** for agentic and GenAI systems.

---

## Why C³ Exists

Modern AI systems:
- repeat the same failures across retries
- do not improve across interactions
- confuse retrieval with memory

Humans remember *what didn’t work* and avoid it.  
C³ brings this capability to AI systems in a **deterministic, low-overhead way**.

This is a **system design problem**, not a model problem.

---

## What C³ Does (In One Line)

C³ allows AI systems to learn from outcomes and bias future decisions  
**without changing the model**.

---

## Project Status

- ✅ C++ core implemented
- ✅ Deterministic unit tests passing
- ✅ Benchmarks demonstrating failure suppression
- ⚠️ Python / JS bindings in progress
- ⚠️ Persistence & concurrency planned

---

## Repository Structure

```
c3-cCube/
├── core/ # C++ core engine
├── bindings/ # Language bindings (Python WIP)
├── paper/ # Research draft
├── README.md
├── ARCHITECTURE.md
├── LICENSE
└── CONTRIBUTING.md
```

---

## Quick Start (C++)

### Build & Run a Benchmark

From the repository root:

```bash
cd core
g++ -std=c++17 -O2 \
  context/context.cpp \
  store/store.cpp \
  recall/recall.cpp \
  update/update.cpp \
  prune/prune.cpp \
  memory/memory.cpp \
  bench/benchmark_repeated_failure.cpp \
  -o benchmark
```

Run:

```bash
./benchmark
```

You should observe stateless retries growing linearly, while C³ suppresses repeated failures.

### Example Usage (C++)

```cpp
#include "memory/memory.h"

using namespace c3;

Memory mem;

ContextFeatures ctx{
    INTENT_FACTUAL,
    DOMAIN_QA,
    TOOL_SEARCH,
    0
};

// Record a failed action
mem.update(ctx, 42, -1.0f, 1);

// Recall bias
Bias b = mem.recall(ctx);
// b.avoid now contains action 42
```

---

## Benchmarks

### Repeated Failure Suppression

A stateless agent retries the same failing action indefinitely.

C³:

- records the failure once
- suppresses retries thereafter

Example result:

```
Stateless failures: 50
C³ failures:        1
```

Benchmarks live in:

```bash
core/bench/
```

---

## Contributing

Contributions are welcome.

We are especially interested in:

- C++ systems optimization
- Python / JavaScript bindings
- Agent & GenAI benchmarks
- Design critique and edge cases

See CONTRIBUTING.md for details.