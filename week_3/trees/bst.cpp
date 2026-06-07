#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

bool search(Node* root, int val) {
    if (!root) return false;
    if (root->data == val) return true;
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}

Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left)
        current = current->left;
    return current;
}

Node* remove(Node* root, int val) {
    if (!root) return nullptr;
    if (val < root->data)
        root->left = remove(root->left, val);
    else if (val > root->data)
        root->right = remove(root->right, val);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int v : values)
        root = insert(root, v);

    std::cout << "BST after inserts (inorder): ";
    inorder(root);
    std::cout << "\n";

    std::cout << "Search 40: " << (search(root, 40) ? "found" : "not found") << "\n";
    std::cout << "Search 90: " << (search(root, 90) ? "found" : "not found") << "\n";

    root = remove(root, 20);
    std::cout << "After deleting 20 (inorder): ";
    inorder(root);
    std::cout << "\n";

    root = remove(root, 30);
    std::cout << "After deleting 30 (inorder): ";
    inorder(root);
    std::cout << "\n";

    root = remove(root, 50);
    std::cout << "After deleting 50 (inorder): ";
    inorder(root);
    std::cout << "\n";

    deleteTree(root);
    return 0;
}
