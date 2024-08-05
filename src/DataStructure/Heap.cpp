#include "Heap.hpp"

template <typename T>
int Heap<T>::parent(int index) 
{
    return (index - 1) / 2;
}

template <typename T>
int Heap<T>::leftChild(int index) {
    return 2 * index + 1;
}

template <typename T>
int Heap<T>::rightChild(int index) {
    return 2 * index + 2;
}

template <typename T>
void Heap<T>::push(T value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T>
T Heap<T>::top() {
    if (!heap.empty()) {
        return heap.front();
    }
    throw std::out_of_range("Heap is empty");
}

template <typename T>
void Heap<T>::pop() {
    if (!heap.empty()) {
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        heapifyDown(0);
    } else {
        throw std::out_of_range("Heap is empty");
    }
}

template <typename T>
bool Heap<T>::empty() {
    return heap.empty();
}

template <typename T>
void MaxHeap<T>::heapifyUp(int index) 
{
    if (index && heap[parent(index)] < heap[index]) 
    {
        std::swap(heap[index], heap[parent(index)]);
        heapifyUp(parent(index));
    }
}

template <typename T>
void MaxHeap<T>::heapifyDown(int index) 
{
    int left = leftChild(index);
    int right = rightChild(index);
    int largest = index;
    if (left < heap.size() && heap[left] > heap[index]) 
    {
        largest = left;
    }
    if (right < heap.size() && heap[right] > heap[largest]) 
    {
        largest = right;
    }
    if (largest != index) 
    {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

template <typename T>
void MinHeap<T>::heapifyUp(int index) 
{
    if (index && heap[parent(index)] > heap[index]) 
    {
        std::swap(heap[index], heap[parent(index)]);
        heapifyUp(parent(index));
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(int index) 
{
    int left = leftChild(index);
    int right = rightChild(index);
    int smallest = index;
    if (left < heap.size() && heap[left] < heap[index]) 
    {
        smallest = left;
    }
    if (right < heap.size() && heap[right] < heap[smallest]) 
    {
        smallest = right;
    }
    if (smallest != index) 
    {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}