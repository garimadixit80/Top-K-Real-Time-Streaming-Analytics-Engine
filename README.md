# 📊 Top-K Real-Time Streaming Analytics Engine (C++)

## Quick Summary

A backend-focused C++ project that processes a continuous stream of events and identifies the Top-K most frequent items in real time using a Count-Min Sketch and a Min-Heap, optimized for fixed memory and low latency.

## 1. Overview
This project implements a Top-K real-time analytics engine that continuously processes a stream of events and identifies the most frequent (Top-K) events at any point in time.

The goal of this project is to demonstrate how large-scale systems (like search trend detection or content popularity tracking) can efficiently process high-volume streams without storing all data in memory.

This is a backend / systems-focused project — there is no UI. The emphasis is on:

* algorithms

* data structures

* performance

* correctness

---

## 2. The Current Problem
Modern systems deal with massive, continuous data streams, for example:
* **Google:** most searched queries
* **Netflix:** most watched content
* **E-commerce:** trending products
* **Social media:** trending hashtags

### Why this is a problem
* **Data never stops:** Events arrive continuously.
* **Data volume is huge:** Millions of events per second.
* **Memory is limited:** Cannot store all events or exact counts.
* **Low latency is required:** Results must be available almost instantly.

### Traditional approach (not scalable)
Store every event → Maintain exact counts → Sort → Pick Top-K

**Problems:**
* Very high memory usage
* Sorting is expensive
* Does not scale for streaming data

---

## 3. How This System Solves the Problem
This system uses a streaming-first approach. Instead of storing everything, it:
1.  Approximates frequencies
2.  Keeps only the most important data
3.  Processes events one by one

### Core Idea
“You don’t need perfect accuracy to know what’s trending — you need speed and scalability.”

This project combines:

| Component | Purpose |
| :--- | :--- |
| **Count-Min Sketch** | Approximate event frequency using fixed memory |
| **Min-Heap (Top-K)** | Track only the K most frequent events |
| **Stream Simulator** | Mimic real-time data arrival |

---
## 4. Project Structure
```text
topk_streaming_engine/
│
├── src/
│   ├── main.cpp                # Entry point
│   ├── CountMinSketch.h        # CMS interface
│   ├── CountMinSketch.cpp      # CMS implementation
│   ├── TopKManager.h           # Top-K interface
│   ├── TopKManager.cpp         # Heap-based Top-K logic
│   ├── StreamSimulator.cpp     # Stream generator
│
└── README.md
```
---

## 5. Component Breakdown

### 1️⃣ Count-Min Sketch
**Responsible for:**
* Updating event frequencies
* Querying approximate counts

**Key properties:**
* **Fixed memory:** Uses a 2D array of counters, preventing memory bloat.
* **O(1) update and query:** Constant time performance regardless of stream size.
* **Probabilistic accuracy:** Provides a frequency estimate with a provable error bound.

### 2️⃣ Top-K Manager
**Responsible for:**
* Tracking only the Top-K most frequent events.
* Using a **Min-Heap** to keep the smallest frequency at the top for quick comparison.

**Why a Min-Heap?**
* **Efficient removal:** Allows us to quickly discard the "weakest" member of the Top-K list when a higher-frequency event arrives.
* **K-sized storage:** Keeps memory usage strictly tied to the value of $K$.

### 3️⃣ Stream Simulator
**Simulates:**
* Continuous arrival of events.
* Random distribution of event types (simulating different user actions).
* Real-time behavior using artificial delays.

*Note: This replaces real production data sources (like Kafka or RabbitMQ) for demonstration purposes.*

### 4️⃣ main.cpp
**The Orchestration Workflow:**
1.  **Initialize** the Count-Min Sketch with desired depth and width.
2.  **Initialize** the Top-K manager with the value of $K$.
3.  **Generate** the event stream via the Simulator.
4.  **Process** events one by one: Update CMS → Query CMS → Update Top-K.
5.  **Print** the final Top-K results to the console.

---

