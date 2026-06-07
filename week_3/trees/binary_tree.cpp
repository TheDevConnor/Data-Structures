#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void preorder(Node* root) {
    if (!root) return;
    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << " ";
}

int height(Node* root) {
    if (!root) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    std::cout << "Tree structure:\n";
    std::cout << "        1\n";
    std::cout << "       / \\\n";
    std::cout << "      2   3\n";
    std::cout << "     / \\ / \\\n";
    std::cout << "    4  5 6  7\n\n";

    std::cout << "Preorder:  ";
    preorder(root);
    std::cout << "\n";

    std::cout << "Inorder:   ";
    inorder(root);
    std::cout << "\n";

    std::cout << "Postorder: ";
    postorder(root);
    std::cout << "\n";

    std::cout << "Height: " << height(root) << "\n";

    deleteTree(root);
    return 0;
}
