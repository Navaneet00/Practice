# C++ Low-Latency Practice

Focused exercises in systems programming, lock-free concurrency,
and cache-optimized data structures — every claim is benchmarked
with measured results.

## Repository Structure
```
Practice/
├── concurrency/
│   ├── lockfree_stack.cpp
│   ├── producer_consumer_pattern.cpp
│   └── week2_multithreading.cpp
├── dsa/
│   ├── binary_tree.cpp
│   ├── graphs.cpp
│   └── shortest_path_algos.cpp
├── memory_layout/
│   ├── aos_vs_soa.cpp
│   └── branchy_vs_branchless.cpp
├── systems/
│   └── fork_example.cpp
├── student_record_system.cpp
├── week1_cpp_fundamentals.cpp
└── README.md
```

## Contents

### Concurrency

| File | Concept | Key Takeaway |
|------|---------|--------------|
| `lockfree_stack.cpp` | CAS-based lock-free stack | `compare_exchange_weak` retry loop, ABA problem awareness |
| `producer_consumer_pattern.cpp` | condition_variable + mutex | `notify_one` vs `notify_all`, spurious wakeup handling |
| `week2_multithreading.cpp` | Rule of Five, atomic ops | move semantics, `memory_order` semantics |

### Memory Layout

| File | Concept | Key Takeaway |
|------|---------|--------------|
| `aos_vs_soa.cpp` | AoS vs SoA cache efficiency | **6.7x speedup** on price scan with SoA layout |
| `branchy_vs_branchless.cpp` | Branch prediction cost | **3.75x speedup** on random data with branchless arithmetic |
| `false_sharing/` | Cache line contention | `alignas(64)` — **3x improvement** on contended counters |

### Systems

| File | Concept | Key Takeaway |
|------|---------|--------------|
| `fork_example.cpp` | Process creation, copy-on-write | `fork()` semantics, `waitpid()` lifecycle |

### DSA (C++)

| File | Concept |
|------|---------|
| `binary_tree.cpp` | DFS/BFS traversals, LCA, path sum, BST validation |
| `graphs.cpp` | BFS, DFS, Dijkstra, Topological sort, Course Schedule |
| `shortest_path_algos.cpp` | Dijkstra, Bellman-Ford, BFS on weighted graphs |

### Week 1 Capstone

| File | Concept | Key Takeaway |
|------|---------|--------------|
| `student_record_system.cpp` | Full CRUD system | OOP, RAII, smart pointers, templates, STL containers |
| `week1_cpp_fundamentals.cpp` | C++ core concepts | Pointers, references, const correctness, Rule of Five |

---

## Benchmarked Results

| Experiment | Naive | Optimized | Speedup |
|------------|-------|-----------|---------|
| Price scan — AoS vs SoA | ~800ms | ~120ms | **6.7x** |
| Conditional sum — branchy vs branchless | ~450ms | ~120ms | **3.75x** |
| Counter updates — false sharing vs aligned | ~3x slower | baseline | **3x** |

All benchmarks run on 1M element datasets with `-O2` unless noted.
False sharing demo: run with `-O0` to see contention effect clearly.

---

## Build
```bash
g++ -O2 -std=c++17 -pthread <filename.cpp> -o out && ./out
```

False sharing demo — run without optimizations:
```bash
g++ -O0 -std=c++17 -pthread memory_layout/false_sharing.cpp -o fs && ./fs
```

---

## Concepts Covered

**C++ Core:** RAII, Rule of Five, move semantics, smart pointers,
templates, const correctness, STL internals

**Concurrency:** mutex, condition_variable, atomics,
memory_order (relaxed/acquire/release/seq_cst),
lock-free CAS loops, ABA problem

**Cache & CPU:** AoS vs SoA layout, false sharing, cache line
alignment, branch prediction, branchless arithmetic

**Systems:** Linux File system hierarchy, Process creation (fork), copy-on-write, signals, virtual memory

**DSA:** Trees, graphs, shortest paths — implemented in C++
with performance-conscious design

---

## Related Project

See [OrderBook](https://github.com/Navaneet00/OrderBook) —
a full concurrent limit order book and matching engine built
on these foundations, achieving **610K trades/sec at 227ns**
average match latency.
