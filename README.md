# C³ — Causal Experience Memory

C³ is a lightweight, deterministic **memory layer for AI systems** that stores and recalls
**causal experience (context → action → outcome)** so systems stop repeating the same mistakes
over time — **without retraining models**.

C³ is not:
- RAG
- prompt engineering
- a vector database
- reinforcement learning

It is a missing systems primitive for agentic and GenAI systems.

---

## Why C³ exists

Modern AI systems:
- repeat the same failures
- do not improve across interactions
- confuse retrieval with memory

Humans remember *what didn’t work* and avoid it.
C³ brings that capability to AI systems.

---

## Core idea

C³ stores **compressed causal rules**, not raw data:

(Context) → (Action) → (Outcome, Confidence)

At runtime, C³:
- recalls relevant past outcomes
- biases decisions (avoid / prefer)
- runs in O(1) time with bounded memory

---

## Project status

- ✅ C++ core implemented
- ✅ Deterministic benchmarks passing
- ⚠️ Language bindings (Python / JS) in progress
- ⚠️ Persistence & concurrency planned

---

## Build (C++ core)

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
