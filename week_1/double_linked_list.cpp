#include <iostream>
using namespace std;

// A doubly linked list node
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

// Insert at the beginning
void insertBeg(Node *&head, int newData) {
  Node *new_node = new Node(newData, head);
  head = new_node;
  link_nodes(head);
}

// Insert after a given node
void insertAfter(Node *prevNode, int newData) {
  if (prevNode == nullptr)
    return;

  Node *new_node = new Node(newData, prevNode->next);
  prevNode->next = new_node;
  link_nodes(prevNode);
}

// Insert at the end
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

// Print forward and backward
void printList(Node *node) {
  Node *last = nullptr;
  cout << "\nForward: ";
  while (node != nullptr) {
    cout << node->data << " ";
    last = node;
    node = node->next;
  }
  cout << "\nReverse: ";
  while (last != nullptr) {
    cout << last->data << " ";
    last = last->prev;
  }
  cout << "\n";
}

int main() {
  Node *head = nullptr;
  insertAtEnd(head, 10);
  insertBeg(head, 20);
  insertBeg(head, 40);
  insertAtEnd(head, 40);
  insertAfter(head->next, 8);
  cout << "DLL is:";
  printList(head);
  return 0;
}
