#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head_;
    while (current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    if (size_) return false;
    return true;
}


bool DoublyLinkedList::full() const {
    if (size_==CAPACITY) return true;
    return false;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if (index >= size_) {
        return tail_->value;
    }
    return getNode(index)->value;

}


unsigned int DoublyLinkedList::search(DataType value) const {
    Node* current = head_;
    unsigned int index = 0;
    while (current!=nullptr){
        if (current->value == value) return index;
        index++;
        current = current->next;
    }
    return size_;
}


void DoublyLinkedList::print() const {
    if (head_ == nullptr) {
        return;
    }
    //print all nodes
    Node *temp = head_;
    while (temp != nullptr) {
        std::cout<< temp->value << "->";
        temp = temp->next;
    }
    std::cout << std::endl;
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    if (index>=size_){
        std::cout << "Index doesn't exist";
        return nullptr;
    }
    Node* current = head_;
    for (int i = 0; i < index; i++){
        current = current->next;
    }
    return current;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if (full() || index>size_){
        std::cout << "Index doesn't exist or list is full";
        return false;
    }
    if (!index){
        insert_front(value);
        size_++;
        return true;
    }
    if (index == size_){
        insert_back(value);
        size_++;
        return true;
    }
    Node* newNode = new Node(value);
    Node* current = getNode(index);
    Node* previous = current->prev;
    newNode->prev = previous;
    newNode->next = current;
    previous->next = newNode;
    current->prev = newNode;
    size_++;
    return true;
}


bool DoublyLinkedList::insert_front(DataType value) {
    if (full()) return false;
    Node* newNode = new Node(value);
    if (empty()){
        head_ = newNode;
        tail_ = newNode;
    }
    else{
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
    }
    size_++;
    return true;
}


bool DoublyLinkedList::insert_back(DataType value) {
    if (full()) return false;
    Node* newNode = new Node(value);
    if (empty()){
        head_ = newNode;
        tail_ = newNode;
    }
    else {
        newNode->prev = tail_;
        tail_->next = newNode;
        tail_ = newNode;
    }
    size_++;
    return true;
}


bool DoublyLinkedList::remove(unsigned int index) {
    if (index >= size_){
        return false;
    }
    Node* current = getNode(index);
    if (current == head_){
        remove_front();
        return true;
    }
    if (current == tail_){
        remove_back();
        return true;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    size_--;
    return true;
}


bool DoublyLinkedList::remove_front() {
    if (empty()) return false;
    Node* current = head_;
    head_ = current->next;
    if (head_ != nullptr) head_->prev = nullptr;
    else tail_ = nullptr;
    delete current;
    size_--;
    return true;
}


bool DoublyLinkedList::remove_back() {
    if (empty()) return false;
    Node* current = tail_;
    tail_ = current->prev;
    if (tail_ != nullptr) tail_->next = nullptr;
    else tail_ = nullptr;
    delete current;
    size_--;
    return true;
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if (index >= size_) return false;
    getNode(index)->value = value;
    return true;
}
