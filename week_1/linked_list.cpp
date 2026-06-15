#include <iostream>

class Node {
public:
  int data;
  Node *next;

  Node(int newData, Node *head) {
    data = newData;
    next = (head != nullptr) ? head : nullptr;
  }
};

void insertBeg(Node *&head, int newData) {
  Node *new_node = new Node(newData, head);
  head = new_node;
}

void insertAfter(Node *prevNode, int newData) {
  if (prevNode == nullptr)
    return;

  Node *new_node = new Node(newData, prevNode->next);
  prevNode->next = new_node;
}

void insertLast(Node *&head, int newData) {
  Node *new_node = new Node(newData, nullptr);

  if (head == nullptr) {
    head = new_node;
    return;
  }

  Node *temp = head;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  temp->next = new_node;
}

void printList(Node *node) {
  while (node != nullptr) {
    std::cout << node->data << " -> ";
    node = node->next;
  }
  std::cout << "NULL\n";
}

int main() {
  Node *head = nullptr;
  insertLast(head, 6);        // 6
  insertBeg(head, 7);         // 7 -> 6
  insertBeg(head, 1);         // 1 -> 7 -> 6
  insertLast(head, 4);        // 1 -> 7 -> 6 -> 4
  insertAfter(head->next, 8); // after 7

  std::cout << "Linked list:\n";
  printList(head);

  return 0;
}
