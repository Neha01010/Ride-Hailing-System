# Ride-Hailing Management System 🚗🚲

An advanced, console-based Ride-Hailing Management System developed in **C** that simulates a real-world ride-booking platform for Cabs and Bikes. The system seamlessly handles drivers, passengers, vehicle allocation, booking history, ride completion, earnings tracking, and performance analytics. 📊

To demonstrate architectural evolution and performance optimization, two distinct versions were developed:
* **Linked List Version:** Simple, dynamic memory storage using linear linked lists. 🧬
* **AVL Tree Version:** Highly optimized implementation utilizing self-balancing AVL Trees for lightning-fast search, insertion, and retrieval operations. ⚡

---

## 🚀 Features

### 👨‍✈️ Driver Management
* Add new drivers and delete drivers from the system.
* Update driver coordinates/locations in real-time.
* Track driver availability statuses.
* Calculate and track cumulative total earnings.

###   Passenger Management
* Register new passengers.
* Maintain detailed ride frequency and usage statistics.
* Perform range-searches for passengers within specific ID intervals.

### 🎫 Ride Booking
* Request instant Cab or Bike rides.
* Support preferred vehicle type filtering.
* **Smart Matching:** Automatically assigns the closest available vehicle.
* Generates cryptographic-style unique booking IDs.

### 🏁 Ride Completion
* Mark active rides as completed.
* Calculate dynamic fares based on vehicle type and travel distance.
* Instantly update driver wallets and passenger trip frequencies.

### 📈 Analytics Dashboard
* Display the **Top 3** highest-earning drivers.
* Identify the most frequent Driver-Passenger pairing (loyalty metrics).
* Show real-time available fleet tracking.
* Review entire system booking histories.

### 💾 Data Persistence
* Save/load driver records to/from flat-file storage.
* Save/load passenger records to/from flat-file storage.
* **Automated Sync:** Loads all records seamlessly on system startup.

---

## 🛠️ Data Structures Used

### 1. Linked List Version
* **Driver List:** Stores all driver profiles dynamically.
* **Passenger List:** Manages passenger details and historical ride frequencies.
* **Booking History List:** Maintains a chronological ledger of active and completed trips.

### 2. AVL Tree Version
* **Driver AVL Tree** *(Key: Driver ID)*
* **Passenger AVL Tree** *(Key: Passenger ID)*
* **Booking AVL Tree** *(Key: Booking ID)*

> 🔄 **Self-Balancing Logic:** The AVL Trees preserve strict balancing properties via 4 classic rotations to ensure heights never drift:
> * Left Rotation (LL)
> * Right Rotation (RR)
> * Left-Right Rotation (LR)
> * Right-Left Rotation (RL)

---

## 🗺️ System Workflow

```text
Passenger Request
       |
       v
Find Nearby Available Vehicles
       |
       v
Select Nearest Vehicle (Euclidean Filter)
       |
       v
Create Booking & Generate Unique ID
       |
       v
Ride Completion & Fare Calculation
       |
       v
Update Wallet Earnings & System Statistics
```

## ⚖️ Trade-offs & Analysis

Choosing the right data structure for a ride-hailing app is a balancing act between simplicity and speed! Here is how the two implementations compare:

### 🧬 Linked List Version

#### 🟢 Advantages
* **Simpler Implementation:** Very easy to understand, code, and debug without worrying about complex tree pointers.
* **Dynamic Memory Allocation:** No fixed-size arrays required; memory scales fluidly as new drivers or passengers join.
* **Low Maintenance Cost:** Zero CPU overhead spent on balancing metrics or node rotations.
* **Efficient Sequential Traversal:** Perfect when you need to process or print every single record one after another (e.g., printing the full booking history).

#### 🔴 Disadvantages
* **Slow Searching:** Finding a specific driver or passenger requires a linear traversal. In the worst case, it takes $O(n)$ time. 
* **Poor Scalability:** Performance degrades significantly as the dataset grows to thousands of active users.
* **No Ordering Guarantee:** The list is inherently unsorted, meaning extra work and processing are needed to display sorted data.
* **Expensive Vehicle Allocation:** Finding the nearest vehicle forces the system to scan through every single driver in the list sequentially.

---

### 🌳 AVL Tree Version

#### 🟢 Advantages
* **Fast Search Operations:** Search operations are mathematically guaranteed to execute in lightning-fast logarithmic time ($O(\log n)$). ⚡
* **Self-Balancing:** Tree height remains perfectly optimized and approximately around $\text{Height} \approx \log_{2}(n)$.
* **Efficient Range Queries:** Highly suitable for specific lookups, like searching for passengers within a given ID range.
* **Better Scalability:** Handles massive numbers of drivers, passengers, and bookings simultaneously without lagging.
* **Faster Ride Allocation:** Quick retrieval of records improves overall system responsiveness when matching a passenger to a driver.

#### 🔴 Disadvantages
* **More Complex Implementation:** Requires intricate rotation logic (LL, RR, LR, RL) and strict balance-factor maintenance.
* **Additional Memory Overhead:** Each node requires extra memory fields to store its current height information.
* **Slower Insert/Delete than Simple Linked Lists:** While finding the spot is fast, the actual insertion or deletion takes extra work due to the required balancing operations.
* **Harder to Debug:** Tracking pointer movements across multiple structural rotations can introduce subtle, hard-to-find bugs.

---

## 💻 Technologies & Computer Science Concepts Used

This ecosystem relies heavily on core engineering principles and native C paradigms:

* **C Programming Language:** Chosen for low-level memory control, predictable runtime execution, and zero garbage collection overhead.
* **Structures (`struct`):** Used to construct customized composite data contracts representing `Driver`, `Passenger`, and `Booking` entities.
* **Pointers & Memory Addresses:** Extensively deployed to map dynamic tracking nodes, pass structures without copy overhead, and build structural linkages.
* **Dynamic Memory Allocation:** Native usage of `malloc()` and `free()` to scale node counts on-demand directly from the system heap.
* **Advanced Data Layouts:** * Linear Singly/Doubly Linked Lists for raw chronological journaling.
  * Balanced Binary Search Trees (AVL Trees) acting as optimized lookup indexes.
* **File I/O Handling:** Persistent stream writing (`fprintf`/`fwrite`) and stream parsing (`fscanf`/`fread`) to back up and restore states onto local disk storage.
* **Recursive Algorithms:** Clean mathematical implementations used for tree traversals, structural balance validations, and multi-level node deletions.
* **Tree Traversals:** Utilization of In-order, Pre-order, and Post-order strategies to dump sequential indexes, clone states, and clean up memory allocations.