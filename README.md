# C++ Low-Latency Practice

Focused exercises in systems programming, lock-free concurrency, and 
cache-optimized data structures — written as preparation for HFT 
software engineering roles.

Each file is self-contained with inline comments explaining the 
"why" behind every technique, not just the "what".

---

## Contents

### Concurrency
| File | Concept | Key Takeaway |
|------|---------|--------------|
| `lockfree_stack.cpp` | CAS-based lock-free stack | compare_exchange_weak loop, ABA awareness |
| `producer_consumer.cpp` | condition_variable + mutex | notify_one vs notify_all, spurious wakeup |
| `week2_multithreading.cpp` | Rule of Five, atomic ops | move semantics, memory_order semantics |

### Memory Layout
| File | Concept | Key Takeaway |
|------|---------|--------------|
| `aos_vs_soa.cpp` | AoS vs SoA cache efficiency | 6-7x speedup on price scan with SoA |
| `branchy_vs_branchless.cpp` | Branch prediction cost | 3-4x speedup on random data with branchless |
| `false_sharing/` | Cache line contention | alignas(64) — 2-3x improvement on contended counters |

### Systems
| File | Concept | Key Takeaway |
|------|---------|--------------|
| `fork_example.cpp` | Process creation, copy-on-write | fork() semantics, waitpid |

---

## Key Numbers Demonstrated

| Experiment | Naive | Optimized | Speedup |
|------------|-------|-----------|---------|
| Price scan (AoS vs SoA) | ~800ms | ~120ms | 6.7x |
| Branchy vs branchless (random data) | ~450ms | ~120ms | 3.75x |
| False sharing vs aligned | ~3x slower | baseline | 3x |

---

## Build
```bash
g++ -O2 -std=c++17 -pthread <filename.cpp> -o out && ./out
```

For false sharing demo — run without optimizations to see the effect clearly:
```bash
g++ -O0 -std=c++17 -pthread false_sharing/false_sharing.cpp -o fs && ./fs
```
