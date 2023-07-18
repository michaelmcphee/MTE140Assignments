#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    // Set the initial capacity of the queue to 16.
    capacity_ = 16;

    // Allocate memory for the queue items.
    items_ = new QueueItem[capacity_];

    // Set the head and tail indices to 0.
    head_ = 0;
    tail_ = 0;

    // Set the initial size of the queue to 0.
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    // Allocate memory for the items array.
    items_ = new QueueItem[capacity];

    // Set head and tail indices to zero, as well as the size of the queue.
    head_ = 0;
    tail_ = 0;
    size_ = 0;

    // Set the maximum capacity of the queue.
    capacity_ = capacity;
}

CircularQueue::~CircularQueue() {
    delete[] items_;
    items_ = nullptr;
}

unsigned int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::empty() const {
    return !size_;
}

bool CircularQueue::full() const {
    return size_ == capacity_;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (empty()) {
        return EMPTY_QUEUE;
    }
    return items_[head_];
}

bool CircularQueue::enqueue(QueueItem value) {
    // Check if the queue is full
    if (full()) {
        return false;
    }

    // Add the item to the tail of the queue
    items_[tail_] = value;

    // Increment the tail index, wrapping around to the front if necessary
    tail_ = (tail_ + 1) % capacity_;

    // Increment the size of the queue
    size_++;

    return true;
}


CircularQueue::QueueItem CircularQueue::dequeue() {
    if (empty()) {
        return EMPTY_QUEUE;
    }

    QueueItem value = items_[head_];
    head_ = (head_ + 1) % capacity_;
    size_--;

    return value;
}

void CircularQueue::print() const {
    if (empty()) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    unsigned int index = head_;
    std::cout << "Queue contents: ";
    for (unsigned int i = 0; i < size_; i++) {
        std::cout << items_[index] << " ";
        index = (index + 1) % capacity_;
    }
    std::cout << std::endl;
}
