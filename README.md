# C++ Threading Practice Project

This project is set up to practice C++ threading concepts.

## Building and Running

### Prerequisites

Install Nix then get into the shell with `nix develop`. For integration with VS Code I use the "Nix Environment Selector". I'm using Nix to get a newer compiler version so I can play around with C++23 featuers like `std::println`.

### Build Commands

Create a build directory and configure the project:
```bash
mkdir build
cd build
cmake -G Ninja ..
```

Build all targets:
```bash
ninja
```

Or build specific targets:
```bash
ninja atomic_example
```

### Run Commands

Run the main executable:
```bash
./atomic_example
```

Run specific examples:
```bash
./mutex_example
./condition_variable_example
./thread_pool_example
./atomic_example
```

## Threading Concepts to Practice

1. **Basic Thread Creation and Management**
   - `std::thread` creation and joining
   - `std::jthread` (C++23) with automatic cleanup and stop tokens
   - Thread lifecycle management

2. **Synchronization Primitives**
   - `std::mutex` and `std::lock_guard`
   - `std::unique_lock` and `std::shared_lock`
   - `std::condition_variable`
   - `std::barrier` and `std::latch` (C++20/23)

3. **Atomic Operations**
   - `std::atomic` types
   - Memory ordering semantics
   - Enhanced atomic operations (C++23)

4. **Advanced Concepts**
   - Thread pools
   - Producer-consumer patterns
   - Reader-writer locks
   - Futures and promises
   - Cooperative cancellation with `std::stop_token` (C++23)

## Notes

- All targets are configured to link against pthreads using CMake's `Threads::Threads`
- C++23 standard is enabled for modern threading features
- Compiler warnings are enabled for better code quality
- The project is ready for implementing various threading examples

