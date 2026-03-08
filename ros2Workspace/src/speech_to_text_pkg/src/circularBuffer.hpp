#pragma once
#include "pch.hpp"



template <typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    size_t head = 0;      // next write
    size_t tail = 0;      // next read
    size_t capacity = 0;
    bool full = false;
    mutable std::mutex mtx;  // Made mutable for const methods

public:
    explicit CircularBuffer(size_t size) : buffer(size), capacity(size) {}

    // Push data into buffer
    void push(const T* data, size_t len) {
        std::lock_guard<std::mutex> lock(mtx);
        for(size_t i = 0; i < len; ++i) {
            buffer[head] = data[i];
            head = (head + 1) % capacity;

            if(full) { // overwrite oldest
                tail = (tail + 1) % capacity;
            }
            if(head == tail) {
                full = true;
            } 
            
        }
    }

    // Pop up to len items from buffer into a vector
    std::vector<T> pop(size_t len) {
        std::lock_guard<std::mutex> lock(mtx);
        size_t available = sizeUnsafe();
        if(len > available) {
            len = available;
        }
        std::vector<T> out(len);
        for(size_t i = 0; i < len; ++i) {
            out[i] = buffer[tail];
            tail = (tail + 1) % capacity;
            full = false;
        }
        return out;
    }

    // Thread-safe size getter
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return sizeUnsafe();
    }

    // Check if empty (thread-safe)
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return (!full && head == tail);
    }

    // Clear buffer
    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        head = tail = 0;
        full = false;
    }

    std::vector<T> peekLast(size_t len) const {
        std::lock_guard<std::mutex> lock(mtx);

        size_t available = sizeUnsafe();
        if(len > available) {
            len = available;
        }

        std::vector<T> out(len);

        size_t start = (head + capacity - len) % capacity;

        if(start + len <= capacity) {
            std::copy(buffer.begin() + start,
                    buffer.begin() + start + len,
                    out.begin());
        } else {
            size_t first_part = capacity - start;

            std::copy(buffer.begin() + start,
                    buffer.end(),
                    out.begin());

            std::copy(buffer.begin(),
                    buffer.begin() + (len - first_part),
                    out.begin() + first_part);
        }

        return out;
    }

private:
    // Internal unsafe version for when lock is already held
    size_t sizeUnsafe() const {
        if(full) return capacity;
        if(head >= tail) return head - tail;
        return capacity - tail + head;
    }
};

