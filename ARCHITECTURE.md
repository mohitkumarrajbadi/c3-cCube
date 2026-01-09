# C³ Architecture — Causal Experience Memory

This document explains the **design principles, data model, and execution flow**
of C³ (Causal Experience Memory).

---

## Design Principles

C³ is built around the following constraints:

- Deterministic behavior
- O(1) lookup and update
- Bounded memory
- No model retraining
- No prompt injection
- No embeddings or vector search

C³ is intentionally **not intelligent** — it provides *experience*, not reasoning.

---

## System Placement

C³ sits **after reasoning and before action**.

```
User / Environment
↓
Reasoning Engine (LLM / Planner)
↓
C³ Memory
↓
Tools / APIs / Actions
↓
Outcome / Feedback
↺
```

This placement allows C³ to influence behavior **without hijacking the model**.

---

## Mental Model (Human Analogy)

Humans do not remember:
- every sentence
- every document
- every conversation

Humans remember:
- “This failed before”
- “This works here”
- “Avoid this mistake”

C³ encodes this exact mechanism.

---

## Core Data Model

### Causal Rule (Atomic Unit)

```
(ContextHash) → (Action) → (Outcome, Confidence)
```

Only **lessons** are stored — not raw data.

### Example

**Context:**
- intent = FACTUAL
- domain = QA
- tool = SEARCH
- retry = 0

**Action:**
- tool_id = 42

**Outcome:**
- confidence = -0.8

---

## Core Components

### 1. Context Encoder

- Converts structured context into a fixed-size hash
- No raw text
- No embeddings

**Output:**
- ContextHash (uint64)

---

### 2. Memory Store

**Data structure:**

```cpp
unordered_map<ContextHash, vector<CausalRule>>
```

**Properties:**
- O(1) lookup
- Cache-friendly
- Deterministic
- Bounded per context

### 3. Recall Engine

Given a context:
- retrieves matching rules
- selects high-confidence rules
- returns bias, not content

**Output:**
- prefer: actions to promote
- avoid: actions to suppress

### 4. Bias Injection Layer

Bias is applied via:
- tool selection
- retry suppression
- strategy ranking
- (future) logit bias

No prompt stuffing. No token overhead.

### 5. Update Engine

After action execution:
- observes outcome
- updates confidence
- increments hits
- timestamps usage

Learning is:
- online
- incremental
- constant-time
- safe

### 6. Pruning & Forgetting

To prevent overfitting:
- confidence decay
- age-based pruning
- weak-rule removal

This keeps C³ adaptive and bounded.

What C³ Explicitly Does NOT Do
C³ does not:

generate text

plan actions

explore new strategies

store documents or conversations

C³ assumes:

actions already exist

feedback exists

context can be identified

Failure Modes (Honest)
C³ is weak at:

creative exploration

continuous control

discovering new actions

This is by design.

Why This Matters
LLMs are powerful but stateless.

C³ provides:

persistent experience

behavioral improvement

system-level learning

You do not get intelligent systems
without a memory layer like this.

## Future Extensions

- Thread-safe sharding
- Persistent storage
- Cross-context generalization
- Python / JS bindings
- Agent framework integrations
