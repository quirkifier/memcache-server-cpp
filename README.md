# 🧠 Memcached (C++ Clone)

An in-key memory value store designed to mimic the core functionality of **Memcached**, such as:
- `get`
- `set`
- `update`
- `del`

It includes:
-  Multi-threading support via `std::thread` and `std::async`
- ️ A built-in custom `hashmap`
-  Networking through Telnet (might implement it through Boost.Asio)
-  File input/output persistence
-  Modular design to fulfill OOP principles


# 📊 Diagrams

## 🧱 System Architecture

![System Architecture](assets/sys_diagram.png)

> 🔹 Note: The **Quantum HashMap** is just the name of my custom-built hashmap

---

## 🧭 Analysis Diagram (Flowchart)

![Flow Chart](assets/flow_chart.png)

---

## 🔧 UML Class Diagram

![UML Diagram](assets/memcache_uml.png)
> 🔹 Note: Might change a little bit during the implementation phase
# Networking
For networking, the system uses a Telnet-compatible interface to allow clients to connect and issue commands in real time. The server is designed to handle multiple concurrent client connections using std::thread, with each thread responsible for processing incoming requests from a separate client.
The protocol used will be Tcp.Optionally i might use Boost asio to implement it.
# Hashmap
I will implement a custom-built hashmap which will replicate std::unorderedMap<>.
The hashmap will handle collisions using a linked list and will be thread-safe through the use of a mutex. 
One advantage of this is that we can manipulate the hashmap for our use—for example, we can create a read-only memcache with no mutex lock on reads, allowing multiple users to access it at the same time.
# implementation
## ✅ Implementation Checklist

### 🔹 Core Infrastructure
- [x] Define command interface: `get`, `set`, `update`, `del`, `exit`.
- [x] Parse client commands with basic tokenization.

### 🔹 Custom Hashmap
- [x] Implement internal `Node` struct (key, value, next pointer).
- [x] Implement `HashMap` class with:
    - [x] Custom hash function.
    - [x] `insert()` / `set()` method.
    - [x] `get()` method.
    - [x] `update()` method.
    - [x] `delete()` method.
    - [x] Collision handling using separate chaining.
- [x] Add `std::mutex` for thread-safe access:
### 🔹 Multithreading Support
- [x] Accept multiple clients using `std::thread`.
- [x] Handle each client in a dedicated worker thread.
- [x] Ensure thread-safe hashmap operations.
- [x] Implement proper thread cleanup (join/detach).
- 
- ### 🔹 Networking Layer
- [x] Create socket server using:
    - [x] Telnet-compatible raw TCP sockets, or
    - [ ] Boost.Asio (optional).
- [x] Accept client connections in a loop.
- [x] Process commands sent over TCP.
- [x] Handle graceful disconnect and client errors.

### 🔹 File
- [x] Load key value data from a file at startup.
  - [x] A Logging file for error
- [x] Write updated data back to file on:
    - [x] Key updates
    - [x] Program exit
- [x] Support simple serialization/deserialization.
