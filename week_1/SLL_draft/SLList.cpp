#include "SLList.h"
#include "SLLNode.h"
#include <iostream>

template <typename T> SLList<T>::SLList() {
  head = nullptr;
  tail = nullptr;
  listSize = 0;
}

template <typename T> unsigned SLList<T>::size() const {
  return this->listSize;
}

template <typename T> bool SLList<T>::empty() const {
  return (this->size() == 0);
}

template <typename T> void SLList<T>::push_front(const T &value) {
  this->head = new SLLNode<T>(value, head);
  this->listSize++;

  if (this->size() == 1)
    this->tail = this->head;
}

template <typename T> void SLList<T>::print() const {
  SLLNode<T> *current = head;
  while (current) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << std::endl;
}

template <typename T> void SLList<T>::push_back(const T &value) {
  if (this->empty())
    this->push_front(value);
  else {
    this->tail->next = new SLLNode<T>(value);
    this->tail = this->tail->next;
    this->listSize++;
  }
}

template <typename T> void SLList<T>::pop_front() {
  if (this->empty())
    return;

  SLLNode<T> *temp = this->head;
  this->head = this->head->next;
  delete temp;

  this->listSize--;

  if (this->head == nullptr)
    this->tail = nullptr;
}

template <typename T> void SLList<T>::pop_back() {
  if (this->empty())
    return;

  if (this->size() == 1)
    this->pop_front();
  else {
    SLLNode<T> *current = this->head;

    while (current->next->next != nullptr) {
      current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    this->tail = current;

    this->listSize--;
  }
}
