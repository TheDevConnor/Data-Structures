#include "Queue.h"

#include <iostream>
#include <string>

template <typename T> Queue<T>::Queue(unsigned capacity) {
  data = new T[capacity];
  frnt = 0;
  bck = 0;
  queueSize = 0;
  this->capacity = capacity;
}

template <typename T> unsigned Queue<T>::size() const { return queueSize; }
template <typename T> bool Queue<T>::empty() const { return (queueSize == 0); }

template <typename T> bool Queue<T>::full() const {
  return (this->queueSize == this->capacity);
}

template <typename T> const T &Queue<T>::front() const {
  if (this->empty())
    throw std::string("Empty Queue!");
  return this->data[frnt];
}

template <typename T> void Queue<T>::enqueue(const T &val) {
  if (this->full())
    throw std::string("Full Queue!");
  this->data[bck] = val;
  this->bck = (this->bck + 1) % this->capacity;
  ++this->queueSize;
}

template <typename T> void Queue<T>::dequeue() {
  if (this->empty())
    throw std::string("Empty Queue!");
  this->frnt = (this->frnt + 1) % this->capacity;
  --this->queueSize;
}

template <typename T> void Queue<T>::print() const {
  if (empty()) {
    std::cout << "Empty\n";
    return;
  }
  int i = frnt;
  while (i != (bck + 1) % capacity) {
    std::cout << data[i] << ' ';
    i = (i + 1) % capacity;
  }
}
