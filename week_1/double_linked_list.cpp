#include <iostream>

class Node {
public:
  int data;
  Node *next;
  Node *prev;
  Node(int newData, Node *head) {
    data = newData;
    next = (head != nullptr) ? head : nullptr;
    prev = nullptr;
  }
};

void link_nodes(Node *&head) {
  Node *current = head;
  while (current != nullptr) {
    if (current->next != nullptr) {
      current->next->prev = current;
    }

    current = current->next;
  }
}

void insertBeg(Node *&head, int newData) {
  Node *new_node = new Node(newData, head);
  head = new_node;
  link_nodes(head);
}

void insertAfter(Node *prevNode, int newData) {
  if (prevNode == nullptr)
    return;

  Node *new_node = new Node(newData, prevNode->next);
  prevNode->next = new_node;
  link_nodes(prevNode);
}

void insertAtEnd(Node *&head, int newData) {
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
  link_nodes(temp);
}

void printList(Node *node) {
  Node *last = nullptr;
  std::cout << "\nForward: ";
  while (node != nullptr) {
    std::cout << node->data << " ";
    last = node;
    node = node->next;
  }
  std::cout << "\nReverse: ";
  while (last != nullptr) {
    std::cout << last->data << " ";
    last = last->prev;
  }
  std::cout << "\n";
}

int main() {
  Node *head = nullptr;
  insertAtEnd(head, 10);
  insertBeg(head, 20);
  insertBeg(head, 40);
  insertAtEnd(head, 40);
  insertAfter(head->next, 8);
  std::cout << "DLL is:";
  printList(head);
  return 0;
}
