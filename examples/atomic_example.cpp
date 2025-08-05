#include <iostream>
#include <atomic>
#include <array>
#include <thread>
#include <vector>
#include <cstdint>
#include <chrono>
#include <random>
#include <print>
#include <new>

template<typename T, size_t Size>
class SPSCQueue {
private:
    alignas(128) std::atomic<size_t> head_{0};
    alignas(128) std::atomic<size_t> tail_{0};
    alignas(128) std::array<T, Size+1> buffer_;
    
public:
    bool push(const T& item) {
        auto cur_tail = tail_.load(std::memory_order_relaxed);
        if ((cur_tail + 1) % Size == head_.load(std::memory_order_acquire) % Size)
        {
            return false;
        }
        buffer_[cur_tail % Size] = item;
        tail_.store(cur_tail+1, std::memory_order_release);
        return true;
    }
    
    bool pop(T& item) {
        auto cur_head = head_.load(std::memory_order_relaxed);
        if (cur_head % Size == tail_.load(std::memory_order_acquire) % Size)
        {
            return false;
        }
        item = buffer_[cur_head % Size];
        head_.store(cur_head+1, std::memory_order_release);
        return true;
    }
};

int main() {
    constexpr size_t QUEUE_SIZE = 1024;
    constexpr int NUM_ITEMS = 100000;
    
    SPSCQueue<int, QUEUE_SIZE> queue;
    std::atomic<int> items_produced{0};
    std::atomic<int> items_consumed{0};
    std::atomic<bool> producer_done{false};
    
    std::cout << "Starting SPSC Queue Test with " << NUM_ITEMS << " items...\n";
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    {
        // Producer thread
        std::jthread producer([&]() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 1000);
            
            for (int i = 0; i < NUM_ITEMS; ++i) {
                int value = dis(gen);
                
                // Keep trying to push until successful
                while (!queue.push(value)) {
                    // Queue is full, yield and try again
                    std::this_thread::yield();
                }
                
                items_produced.fetch_add(1, std::memory_order_relaxed);
                
                // Occasionally sleep to make it more realistic
                if (i % 10000 == 0) {
                    std::this_thread::sleep_for(std::chrono::microseconds(1));
                }
            }
            
            producer_done.store(true, std::memory_order_release);
            std::cout << "Producer finished: " << items_produced.load() << " items produced\n";
        });
        
        
        // Consumer thread
        std::jthread consumer([&]() {
            int value;
            int consumed = 0;
            
            while (true) {
                if (queue.pop(value)) {
                    consumed++;
                    items_consumed.fetch_add(1, std::memory_order_relaxed);
                    
                    // Occasionally print progress
                    if (consumed % 25000 == 0) {
                        std::cout << "Consumer progress: " << consumed << " items consumed\n";
                    }
                } else {
                    // Queue is empty
                    if (producer_done.load(std::memory_order_acquire)) {
                        // Producer is done, try one more time to empty the queue
                        if (!queue.pop(value)) {
                            break; // Queue is truly empty and producer is done
                        }
                        consumed++;
                        items_consumed.fetch_add(1, std::memory_order_relaxed);
                    } else {
                        // Producer still working, yield and try again
                        std::this_thread::yield();
                    }
                }
            }
            
            std::cout << "Consumer finished: " << consumed << " items consumed\n";
        });
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::println("\n=== SPSC Queue Test Results ===");
    std::cout << "Items produced: " << items_produced.load() << "\n";
    std::cout << "Items consumed: " << items_consumed.load() << "\n";
    std::cout << "Test duration: " << duration.count() << " ms\n";
    std::cout << "Throughput: " << (NUM_ITEMS * 1000.0 / duration.count()) << " items/second\n";
    
    if (items_produced.load() == items_consumed.load() && items_consumed.load() == NUM_ITEMS) {
        std::cout << "✓ Test PASSED: All items successfully transferred!\n";
    } else {
        std::cout << "✗ Test FAILED: Item count mismatch!\n";
    }
    
    return 0;
}
