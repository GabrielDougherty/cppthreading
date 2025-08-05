# C++ Threading Practice Project

This project is set up to practice C++ threading concepts using CMake as the build system.

## Project Structure

- `main.cpp` - Main entry point for the project
- `examples/` - Directory containing example implementations for different threading concepts
  - `mutex_example.cpp` - Mutex and lock examples
  - `condition_variable_example.cpp` - Condition variable examples
  - `thread_pool_example.cpp` - Thread pool implementation examples
  - `atomic_example.cpp` - Atomic operations examples

## Building and Running

### Prerequisites

Make sure you have CMake installed. On macOS, you can install it using:

```bash
brew install cmake
```

### Build Commands

Create a build directory and configure the project:
```bash
mkdir build
cd build
cmake ..
```

Build all targets:
```bash
make
```

Or build specific targets:
```bash
make threading_practice
make mutex_example
make condition_variable_example
make thread_pool_example
make atomic_example
```

### Run Commands

Run the main executable:
```bash
./threading_practice
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

## Alternative Build with Make

If you prefer using make directly without cmake, you can use:

```bash
# Build main program
g++ -std=c++23 -Wall -Wextra -O2 -pthread -o threading_practice main.cpp

# Build examples
g++ -std=c++23 -Wall -Wextra -O2 -pthread -o mutex_example examples/mutex_example.cpp
g++ -std=c++23 -Wall -Wextra -O2 -pthread -o condition_variable_example examples/condition_variable_example.cpp
g++ -std=c++23 -Wall -Wextra -O2 -pthread -o thread_pool_example examples/thread_pool_example.cpp
g++ -std=c++23 -Wall -Wextra -O2 -pthread -o atomic_example examples/atomic_example.cpp
```
