#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Heap {
private:
    std::vector<T> heap;
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);
    virtual void heapifyUp(int index) = 0;
    virtual void heapifyDown(int index) = 0;

public:
    void push(T value);
    T top();
    void pop();
    bool empty();
    int size();
};

template <typename T>
class MaxHeap : public Heap<T>
{
private:
    using Heap<T>::heap;
    using Heap<T>::parent;
    using Heap<T>::leftChild;
    using Heap<T>::rightChild;
    void heapifyUp(int index) override;
    void heapifyDown(int index) override;
};


template <typename T>
class MinHeap : public Heap<T>
{
private:
    using Heap<T>::heap;
    using Heap<T>::parent;
    using Heap<T>::leftChild;
    using Heap<T>::rightChild;
    void heapifyUp(int index) override;
    void heapifyDown(int index) override;
};