#include <iostream>
#include "dynamic-stack.h"

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    capacity_ = 16;
    items_ = new StackItem[capacity_];
    size_ = 0;
    init_capacity_ = capacity_;
}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity;
    items_ = new StackItem[capacity_];
    size_ = 0;
    init_capacity_ = capacity_;
}

DynamicStack::~DynamicStack() {
    delete []items_;
    items_ = nullptr;
}

unsigned int DynamicStack::size() const {
    return size_;
}

bool DynamicStack::empty() const {
    return !size_;
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (empty()) return EMPTY_STACK;
    return items_[0];
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_){
        capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
        StackItem* new_items = new StackItem[capacity_];
        for (unsigned int i = 0; i < size_; i++){
            new_items[i] = items_[i];
        }
        int* temp = items_;
        items_ = new_items;
        delete[] temp;
        temp = nullptr;
    }
    for (int i = size_; i > 0; i--){
        items_[i] = items_[i-1];
    }
    items_[0] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    if (empty()) return EMPTY_STACK;
    StackItem popItem = items_[0];
    for(unsigned int i = 0; i < size_; i++){
        items_[i] = items_[i + 1];
    }
    size_--;
    if (size_ <= capacity_/4 && capacity_/2 >= init_capacity_) {
        StackItem *new_items = new StackItem[capacity_ / 2];
        for (unsigned int i = 0; i < size_; i++){
            new_items[i] = items_[i];
        }
        delete[] items_;
        items_ = new_items;
        capacity_ = capacity_/2;
    }
    return popItem;
}