## 6. How the System Works (Step-by-Step)
1.  An event arrives from the stream (e.g., "scroll").
2.  **Count-Min Sketch** updates its frequency estimate.
3.  The estimated frequency is sent to the **Top-K Manager**.
4.  **Top-K Manager:**
    * Inserts the event if heap size < K.
    * Replaces the smallest-frequency event if needed.
5.  The system always maintains the current Top-K events.


This happens in real time, without stopping the stream.


---

## 7. How This System Is Different From Existing Systems

| Existing Large Systems | This Project |
| :--- | :--- |
| Distributed, complex | Single-process, focused |
| Heavy infrastructure | Lightweight and readable |
| Full production stack | Core algorithm only |
| Many optimizations | Clarity over over-engineering |

**Why this difference is intentional:**
The goal is learning and demonstration, not production deployment. This project focuses on the heart of the problem, clean logic, and interview-explainable design.

---

## 8. Design Constraints
This project intentionally works under these constraints:
* Fixed memory for frequency tracking
* Single-threaded execution
* In-memory processing
* No persistence or database
* No UI


---

## 9. Trade-offs

| Decision | Benefit | Trade-off |
| :--- | :--- | :--- |
| **Count-Min Sketch** | Low memory | Approximate counts |
| **Min-Heap for Top-K** | Fast updates | Lazy cleanup |
| **No database** | Simple | No persistence |
| **No UI** | Focus on core | No visualization |

All trade-offs are explicit and intentional.

---

## 10. Tech Stack
* **Language:** C++ (C++17)
* **Data Structures:** Min-Heap, Hash Map (for Top-K tracking)
* **Algorithms:** Count-Min Sketch (Probabilistic Frequency Tracking)
* **Paradigm:** Streaming / Real-time processing
--- 

## 11. How to Run

### Compile
```bash
g++ -std=c++17 CountMinSketch.cpp TopKManager.cpp StreamSimulator.cpp main.cpp -o topk_engine
```
### Run
```bash
./topk_engine
```
### Sample output
```bash
Top-K Events:
scroll -> 7
view -> 4
purchase -> 4
```

(Note: Output varies because the stream is simulated.)


---

<img width="500" height="500" alt="Architecture_Diagram" src="https://github.com/user-attachments/assets/73e486d0-8aad-4111-963d-0f33e7a1998f" />

## 12. What This Project Demonstrates
* **Understanding of streaming systems:** Managing data that never ends.
* **Practical use of probabilistic data structures:** Leveraging the Count-Min Sketch for efficiency.
* **Efficient memory-aware design:** Working within fixed memory bounds.
* **Clear separation of responsibilities:** Modular architecture (CMS, Top-K Manager, Simulator).
* **Industry-relevant problem solving:** Tackling the "Heavy Hitters" problem found in large-scale systems.

---

## 13. Limitations (Intentional)
To maintain a strict focus on the core analytics engine, the following were deliberately excluded:
* **Approximate counts:** Results are based on probability (standard for CMS).
* **No persistence:** The engine operates entirely in-memory.
* **No UI or dashboards:** Focus is on backend logic and performance.
* **Single-process simulation:** Designed for clarity rather than distributed complexity.

---

## 14. Future Improvements (Logical Extensions)
While not currently implemented, the system is designed to naturally extend to:
* **Sliding window Top-K:** Tracking trends over the last hour/day instead of the whole session.
* **Multithreaded stream processing:** Using a producer-consumer model for higher throughput.
* **Periodic Top-K snapshots:** Saving the state of trending items at regular intervals.
* **Export results:** Sending data to an external file or a REST API.
* **Distributed sketch merging:** Merging multiple sketches from different nodes for horizontal scaling.



---

## 15. Why This Project Matters
This project mirrors the core internal logic used by major platforms for:
1. **Search trend detection** (e.g., Google Trends)
2. **Popular content ranking** (e.g., Netflix or YouTube "Trending")
3. **High-frequency event analytics** (e.g., DDoS attack detection or ad-click tracking)

It prioritizes the **internal mechanics** of high-scale systems over surface-level features.

---


---





